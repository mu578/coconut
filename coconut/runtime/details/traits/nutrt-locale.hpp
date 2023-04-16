//
// nutrt-locale.hpp
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include <coconut/runtime/details/nutrt-types.hpp>

#ifndef COCONUT_RUNTIME_LOCALE_HPP
#define COCONUT_RUNTIME_LOCALE_HPP

namespace coconut
{ namespace runtime
{ namespace traits
{
		
COCONUT_PRIVATE class COCONUT_VISIBLE locale COCONUT_FINAL
{
COCONUT_RUNTIME_CLASSDECLARE(coconut.runtime.locale, locale)
	
public:
	locale();
	locale(const locale & locl);
	~locale();
	
	locale & operator = (const locale & locl);
	int compare(const locale & other_locl) const;
};

}}} /* EONS */

#endif /* !COCONUT_RUNTIME_LOCALE_HPP */

/* EOF */