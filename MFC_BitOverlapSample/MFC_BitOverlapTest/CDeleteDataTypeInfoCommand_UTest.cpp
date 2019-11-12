#include "gtest/gtest.h"
#include "ACommand.h"
#include "CAddDataTypeInfoCommand.h"
#include "CDataType.h"
#include "CDeleteDataTypeInfoCommand.h"
#include <atlstr.h>

class CDeleteDataTypeInfoCommandAdapter : public CDeleteDataTypeInfoCommand
{
public:
	virtual CArray<CDataType*>* GetReceiver() const { return this->m_Receiver; }
	virtual INT_PTR GetTargetIndex() const { return this->m_TargetIndex; }
};

TEST(CDeleteDataTypeInfoCommand, Constructor_001)
{
	CDeleteDataTypeInfoCommandAdapter CommandAdapter;

	ASSERT_EQ(0, CommandAdapter.GetTargetIndex());
	ASSERT_EQ(NULL, CommandAdapter.GetReceiver());
}

TEST(CDeleteDataTypeInfoCommand, SetTargetIndex_001)
{
	CDeleteDataTypeInfoCommandAdapter CommandAdapter;
	CommandAdapter.SetTargetIndex(1);

	ASSERT_EQ(1, CommandAdapter.GetTargetIndex());
}

TEST(CDeleteDataTypeInfoCommand, SetReceiver_001)
{
	CArray<CDataType*> Receiver;
	CDeleteDataTypeInfoCommandAdapter CommandAdapter;
	CommandAdapter.SetReceiver(&Receiver);

	ASSERT_EQ((VOID*)(&Receiver), (VOID*)(CommandAdapter.GetReceiver()));
}

TEST(CDeleteDataTypeInfoCommand, Execute_001)
{
	CDataType* DataType = new CDataType();
	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(DataType);

	CDeleteDataTypeInfoCommand Command;
	Command.SetReceiver(&Receiver);
	Command.SetTargetIndex(0);
	Command.Execute();

	ASSERT_EQ(0, Receiver.GetCount());
}

TEST(CDeleteDataTypeInfoCommand, Execute_002)
{
	CDataType* DataType1 = new CDataType();
	CDataType* DataType2 = new CDataType();
	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(DataType1);
	Receiver.Add(DataType2);

	CDeleteDataTypeInfoCommand Command;
	Command.SetReceiver(&Receiver);
	Command.SetTargetIndex(0);
	Command.Execute();

	CDataType* Item = Receiver.GetAt(0);

	ASSERT_EQ(1, Receiver.GetCount());
	ASSERT_EQ((VOID*)Item, (VOID*)DataType2);

	//å„èàóù
	delete Item;
}

TEST(CDeleteDataTypeInfoCommand, Execute_003)
{
	CDataType* DataType1 = new CDataType();
	CDataType* DataType2 = new CDataType();
	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(DataType1);
	Receiver.Add(DataType2);

	CDeleteDataTypeInfoCommand Command;
	Command.SetReceiver(&Receiver);
	Command.SetTargetIndex(1);
	Command.Execute();

	CDataType* Item = Receiver.GetAt(0);

	ASSERT_EQ(1, Receiver.GetCount());
	ASSERT_EQ((VOID*)Item, (VOID*)DataType1);

	//å„èàóù
	delete Item;
}
