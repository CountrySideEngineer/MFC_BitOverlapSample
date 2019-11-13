#pragma once
#include "pch.h"
#include "CDataType.h"

class CCsvFormatter
{
protected:
	static const CString Separator;
	static const CString CrLf;
	static const CString Lf;
	static const CString DoubleQuotation;

public:
	CCsvFormatter() {}
	virtual ~CCsvFormatter() {}

	virtual	CString Format(CArray<CDataType*>* Src);

protected:
	virtual CString Format(CDataType* Src);

};

