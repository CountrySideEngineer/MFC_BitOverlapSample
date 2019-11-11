#include "gtest/gtest.h"
#include "ACommand.h"
#include "CAddDataTypeInfoCommand.h"
#include "CDataType.h"
#include "CEditNewDataDlg.h"
#include <atlstr.h>

class CAddDataTypeInfoCommandAdapter : public CAddDataTypeInfoCommand
{
public:
	virtual CArray<CDataType*>* GetReceiver() const { return this->m_Receiver; }
	virtual BOOL AddNewDataTypeWrapper(CDataType* DataType)
	{
		return AddNewDataType(DataType);
	}
};

TEST(CAddDataTypeInfoCommand, Constructor_001)
{
	CAddDataTypeInfoCommandAdapter CommandAdapter;

	ASSERT_EQ(NULL, CommandAdapter.GetReceiver());
}

TEST(CAddDataTypeInfoCommand, SetReceiver_001)
{
	CArray<CDataType*> Receiver;
	CAddDataTypeInfoCommandAdapter CommandAdapter;
	CommandAdapter.SetReceiver(&Receiver);

	ASSERT_EQ((VOID*)(&Receiver), (VOID*)(CommandAdapter.GetReceiver()));
}

TEST(CAddDataTypeInfoCommand, AddNewDataType_001)
{
	CArray<CDataType*> Receiver;
	CAddDataTypeInfoCommandAdapter CommandAdapter;
	CommandAdapter.SetReceiver(&Receiver);

	CDataType DataType;

	ASSERT_TRUE(CommandAdapter.AddNewDataTypeWrapper(&DataType));
	ASSERT_EQ(1, CommandAdapter.GetReceiver()->GetCount());
	ASSERT_NE((VOID*)(&DataType), (VOID*)CommandAdapter.GetReceiver()->GetAt(0));

	//å„èàóù
	CDataType* DataTypeItem = Receiver.GetAt(0);
	delete DataTypeItem;
}

TEST(CAddDataTypeInfoCommand, Execute_001)
{
	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	CDataType DataType;
	CAddDataTypeInfoCommand Command;

	Command.SetDataType(&DataType);
	Command.SetReceiver(&Receiver);
	
	ASSERT_TRUE(Command.Execute());
	ASSERT_EQ(1, Receiver.GetCount());

	//å„èàóù
	CDataType* DataTypeItem = Receiver.GetAt(0);
	delete DataTypeItem;
}
