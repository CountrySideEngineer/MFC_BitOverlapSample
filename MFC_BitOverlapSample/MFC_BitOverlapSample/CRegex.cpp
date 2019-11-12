#include "pch.h"
#include "CRegex.h"
#include <regex>

/**
 *	引数で指定された文字列が、オフセットのフォーマット(xxx.x)に一致しているか
 *	否かを判定する。
 *
 *	@param[in]	Target	確認対象の文字列
 *	@return	Targetがオフセットのフォーマットに一致していた場合にはTRUEを、
 *			一致していない場合にはFALSEを返す。
 */
BOOL CRegex::CheckOffset(CString& Target)
{
	CString Regex = _T("[0-9]{1,}[\.]?[0-9]");

	return this->RunCheck(Target, Regex);
}

/**
 *	正規表現と一致するか否かを確認する。
 *
 *	@param[in]	Target	確認対象の文字列
 *	@param[in]	Regex	正規表現の検索文字列
 *	@return	正規表現に一致した場合にはTRUE、一致しなかった場合にはFALSEを返す。
 */
BOOL CRegex::RunCheck(CString& Target, CString& Regex)
{
	USES_CONVERSION;
	std::string TargetString = T2A(Target.GetBuffer());
	std::string RegExString = T2A(Regex.GetBuffer());
	std::regex RegExPattern(RegExString);

	BOOL IsMatch = std::regex_match(TargetString.c_str(), RegExPattern);
	return IsMatch;
}


