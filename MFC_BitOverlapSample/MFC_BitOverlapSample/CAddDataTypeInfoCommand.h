#pragma once
#include "ACommand.h"
#include "CDataType.h"

class CAddDataTypeInfoCommand : public ACommand
{
public:
	CAddDataTypeInfoCommand();
	virtual ~CAddDataTypeInfoCommand() {}

	virtual BOOL Execute();

	virtual VOID SetReceiver(CArray<CDataType*>* Receiver);

protected:
	virtual BOOL AddNewDataType(CDataType* DataType);

protected:
	CArray<CDataType*>* m_Receiver;
};

