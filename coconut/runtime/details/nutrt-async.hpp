//
// nutrt-async.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>
#include <coconut/runtime/details/nutrt-nucleus.hpp>

#ifndef COCONUT_RUNTIME_ASYNC_HPP
#define COCONUT_RUNTIME_ASYNC_HPP

namespace coconut
{ namespace runtime
{

template <typename PromiseT>
COCONUT_PRIVATE class COCONUT_VISIBLE promise COCONUT_FINAL : public nucleus
{
COCONUT_CLASSDECLARE(coconut.runtime.promise, nucleus.promise)

public:
	promise(const promise &) = delete;
	promise & operator = (const promise &) = delete;
	~promise() { /* NOP */ }
	
	promise(promise && s) noexcept
	: nucleus(classkind_anon, classkind_hidden)
	, ___M_fut{std::move(s.___M_fut)}
	{ /* NOP */ }
	
	promise & operator = (promise && s) noexcept
	{ promise(std::move(s)).swap(*this); return *this; }
	
	explicit promise(std::future<PromiseT> && fut) noexcept
	: nucleus(classkind_anon, classkind_hidden)
	, ___M_fut{std::move(fut)}
	{ /* NOP */ }
	
	PromiseT operator () () noexcept { return ___M_fut.get(); }
	
	virtual Owning<Any> copy() const COCONUT_FINAL_OVERRIDE
	{
		return ptr_create< promise<PromiseT> >(
			std::future<PromiseT>(std::move(___M_fut))
		);
	}
	
private:
	mutable std::future<PromiseT> ___M_fut;
};
	
}} /* EONS */
	
namespace coconut
{ namespace runtime
{ namespace async
{

template <typename FuncT, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
promise<typename std::result_of<FuncT(ArgsT...)>::type> exec(launch_option option, FuncT && func, ArgsT &&... args)
{
	std::launch policy = (std::launch::async | std::launch::deferred);
	switch (option) {
		case launch_any:
#if defined(__clang__)
			policy = std::launch::any;
#endif
		break;
		case launch_async:
			policy = std::launch::async;
		break;
		case launch_deferred:
			policy = std::launch::deferred;
		break;
		default:
			break;
	}
	auto bind = std::bind(std::forward<FuncT>(func), std::forward<ArgsT>(args)...);
	return promise<typename std::result_of<FuncT(ArgsT...)>::type>(
		std::async(policy, std::move(bind))
	);
}

template <typename FuncT, typename... ArgsT>
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void detach(FuncT && func, ArgsT &&... args)
{
	using R = typename std::result_of<FuncT(ArgsT...)>::type;
	auto bind = std::bind(std::forward<FuncT>(func), std::forward<ArgsT>(args)...);
	std::packaged_task<R()> task(std::move(bind));
	std::thread thr(std::move(task));
	thr.detach();
}

// //////////////////////////////////////////////////////////
// @based on thread_pool.hpp, thread_pool.cpp
// Copyright (C) 2015 Tyler Hardin. All rights reserved.
// @see https://github.com/Tyler-Hardin/thread_pool
//

COCONUT_PRIVATE class COCONUT_VISIBLE pool COCONUT_FINAL
{
public:
	pool()
	: ___M_mutex()
	, ___M_cond()
	, ___M_tasks()
	, ___M_threads()
	, ___M_count(0)
	, ___M_stop(false)
	, ___M_run(false)
	{ /* NOP */ }
	
	pool(std::size_t count)
	: ___M_mutex()
	, ___M_cond()
	, ___M_tasks()
	, ___M_threads()
	, ___M_count(count)
	, ___M_stop(false)
	, ___M_run(false)
	{ /* NOP */ }
	
	void set_count(std::size_t count)
	{ ___M_count = count; }
	
	void start()
	{
		bool can_start = false;
		{
			std::unique_lock<std::mutex> lock(___M_mutex);
			can_start = !___M_run && ___M_count && !___M_threads.size();
		}
		if (can_start) {
			for (std::size_t i = 0; i < ___M_count; i++) {
				std::function<void(void)> f = std::bind(&pool::main, this);
				___M_threads.push_back(std::move(std::thread(f)));
			}
			___M_run = true;
		}
	}
	
	bool is_running() { return ___M_run; }
	
	void stop()
	{
		if (___M_run) {
			{
				std::unique_lock<std::mutex> lock(___M_mutex);
				___M_run = false;
				___M_stop = true;
			}
			___M_cond.notify_all();
			
			for (std::vector<std::thread>::iterator it = ___M_threads.begin(); it != ___M_threads.end(); ++it) {
				___M_cond.notify_one();
				(*it).join();
			}
			___M_threads.clear();
			___M_tasks.clear();
		}
	}
	
	~pool() { /* NOP */ }
	
	template <typename FuncT, typename... ArgsT>
	promise<typename std::result_of<FuncT(ArgsT...)>::type> push(FuncT f, ArgsT... args)
	{
		if (!___M_run) { throw; }
		using Ret = typename std::result_of<FuncT(ArgsT...)>::type;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](FuncT && ff, ArgsT... aargs) { p->set_value(ff(aargs...)); };
		auto ret_wrapper = [p]() -> Ret { return p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(___M_mutex);
			___M_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f), args...)
			);
		}
		___M_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	template <typename FuncT>
	promise<typename std::result_of<FuncT()>::type> push(FuncT f)
	{
		if (!___M_run) { throw; }
		using Ret = typename std::result_of<FuncT()>::type;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](FuncT && ff) { p->set_value(ff()); };
		auto ret_wrapper = [p]() -> Ret { return p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(___M_mutex);
			___M_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f))
			);
		}
		___M_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	template <typename... ArgsT>
	promise<void> push(const std::function<void(ArgsT...)> f, ArgsT... args)
	{
		if (!___M_run) { throw; }
		using Ret = void;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](const std::function<Ret(ArgsT...)> & ff, ArgsT... aargs) { ff(aargs...); p->set_value(); };
		auto ret_wrapper = [p]() -> Ret { p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(___M_mutex);
			___M_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f), args...)
			);
		}
		___M_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}
	
	promise<void> push(const std::function<void()> f)
	{
		if (!___M_run) { throw; }
		using Ret = void;
		std::shared_ptr< std::promise<Ret> > p = std::make_shared< std::promise<Ret> >();
		auto task_wrapper = [p](const std::function<Ret()> & ff) { ff(); p->set_value(); };
		auto ret_wrapper = [p]() -> Ret { p->get_future().get(); };
		{
			std::unique_lock<std::mutex> lock(___M_mutex);
			___M_tasks.emplace_back(
				std::async(std::launch::deferred, task_wrapper, std::move(f))
			);
		}
		___M_cond.notify_one();
		return promise<Ret>(
			std::async(std::launch::deferred, ret_wrapper)
		);
	}

protected:
	void main()
	{
		for (;;) {
			std::future<void> fut;
			{
				std::unique_lock<std::mutex> lock(___M_mutex);
				___M_cond.wait(lock, [this] {
					return ___M_stop || !___M_tasks.empty();
				});
				
				if (___M_stop && ___M_tasks.empty()) {
					return;
				} else if (!___M_tasks.empty()) {
					fut = std::move(___M_tasks.front());
					___M_tasks.pop_front();
				}
			}
			fut.get();
		}
	}
	
private:
	std::mutex ___M_mutex;
	std::condition_variable ___M_cond;
	std::deque< std::future<void> > ___M_tasks;
	std::vector<std::thread> ___M_threads;
	
	std::size_t ___M_count;
	bool ___M_stop;
	bool ___M_run;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_ASYNC_HPP */

/* EOF */