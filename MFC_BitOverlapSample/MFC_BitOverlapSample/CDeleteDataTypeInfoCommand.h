#pragma once
#include "ACommand.h"
#include "CDataType.h"

class CDeleteDataTypeInfoCommand : public ACommand
{
public:
	CDeleteDataTypeInfoCommand();
	virtual ~CDeleteDataTypeInfoCommand() {}

	virtual BOOL Execute();

	virtual VOID SetTargetIndex(INT_PTR TargetIndex);
	virtual VOID SetReceiver(CArray<CDataType*>* Receiver);

protected:
	INT_PTR	m_TargetIndex;
	CArray<CDataType*>* m_Receiver;

};

