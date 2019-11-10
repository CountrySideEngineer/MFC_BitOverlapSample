#pragma once
#include "ACommand.h"
#include "CDataType.h"

class CEditDataTypeCommand : public ACommand
{
public:
	CEditDataTypeCommand();
	virtual ~CEditDataTypeCommand() {}

	virtual BOOL Execute();

	virtual VOID SetReceiver(CDataType* Receiver);

protected:
	CDataType* m_Receiver;
};

