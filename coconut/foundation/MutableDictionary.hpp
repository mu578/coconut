//
// MutableDictionary.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/foundation/Dictionary.hpp>

#ifndef COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP
#define COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP

namespace coconut
{
	COCONUT_PUBLIC class COCONUT_VISIBLE MutableDictionary COCONUT_FINAL : public Dictionary
	{
	COCONUT_CLASSDECLARE(coconut.MutableDictionary, Object.Dictionary.MutableDictionary)
		
	public:
		MutableDictionary();
		MutableDictionary(const MutableDictionary & dict);
		MutableDictionary & operator = (const MutableDictionary & dict) = default;
		MutableDictionary(const MutableDictionary & dict, CopyOption option);
		MutableDictionary(MutableDictionary && dict) noexcept;
		MutableDictionary(const Dictionary & dict, CopyOption option = CopyNone);
		MutableDictionary(Dictionary && dict) noexcept;
		MutableDictionary(const std::initializer_list< std::pair< Owning<Any>, Owning<Any> > > & args);
		MutableDictionary(const std::initializer_list< std::pair<Any *, Any *> > & args);
		
		template <typename InputIterT>
		MutableDictionary(InputIterT && first, InputIterT && last) :
			Dictionary(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone)
		{ setClassKind(MutableDictionaryClass, true); }
		
		template <typename InputIterT>
		MutableDictionary(InputIterT && first, InputIterT && last, CopyOption option) :
			Dictionary(std::forward<InputIterT>(first), std::forward<InputIterT>(last), option)
		{ setClassKind(MutableDictionaryClass, true); }
		
		template <typename IterKeyT, typename IterValT>
		MutableDictionary(IterKeyT && first_key, IterKeyT && last_key, IterValT && first_val, IterValT && last_val, CopyOption option = CopyNone) :
			Dictionary(std::forward<IterKeyT>(first_key), std::forward<IterKeyT>(last_key), std::forward<IterValT>(first_val), std::forward<IterValT>(last_val), option)
		{ setClassKind(MutableDictionaryClass, true); }
		
		MutableDictionary(const Path & path);
		MutableDictionary(const URL & url);
		virtual ~MutableDictionary();

		virtual void setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
		COCONUT_FINAL_OVERRIDE;
		
		MutableDictionary & setDictionary(MutableDictionary && dict) noexcept;
		MutableDictionary & setDictionary(Dictionary && dict) noexcept;
		
		MutableDictionary & setObjectsFromDictionary(const Dictionary & dict);
		MutableDictionary & setObjectsFromDictionary(const Dictionary & dict, CopyOption option);
		
		template <typename InputIterT>
		MutableDictionary & setObjects(InputIterT && first, InputIterT && last)
		{ return setObjects(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone); }
		
		template <typename InputIterT>
		MutableDictionary & setObjects(InputIterT && first, InputIterT && last, CopyOption option)
		{ return setObjectsFromDictionary({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }
		
		MutableDictionary & setObject(const Owning<Any> & obj, const std::string & utf8_key);
		MutableDictionary & setObject(const Owning<Any> & obj, const Any & key);
		MutableDictionary & setObject(const Owning<Any> & obj, Owning<Any> key);
		
		MutableDictionary & setObject(Owning<Any> obj, const std::string & utf8_key, CopyOption option);
		MutableDictionary & setObject(Owning<Any> obj, const Any & key, CopyOption option);
		MutableDictionary & setObject(Owning<Any> obj, const Owning<Any> key, CopyOption option);
		
		Owning<Any> updateObject(const Owning<Any> & obj, const std::string & utf8_key);
		Owning<Any> updateObject(const Owning<Any> & obj, const Any & key);
		Owning<Any> updateObject(const Owning<Any> & obj, const Owning<Any> & key);
		
		Owning<Any> updateObject(const Owning<Any> & obj, const std::string & utf8_key, CopyOption option);
		Owning<Any> updateObject(const Owning<Any> & obj, const Any & key, CopyOption option);
		Owning<Any> updateObject(const Owning<Any> & obj, const Owning<Any> & key, CopyOption option);
		
		MutableDictionary & addEntriesFromDictionary(const Dictionary & dict);
		MutableDictionary & addEntriesFromDictionary(const Dictionary & dict, CopyOption option);
		
		template <typename InputIterT>
		MutableDictionary & addEntries(InputIterT && first, InputIterT && last) const
		{ return addEntries(std::forward<InputIterT>(first), std::forward<InputIterT>(last), CopyNone); }
		
		template <typename InputIterT>
		MutableDictionary & addEntries(InputIterT && first, InputIterT && last, CopyOption option)
		{ return addEntriesFromDictionary({std::forward<InputIterT>(first), std::forward<InputIterT>(last)}, option); }
		
		MutableDictionary & removeObjectForKey(const std::string & utf8_key);
		MutableDictionary & removeObjectForKey(const Any & key);
		MutableDictionary & removeObjectForKey(const Owning<Any> & key);
		
		MutableDictionary & removeAllObjects();
		MutableDictionary & removeObjectsForKeys(const Array & keys);
		
	public:
		Owning<Any> & operator [] (const std::string & utf8_key);
		Owning<Any> & operator [] (const Any & key);
		Owning<Any> & operator [] (const Owning<Any> & key);
	};
}

#endif /* !COCONUT_FOUNDATION_MUTABLEDICTIONARY_HPP */

/* EOF */