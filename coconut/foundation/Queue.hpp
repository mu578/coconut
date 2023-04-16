//
// Queue.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/Object.hpp>

#ifndef COCONUT_FOUNDATION_QUEUE_HPP
#define COCONUT_FOUNDATION_QUEUE_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE Queue COCONUT_FINAL : public Object
	{
	COCONUT_CLASSDECLARE(coconut.Queue, Object.Queue)
		
	public:
		Queue();
		Queue(const Queue & que);
		Queue & operator = (const Queue & que) = default;
		Queue(Queue && que) noexcept;
		virtual ~Queue();

	public:
		virtual Owning<Any> copy() const
		COCONUT_FINAL_OVERRIDE;
		
		virtual std::size_t size() const
		COCONUT_FINAL_OVERRIDE;
	
	public:
		void enqueue(const Owning<Any> & obj);
		const Owning<Any> dequeue();
		const Owning<Any> peek() const;
		
		void clear();
		
	private:
		typedef std::queue< Owning<Any> > impl_trait;

	public:
		typedef impl_trait::container_type::iterator iterator;
		typedef impl_trait::container_type::const_iterator const_iterator;
		
		typedef impl_trait::container_type::reverse_iterator reverse_iterator;
		typedef impl_trait::container_type::const_reverse_iterator const_reverse_iterator;
		
		typedef impl_trait::container_type::value_type value_type;
		typedef impl_trait::container_type::size_type size_type;
		typedef impl_trait::container_type::difference_type difference_type;
		
		typedef impl_trait::container_type::reference reference;
		typedef impl_trait::container_type::const_reference const_reference;
		typedef impl_trait::container_type::pointer pointer;
		typedef impl_trait::container_type::const_pointer const_pointer;
		
		typedef impl_trait::container_type::allocator_type allocator_type;
		
	public:
		iterator begin();
		iterator end();
		
		const_iterator begin() const;
		const_iterator end() const;
		
		const_iterator cbegin() const;
		const_iterator cend() const;
		
		reverse_iterator rbegin();
		reverse_iterator rend();
		
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
		
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
		
	private:
		impl_trait ___M_impl;
	};
}

#endif /* !COCONUT_FOUNDATION_QUEUE_HPP */

/* EOF */