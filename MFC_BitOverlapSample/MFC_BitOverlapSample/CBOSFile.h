#pragma once
#include "pch.h"
#include "CDataType.h"
#include "CCsvFormatter.h"

class CBOSFile
{
protected:
	const TCHAR Dot = _T('.');
	const TCHAR BackSlash = _T('\\');
	const CString AVAILABLE_FILE_EXTENTION_CSV = _T("csv");

public:
	CBOSFile();
	CBOSFile(CString FilePath);
	virtual ~CBOSFile();

	virtual void WriteData(CArray<CDataType*>* Src);

protected:
	virtual CString GetDataToWrite(CArray<CDataType*>* Src);
	virtual CString ExtractExtention();
	virtual CCsvFormatter* CreateFormatter();

protected:
	CString m_FilePath;
};

