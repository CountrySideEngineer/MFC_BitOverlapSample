#pragma once
#include "pch.h"
#include "ACommand.h"

class CBOSCommandManager
{
public:
	CBOSCommandManager();
	virtual ~CBOSCommandManager();

	virtual BOOL ExecuteCommand(ACommand* Command, BOOL DoesStack = TRUE);

	virtual CList<ACommand*>* GetCommandStack() { return &(this->m_CommandStack); }

protected:
	CList<ACommand*> m_CommandStack;
};

