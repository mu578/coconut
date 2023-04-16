//
// Features.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/Types.hpp>

#ifndef COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP
#define COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP

namespace coconut
{		
	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_conforms_to(const T2 & r, std::false_type) -> bool
	{ const T1 * ptr = dynamic_cast<const T1 *>(std::addressof(r)); return (ptr != nullptr); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_conforms_to(Owning<T2> const & r, std::true_type) -> bool
	{ if (r) { const T1 * ptr = dynamic_cast<const T1 *>(std::addressof(*r)); return (ptr != nullptr); }; return false; }
	
	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_kind_of(const T2 & r, std::false_type) -> bool
	{ return r . template isKindOf<T1>(); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_kind_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isKindOf<T1>()); }
	
	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_subclass_of(const T2 & r, std::false_type) -> bool
	{ return r . template isSubclassOf<T1>(); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_subclass_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isSubclassOf<T1>()); }

	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_member_of(const T2 & r, std::false_type) -> bool
	{ return r . template isMemberOf<T1>(); }
	
	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_member_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isMemberOf<T1>()); }

	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_ancestor_of(const T2 & r, std::false_type) -> bool
	{ return r . template isAncestorOf<T1>(); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_ancestor_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isAncestorOf<T1>()); }

	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_parent_of(const T2 & r, std::false_type) -> bool
	{ return r . template isParenOf<T1>(); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_parent_of(Owning<T2> const & r, std::true_type) -> bool
	{ return (r && r -> template isParenOf<T1>()); }
	
	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_thus(const T2 & r, std::false_type)
		-> T1 &
	{ return ref_cast<T1>(r); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_thus(Owning<T2> const & r, std::true_type)
		-> T1 &
	{ return (*(ptr_cast<T1>(r))); }

	template <typename T1, typename T2
		, typename std::enable_if<
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_then(const T2 & r, std::false_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r.itself()); }
	
	template <typename T1, typename T2>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_then(Owning<T2> const & r, std::true_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r); }

	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value &&
			!arg_is_raw_ptr<T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_copy(const T2 & r, std::false_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r.kindCopy()); }
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, T1>::value &&
			std::is_base_of<Any, T2>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_copy(Owning<T2> const & r, std::true_type)
		-> Owning<T1>
	{ return ptr_cast<T1>(r->kindCopy()); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Array>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableArray>::value ||
			std::is_same<typename std::decay<CollT>::type, OrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableOrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, Set>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableSet>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	void ___F_enumerate_dispatch_aliasing
	(
		  const CollT & r
		, const std::function<void(const Owning<Any> & obj)> & func
		, EnumerationOptions options
	)
	{
		ref_cast<CollT>(r).enumerateObjectsUsingFunction(func, options);
	}

	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Dictionary>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableDictionary>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch_aliasing
	(
	 	  const CollT & r
		, const std::function<void(const Owning<Any> & key)> & func
		, EnumerationOptions options
	) -> void
	{
		ref_cast<CollT>(r).enumerateKeysUsingFunction(func, options);
	}
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Dictionary>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableDictionary>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch_aliasing
	(
		const CollT & r,
		const std::function<void(const Owning<Any> & key, const Owning<Any> & obj)> & func,
		EnumerationOptions options
	 ) -> void
	{
		ref_cast<CollT>(r).enumerateKeysAndObjectsUsingFunction(func, options);
	}
	
	template <typename TypeT, typename CollT>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch
	(
		  const CollT & r
		, const std::function<void(const Owning<Any> & key, const Owning<Any> & obj)> & func
		, EnumerationOptions options
	) -> void
	{ ___F_enumerate_dispatch_aliasing<TypeT, CollT>(r, func, options); }

	template <typename TypeT, typename CollT>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch
	(
		  const CollT & r
		, const std::function<void(const Owning<Any> & obj)> & func
		, EnumerationOptions options
	) -> void
	{ ___F_enumerate_dispatch_aliasing<TypeT, CollT>(r, func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Array>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableArray>::value ||
			std::is_same<typename std::decay<CollT>::type, OrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableOrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, Set>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableSet>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch
	(
	 	  const CollT & r
	 	, const std::function<void(const Owning<Any> & obj, bool & stop)> & func
	 	, EnumerationOptions options
	) -> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Array>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableArray>::value ||
			std::is_same<typename std::decay<CollT>::type, OrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableOrderedSet>::value ||
			std::is_same<typename std::decay<CollT>::type, Set>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableSet>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch
	(
	 	  const CollT & r
	 	, const std::function<void(const Owning<Any> & obj, std::size_t index, bool & stop)> & func
	 	, EnumerationOptions options
	) -> void
	{ ref_cast<TypeT>(r).enumerateObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT,
		typename std::enable_if<
			std::is_same<typename std::decay<CollT>::type, Dictionary>::value ||
			std::is_same<typename std::decay<CollT>::type, MutableDictionary>::value
		>::type* = nullptr
	>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate_dispatch
	(
		  const CollT & r
	 	, const std::function<void(const Owning<Any> & key, const Owning<Any> & obj, bool & stop)> & func
	 	, EnumerationOptions options
	) -> void
	{ ref_cast<TypeT>(r).enumerateKeysAndObjectsUsingFunction(func, options); }
	
	template <typename TypeT, typename CollT, typename FuncT>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate(const CollT & r, const FuncT & func, EnumerationOptions options, std::false_type)
		-> void
	{ ___F_enumerate_dispatch<TypeT>(r, func, options); }
	
	template <typename TypeT, typename CollT, typename FuncT>
	COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
	auto ___F_enumerate(Owning<CollT> const & r, const FuncT & func, EnumerationOptions options, std::true_type)
		-> void
	{ if (r) { ___F_enumerate_dispatch<TypeT>(*r, func, options); }; }

	template <typename RetT, typename ErrT>
	COCONUT_PUBLIC class COCONUT_VISIBLE OptionalReturn COCONUT_FINAL
	{
	public:
		OptionalReturn(const OptionalReturn &) = delete;
		OptionalReturn & operator = (const OptionalReturn &) = delete;
		~OptionalReturn() { /* NOP */ }
		
		OptionalReturn(OptionalReturn && oret) noexcept
		: ___M_success{std::move(oret.___M_success)}
		, ___M_error{std::move(oret.___M_error)}
		, ___M_valid{oret.___M_valid}
		{ /* NOP */ }
		
		OptionalReturn & operator = (OptionalReturn && oret) noexcept
		{ OptionalReturn(std::move(oret)).swap(*this); return *this; }
		
		explicit OptionalReturn()
		: ___M_success{}
		, ___M_error{}
		, ___M_valid(false)
		{ /* NOP */ }
		
		const RetT & success() const { return ___M_success; }
		const ErrT & error() const { return ___M_error; }
		
		operator bool () const { return ___M_valid; }
		const RetT & operator () () const { return success(); }
		const ErrT & operator ~ () const { return error(); }
		
		void setSuccess(const RetT & success)
		{ ___M_success = success; ___M_error = {}; ___M_valid = true; }
		
		void setError(const ErrT & error)
		{ ___M_success = {}; ___M_error = error; ___M_valid = false; }

	private:
		RetT ___M_success;
		ErrT ___M_error;
		bool ___M_valid;
	};

	template <typename T1, typename T2>
	inline auto ConformsTo(T2 && r) -> bool
	{ return ___F_conforms_to<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto KindOf(T2 && r) -> bool
	{ return ___F_kind_of<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }

	template <typename T1, typename T2>
	inline auto SubclassOf(T2 && r) -> bool
	{ return ___F_subclass_of<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto MemberOf(T2 && r) -> bool
	{ return ___F_member_of<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto AncestorOf(T2 && r) -> bool
	{ return ___F_ancestor_of<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto isParentOf(T2 && r) -> bool
	{ return ___F_parent_of<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(void * no_param = nullptr)
		-> Owning<TypeT>
	{ COCONUT_UNUSED(no_param); return ptr_create<TypeT>(); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const TypeT & arg)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(arg); }
	
	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, typename std::decay<T2>
		>::value>::type* = nullptr
	>
	inline auto With(T2 && arg)
		-> Owning<T1>
	{ return ptr_create<T1>(std::move(arg)); }

	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const std::initializer_list< Owning<Any> > & args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(args); }
	
	template <typename TypeT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(args); }

	template <typename TypeT, typename... ArgsT,
		typename std::enable_if<std::is_base_of<Any, TypeT>::value>::type* = nullptr
	>
	inline auto With(ArgsT &&... args)
		-> Owning<TypeT>
	{ return ptr_create<TypeT>(std::forward<ArgsT>(args)...); }
	
	template <typename T1, typename T2>
	inline auto Thus(T2 && r)
		-> decltype(___F_thus<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}))
	{ return ___F_thus<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }
	
	template <typename T1, typename T2>
	inline auto Then(T2 && r)
		-> decltype(___F_then<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}))
	{ return ___F_then<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }

	template <typename T1, typename T2,
		typename std::enable_if<
			std::is_base_of<Any, typename std::decay<T2>::type
		>::value>::type* = nullptr
	>
	inline auto Shift(T2 && r) -> decltype(std::move(r))
	{ return std::move(r); }
	
	template <typename T1, typename T2>
	inline auto Copy(T2 && r)
		-> Owning<T1>
	{ return ___F_copy<T1>(r, tag_is_shared_ptr<typename std::decay<T2>::type>{}); }

	template <typename TypeT, typename CollT, typename FuncT>
	inline auto Enumerate(CollT && r, FuncT && func, EnumerationOptions options = EnumerationDefault)
		-> void
	{ ___F_enumerate<TypeT>(r, func, options, tag_is_shared_ptr<typename std::decay<CollT>::type>{}); }
}

#endif /* !COCONUT_RUNTIME_TO_FOUNDATION_FEATURES_HPP */

/* EOF */