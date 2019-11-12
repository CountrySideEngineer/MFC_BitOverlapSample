#pragma once
class CRegex
{
public:
	BOOL CheckOffset(CString& Target);

protected:
	BOOL RunCheck(CString& Target, CString& Regex);
};

