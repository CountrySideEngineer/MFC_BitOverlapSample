#pragma once
#include <afxstr.h>

const CString DataTypeName_NONE = _T("");
const CString DataTypeName_BOOL = _T("BOOL");
const CString DataTypeName_BYTE = _T("BYTE");
const CString DataTypeName_WORD = _T("WORD");
const CString DataTypeName_DWORD = _T("DWORD");

class CDataTypeInfo
{
public:
	enum {
		DATA_TYPE_INFO_NAME_NONE = 0,
		DATA_TYPE_INFO_NAME_BOOL,
		DATA_TYPE_INFO_NAME_BYTE,
		DATA_TYPE_INFO_NAME_WORD,
		DATA_TYPE_INFO_NAME_DWORD,
		DATA_TYPE_INFO_NAME_MAX,
	};

	enum {
		DATA_TYPE_INFO_BIT_LEN_NONE = 0,
		DATA_TYPE_INFO_BIT_LEN_BOOL = 1,
		DATA_TYPE_INFO_BIT_LEN_BYTE = 8,
		DATA_TYPE_INFO_BIT_LEN_WORD = 16,
		DATA_TYPE_INFO_BIT_LEN_DWORD = 32,
	};

protected:
	CDataTypeInfo() {}

public:
	virtual ~CDataTypeInfo() {}

	static CDataTypeInfo* GetInstance();

	CString GetTypeName(INT_PTR Index) { return this->m_DataTypeNameArray[Index]; }
	INT_PTR GetBitLen(INT_PTR Index) { return this->m_DataBitLenArray[Index]; }

protected:
	CString m_DataTypeNameArray[DATA_TYPE_INFO_NAME_MAX] = {
		DataTypeName_NONE,
		DataTypeName_BOOL,
		DataTypeName_BYTE,
		DataTypeName_WORD,
		DataTypeName_DWORD
	};

	INT_PTR m_DataBitLenArray[DATA_TYPE_INFO_NAME_MAX] = {
		DATA_TYPE_INFO_BIT_LEN_NONE,
		DATA_TYPE_INFO_BIT_LEN_BOOL,
		DATA_TYPE_INFO_BIT_LEN_BYTE,
		DATA_TYPE_INFO_BIT_LEN_WORD,
		DATA_TYPE_INFO_BIT_LEN_DWORD
	};
};

