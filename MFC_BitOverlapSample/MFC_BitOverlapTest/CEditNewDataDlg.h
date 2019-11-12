#pragma once
#include "CDataType.h"

class CEditNewDataDlg
{
public:
	CEditNewDataDlg(CWnd* parent);
	virtual ~CEditNewDataDlg();

	virtual void SetDataTypeStore(CDataType* DataType) { this->m_DataTypeBuff = DataType; }
	virtual INT_PTR DoModal();

public:
	static INT_PTR DoModalResult;

protected:
	CDataType* m_DataTypeBuff;

};

