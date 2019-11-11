#include "gtest/gtest.h"
#include "ACommand.h"
#include "CBOSCommandManager.h"
#include <atlstr.h>

/**
 *	テスト用のサンプルクラス
 */
class CCommandForCommandManagerUTest : public ACommand
{
public:
	CCommandForCommandManagerUTest()
		: m_ExecuteCalledCount(0)
		, m_ExecuteReturn(FALSE)
	{}

	virtual BOOL Execute()
	{
		this->m_ExecuteCalledCount++;

		return this->m_ExecuteReturn;
	}

	virtual INT_PTR GetExecuteCalledCount() { return this->m_ExecuteCalledCount; }
	virtual VOID SetExecuteCalledCount(INT_PTR ExecuteCalledCount) { this->m_ExecuteCalledCount = ExecuteCalledCount; }
	virtual BOOL GetExecuteReturn() { return this->m_ExecuteReturn; }
	virtual VOID SetExecuteReturn(BOOL ExecuteReturn) { this->m_ExecuteReturn = ExecuteReturn; }

protected:
	INT_PTR m_ExecuteCalledCount;
	BOOL m_ExecuteReturn;
};

TEST(CBOSCommandManager, Constructor_001)
{
	CBOSCommandManager CommandManager;

	ASSERT_EQ(0, CommandManager.GetCommandStack()->GetCount());
}

TEST(CBOSCommandManager, Execute_001)
{
	CBOSCommandManager CommandManager;
	CCommandForCommandManagerUTest* Command = new CCommandForCommandManagerUTest();
	Command->SetExecuteReturn(TRUE);

	ASSERT_TRUE(CommandManager.ExecuteCommand(Command));
	ASSERT_EQ(1, CommandManager.GetCommandStack()->GetCount());
	ACommand* StackCommand = CommandManager.GetCommandStack()->GetHead();
	ASSERT_EQ(Command, StackCommand);
}

TEST(CBOSCommandManager, Execute_002)
{
	CBOSCommandManager CommandManager;
	CCommandForCommandManagerUTest* Command = new CCommandForCommandManagerUTest();
	Command->SetExecuteReturn(FALSE);

	ASSERT_FALSE(CommandManager.ExecuteCommand(Command));
	ASSERT_EQ(0, CommandManager.GetCommandStack()->GetCount());

	delete Command;
}

TEST(CBOSCommandManager, Execute_003)
{
	CBOSCommandManager CommandManager;
	CCommandForCommandManagerUTest* Command = new CCommandForCommandManagerUTest();
	Command->SetExecuteReturn(TRUE);

	ASSERT_TRUE(CommandManager.ExecuteCommand(Command, FALSE));
	ASSERT_EQ(0, CommandManager.GetCommandStack()->GetCount());

	delete Command;
}

TEST(CBOSCommandManager, Execute_004)
{
	CBOSCommandManager CommandManager;
	CCommandForCommandManagerUTest* Command = new CCommandForCommandManagerUTest();
	Command->SetExecuteReturn(TRUE);

	ASSERT_TRUE(CommandManager.ExecuteCommand(Command, TRUE));
	ASSERT_EQ(1, CommandManager.GetCommandStack()->GetCount());
	ACommand* StackCommand = CommandManager.GetCommandStack()->GetHead();
	ASSERT_EQ(Command, StackCommand);
}
