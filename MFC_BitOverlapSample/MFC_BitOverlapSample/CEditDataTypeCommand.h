#pragma once
#include "ACommand.h"
#include "CDataType.h"

class CEditDataTypeCommand : public ACommand
{
public:
	CEditDataTypeCommand();
	virtual ~CEditDataTypeCommand() {}

	virtual BOOL Execute();

	virtual VOID SetReceiver(CArray<CDataType*>* Receiver);
	virtual VOID SetDataType(CDataType* DataType);
	virtual VOID SetDataTypeIndex(INT_PTR DataTypeIndex);

protected:
	CArray<CDataType*>* m_Receiver;
	CDataType*	m_DataType;
	INT_PTR		m_DataTypeIndex;
};

