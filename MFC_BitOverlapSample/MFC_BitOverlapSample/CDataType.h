#pragma once
#include <afx.h>

class CDataType
{
public:
	CDataType();
	CDataType(CDataType* Src);
	virtual ~CDataType() {}

	virtual INT_PTR GetDataTypeId() const { return this->m_DataTypeID; }
	virtual VOID SetDataTypeID(INT_PTR DataTypeId) { this->m_DataTypeID = DataTypeId; }
	virtual CString GetDataDesc() const { return this->m_DataDesc; }
	virtual VOID SetDataDesc(CString DataDesc) { this->m_DataDesc = DataDesc; }
	virtual INT_PTR GetDataOffset() const { return this->m_DataOffset; }
	virtual VOID SetDataOffset(INT_PTR DataOffset) { this->m_DataOffset = DataOffset; }
	virtual INT_PTR GetBitOffset() const { return this->m_BitOffset; }
	virtual VOID SetBitOffset(INT_PTR BitOffset) { this->m_BitOffset = BitOffset; }
	virtual CString GetRemarks() const { return this->m_Remarks; }
	virtual VOID SetRemarks(CString Remarks) { this->m_Remarks = Remarks; }

protected:
	INT_PTR	m_DataTypeID;
	CString m_DataDesc;
	INT_PTR m_DataOffset;
	INT_PTR m_BitOffset;
	CString m_Remarks;

};

