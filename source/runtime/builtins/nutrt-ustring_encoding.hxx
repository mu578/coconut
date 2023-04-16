//
// nutrt-ustring_encoding.hxx
//
// Copyright (C) 2015-2016 mu578. All rights reserved.
//

#include "unicode/coll.h"
#include "unicode/ucsdet.h"

namespace coconut
{ namespace runtime
{ namespace builtins
{

namespace
{
	
static struct { encoding_option encoding; const char * codepage; } const ___F_ustring_codepages[] =
{
	{ encoding_utf8, "UTF-8" },
	
	{ encoding_utf16, "UTF-16LE" },
	{ encoding_utf16be, "UTF-16BE" },
	{ encoding_utf16le, "UTF-16LE" },

	{ encoding_utf32, "UTF-32" },
	{ encoding_utf32be, "UTF-32BE" },
	{ encoding_utf32le, "UTF-32LE" },

	{ encoding_ucs2, "UTF-16" },
	{ encoding_ucs2be, "UTF-16BE" },
	{ encoding_ucs2le, "UTF-16LE" },

	{ encoding_ucs4, "UTF-32" },
	{ encoding_ucs4be, "UTF-32BE" },
	{ encoding_ucs4le, "UTF-32LE" },
	
	{ encoding_shiftjis, "Shift_JIS" },
	
	{ encoding_iso2022jp, "ISO-2022-JP" },
	{ encoding_iso2022cn, "ISO-2022-CN" },
	{ encoding_iso2022kr, "ISO-2022-KR" },
	
	{ encoding_gb18030, "GB18030" },
	{ encoding_big5, "Big5" },
	
	{ encoding_eucjp, "EUC-JP" },
	{ encoding_euckr, "EUC-KR" },
	
	{ encoding_iso88591, "ISO-8859-1" },
	{ encoding_iso88592, "ISO-8859-2" },
	{ encoding_iso88595, "ISO-8859-5" },
	{ encoding_iso88596, "ISO-8859-6" },
	{ encoding_iso88597, "ISO-8859-7" },
	{ encoding_iso88598, "ISO-8859-8" },
	{ encoding_iso88598i, "ISO-8859-8-I" },
	{ encoding_iso88599, "ISO-8859-9" },
	
	{ encoding_windows1250, "windows-1250" },
	{ encoding_windows1251, "windows-1251" },
	{ encoding_windows1252, "windows-1252" },
	{ encoding_windows1253, "windows-1253" },
	{ encoding_windows1254, "windows-1254" },
	{ encoding_windows1255, "windows-1255" },
	{ encoding_windows1256, "windows-1256" },
	
	{ encoding_koi8r, "KOI8-R" },
	
	{ encoding_ibm420, "IBM420_ltr" },
	{ encoding_ibm420ltr, "IBM420_ltr" },
	{ encoding_ibm420rtl, "IBM420_rtl" },
	
	{ encoding_ibm424, "IBM424_ltr" },
	{ encoding_ibm424ltr, "IBM424_ltr" },
	{ encoding_ibm424rtl, "IBM424_rtl" },
	{ 10000, nullptr }
};
	
} /* EONS */
	
COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ___F_ustring_syscodepages(std::vector<std::string> & codepages)
{
	UErrorCode status = U_ZERO_ERROR;
	UCharsetDetector * dctr = ucsdet_open(&status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		return false;
	}
	
	status = U_ZERO_ERROR;
	UEnumeration * all = ucsdet_getAllDetectableCharsets(dctr, &status);
	if (U_FAILURE(status)) {
		uenum_close(all);
		ucsdet_close(dctr);
		return false;
	}
	
	status = U_ZERO_ERROR;
	std::int32_t sz = uenum_count(all, &status);
	if (U_FAILURE(status)) {
		uenum_close(all);
		ucsdet_close(dctr);
		return false;
	}
	std::int32_t ite_M_len = 0;
	const char * item = nullptr;
	for (std::int32_t i = 0; i < sz; i++) {
		ite_M_len = 0;
		status = U_ZERO_ERROR;
		item = uenum_next(all, &ite_M_len, &status);
		if (U_FAILURE(status)) {
			codepages.clear();
			break;
		}
		if (item && ite_M_len) {
			codepages.push_back(std::string(item, static_cast<std::size_t>(ite_M_len)));
		}
	}
	if (codepages.size()) {
		std::sort(codepages.begin(), codepages.end());
	}
	uenum_close(all);
	ucsdet_close(dctr);
	
	return (codepages.size() > 0);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
void ___F_ustring_getcodepages(std::set<std::string> & codepages)
{
	std::size_t i = 0;
	do {
		codepages.insert({___F_ustring_codepages[i].codepage});
		++i;
	} while(nullptr != ___F_ustring_codepages[i].codepage);
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ___F_ustring_getcodepage(encoding_option encoding)
{
	std::size_t i = 0;
	do {
		if (___F_ustring_codepages[i].encoding == encoding) {
			return {___F_ustring_codepages[i].codepage};
		}
		++i;
	} while(nullptr != ___F_ustring_codepages[i].codepage);
	return {"UTF-8"};
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool ___F_ustring_getencoding(const char * codepage, encoding_option & encoding)
{
	std::size_t i = 0;
	encoding = encoding_auto;
	do {
		std::string cp1(___F_ustring_codepages[i].codepage);
		std::string cp2(codepage);
		if (0 == algorithms::icmp(cp1, cp2)) {
			encoding = ___F_ustring_codepages[i].encoding;
			return true;
		}
		++i;
	} while(nullptr != ___F_ustring_codepages[i].codepage);
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
std::string ___F_ustring_detectcodepage(const char * in, std::size_t len, float & confidence)
{
	std::string result{u8"UTF-8"};
	const char * res;
	UCharsetDetector * dctr;
	const UCharsetMatch * chmt;
	const UCharsetMatch ** chmts;
	UErrorCode status = U_ZERO_ERROR;
	
	dctr = ucsdet_open(&status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return result;
	}
	
	status = U_ZERO_ERROR;
	ucsdet_setText(dctr, in, weak_cast<std::int32_t>(len), &status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return result;
	}
	
	std::size_t i = 0, idx = 0, best = 0;
	std::int32_t c = 0, num;
	
	status = U_ZERO_ERROR;
	chmts = ucsdet_detectAll(dctr, &num, &status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return result;
	}
	
	for (i = 0; i < num; i++) {
		status = U_ZERO_ERROR;
		c = ucsdet_getConfidence(chmts[i], &status);
		if (U_FAILURE(status)) {
			ucsdet_close(dctr);
			confidence = 0.0;
			return result;
		}
		if (c > best) {
			best = c;
			idx = i;
		}
	}
	if (best) {
		status = U_ZERO_ERROR;
		res = ucsdet_getName(chmts[idx], &status);
		if (res == NULL || U_FAILURE(status)) {
			ucsdet_close(dctr);
			confidence = 0.0;
			return {};
		}
		result = res;
		confidence = static_cast<float>(best) / 100.0;
		return result;
	}
	
	status = U_ZERO_ERROR;
	chmt = ucsdet_detect(dctr, &status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return result;
	}
	
	status = U_ZERO_ERROR;
	res = ucsdet_getName(chmt, &status);
	if (res == NULL || U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return {};
	}
	result = res;
	c = ucsdet_getConfidence(chmt, &status);
	if (U_FAILURE(status)) {
		ucsdet_close(dctr);
		confidence = 0.0;
		return result;
	}
	confidence = static_cast<float>(c) / 100.0;
	
	ucsdet_close(dctr);
	
	return result;
}

}}} /* EONS */

/* EOF */