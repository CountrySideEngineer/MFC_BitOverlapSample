#pragma once
#include "pch.h"
#include "ACommand.h"

class CBOSCommandManager
{
public:
	CBOSCommandManager();
	virtual ~CBOSCommandManager();

	virtual BOOL ExecuteCommand(ACommand* Command, BOOL DoesStack = TRUE);

protected:
	CList<ACommand*> m_CommandStack;
};

