#include "gtest/gtest.h"
#include "CDataType.h"
#include "ACommand.h"
#include "CEditDataTypeCommand.h"
#include <atlstr.h>

class CEditDataTypeCommandAdapter : public CEditDataTypeCommand
{
public:
	CEditDataTypeCommandAdapter() : CEditDataTypeCommand() {}

	virtual CArray<CDataType*>* GetReceiver() const { return this->m_Receiver; }
	virtual CDataType* GetDataType() const { return this->m_DataType; }
	virtual INT_PTR GetDataTypeIndex() const { return this->m_DataTypeIndex; }

};

TEST(CEditDataTypeCommand, Constructor_001)
{
	CEditDataTypeCommandAdapter Command;

	ASSERT_EQ(NULL, Command.GetReceiver());
	ASSERT_EQ(NULL, Command.GetDataType());
	ASSERT_EQ(0, Command.GetDataTypeIndex());
}

TEST(CEditDataTypeCommand, SetReceiver_001)
{
	CArray<CDataType*> Receiver;
	CEditDataTypeCommandAdapter Command;

	Command.SetReceiver(&Receiver);

	ASSERT_EQ((VOID*)(&Receiver), Command.GetReceiver());
}

TEST(CEditDataTypeCommand, SetDataType_001)
{
	CDataType DataType;
	CEditDataTypeCommandAdapter Command;
	Command.SetDataType(&DataType);

	ASSERT_EQ((VOID*)(&DataType), Command.GetDataType());
}

TEST(CEditDataTypeCommand, SetDataTypeIndex_001)
{
	CEditDataTypeCommandAdapter Command;
	Command.SetDataTypeIndex(0);

	ASSERT_EQ(0, Command.GetDataTypeIndex());
}

TEST(CEditDataTypeCommand, SetDataTypeIndex_002)
{
	CEditDataTypeCommandAdapter Command;
	Command.SetDataTypeIndex(1);

	ASSERT_EQ(1, Command.GetDataTypeIndex());
}

TEST(CEditDataTypeCommand, Execute_001)
{
	CDataType* BaseDataType1 = new CDataType();
	BaseDataType1->SetDataTypeID(1);
	BaseDataType1->SetDataDesc(_T("DataDesc1"));
	BaseDataType1->SetDataOffset(11);
	BaseDataType1->SetBitOffset(12);
	BaseDataType1->SetRemarks(_T("Remaks1"));

	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(BaseDataType1);

	CDataType* DataType = new CDataType();
	DataType->SetDataTypeID(2);
	DataType->SetDataDesc(_T("DataDesc2"));
	DataType->SetDataOffset(21);
	DataType->SetBitOffset(22);
	DataType->SetRemarks(_T("Remaks2"));

	CEditDataTypeCommandAdapter Command;
	Command.SetReceiver(&Receiver);
	Command.SetDataTypeIndex(0);
	Command.SetDataType(DataType);

	ASSERT_TRUE(Command.Execute());

	CDataType* Item = Receiver.GetAt(0);
	ASSERT_EQ(1, Receiver.GetCount());
	ASSERT_EQ(2, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc2"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks2"), Item->GetRemarks());
	ASSERT_EQ(21, Item->GetDataOffset());
	ASSERT_EQ(22, Item->GetBitOffset());

	//å„èàóù
	delete DataType;
	delete Item;
}

TEST(CEditDataTypeCommand, Execute_002)
{
	CDataType* BaseDataType1 = new CDataType();
	BaseDataType1->SetDataTypeID(1);
	BaseDataType1->SetDataDesc(_T("DataDesc1"));
	BaseDataType1->SetDataOffset(11);
	BaseDataType1->SetBitOffset(12);
	BaseDataType1->SetRemarks(_T("Remaks1"));

	CDataType* BaseDataType2 = new CDataType();
	BaseDataType2->SetDataTypeID(2);
	BaseDataType2->SetDataDesc(_T("DataDesc2"));
	BaseDataType2->SetDataOffset(21);
	BaseDataType2->SetBitOffset(22);
	BaseDataType2->SetRemarks(_T("Remaks2"));

	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(BaseDataType1);
	Receiver.Add(BaseDataType2);

	CDataType* DataType = new CDataType();
	DataType->SetDataTypeID(3);
	DataType->SetDataDesc(_T("DataDesc3"));
	DataType->SetDataOffset(31);
	DataType->SetBitOffset(32);
	DataType->SetRemarks(_T("Remaks3"));

	CEditDataTypeCommandAdapter Command;
	Command.SetReceiver(&Receiver);
	Command.SetDataTypeIndex(0);
	Command.SetDataType(DataType);

	ASSERT_TRUE(Command.Execute());

	CDataType* Item = Receiver.GetAt(1);
	ASSERT_EQ(2, Receiver.GetCount());
	ASSERT_EQ(2, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc2"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks2"), Item->GetRemarks());
	ASSERT_EQ(21, Item->GetDataOffset());
	ASSERT_EQ(22, Item->GetBitOffset());

	Item = Receiver.GetAt(0);
	ASSERT_EQ(3, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc3"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks3"), Item->GetRemarks());
	ASSERT_EQ(31, Item->GetDataOffset());
	ASSERT_EQ(32, Item->GetBitOffset());

	//å„èàóù
	delete BaseDataType2;
	delete DataType;
	delete Item;
}

TEST(CEditDataTypeCommand, Execute_003)
{
	CDataType* BaseDataType1 = new CDataType();
	BaseDataType1->SetDataTypeID(1);
	BaseDataType1->SetDataDesc(_T("DataDesc1"));
	BaseDataType1->SetDataOffset(11);
	BaseDataType1->SetBitOffset(12);
	BaseDataType1->SetRemarks(_T("Remaks1"));

	CDataType* BaseDataType2 = new CDataType();
	BaseDataType2->SetDataTypeID(2);
	BaseDataType2->SetDataDesc(_T("DataDesc2"));
	BaseDataType2->SetDataOffset(21);
	BaseDataType2->SetBitOffset(22);
	BaseDataType2->SetRemarks(_T("Remaks2"));

	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(BaseDataType1);
	Receiver.Add(BaseDataType2);

	CDataType* DataType = new CDataType();
	DataType->SetDataTypeID(3);
	DataType->SetDataDesc(_T("DataDesc3"));
	DataType->SetDataOffset(31);
	DataType->SetBitOffset(32);
	DataType->SetRemarks(_T("Remaks3"));

	CEditDataTypeCommandAdapter Command;
	Command.SetReceiver(&Receiver);
	Command.SetDataTypeIndex(1);
	Command.SetDataType(DataType);

	ASSERT_TRUE(Command.Execute());

	CDataType* Item = Receiver.GetAt(0);
	ASSERT_EQ(2, Receiver.GetCount());
	ASSERT_EQ(1, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc1"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks1"), Item->GetRemarks());
	ASSERT_EQ(11, Item->GetDataOffset());
	ASSERT_EQ(12, Item->GetBitOffset());

	Item = Receiver.GetAt(1);
	ASSERT_EQ(3, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc3"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks3"), Item->GetRemarks());
	ASSERT_EQ(31, Item->GetDataOffset());
	ASSERT_EQ(32, Item->GetBitOffset());

	//å„èàóù
	delete BaseDataType1;
	delete DataType;
	delete Item;
}

TEST(CEditDataTypeCommand, Execute_004)
{
	CDataType* BaseDataType1 = new CDataType();
	BaseDataType1->SetDataTypeID(1);
	BaseDataType1->SetDataDesc(_T("DataDesc1"));
	BaseDataType1->SetDataOffset(11);
	BaseDataType1->SetBitOffset(12);
	BaseDataType1->SetRemarks(_T("Remaks1"));

	CDataType* BaseDataType2 = new CDataType();
	BaseDataType2->SetDataTypeID(2);
	BaseDataType2->SetDataDesc(_T("DataDesc2"));
	BaseDataType2->SetDataOffset(21);
	BaseDataType2->SetBitOffset(22);
	BaseDataType2->SetRemarks(_T("Remaks2"));

	CDataType* BaseDataType3 = new CDataType();
	BaseDataType3->SetDataTypeID(3);
	BaseDataType3->SetDataDesc(_T("DataDesc3"));
	BaseDataType3->SetDataOffset(31);
	BaseDataType3->SetBitOffset(32);
	BaseDataType3->SetRemarks(_T("Remaks3"));

	CArray<CDataType*> Receiver;
	Receiver.RemoveAll();
	Receiver.Add(BaseDataType1);
	Receiver.Add(BaseDataType2);
	Receiver.Add(BaseDataType3);

	CDataType* DataType = new CDataType();
	DataType->SetDataTypeID(4);
	DataType->SetDataDesc(_T("DataDesc4"));
	DataType->SetDataOffset(41);
	DataType->SetBitOffset(42);
	DataType->SetRemarks(_T("Remaks4"));

	CEditDataTypeCommandAdapter Command;
	Command.SetReceiver(&Receiver);
	Command.SetDataTypeIndex(1);
	Command.SetDataType(DataType);

	ASSERT_TRUE(Command.Execute());

	CDataType* Item = Receiver.GetAt(0);
	ASSERT_EQ(3, Receiver.GetCount());
	ASSERT_EQ(1, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc1"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks1"), Item->GetRemarks());
	ASSERT_EQ(11, Item->GetDataOffset());
	ASSERT_EQ(12, Item->GetBitOffset());

	Item = Receiver.GetAt(2);
	ASSERT_EQ(3, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc3"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks3"), Item->GetRemarks());
	ASSERT_EQ(31, Item->GetDataOffset());
	ASSERT_EQ(32, Item->GetBitOffset());

	Item = Receiver.GetAt(1);
	ASSERT_EQ(4, Item->GetDataTypeId());
	ASSERT_STREQ(_T("DataDesc4"), Item->GetDataDesc());
	ASSERT_STREQ(_T("Remaks4"), Item->GetRemarks());
	ASSERT_EQ(41, Item->GetDataOffset());
	ASSERT_EQ(42, Item->GetBitOffset());

	//å„èàóù
	delete BaseDataType1;
	delete BaseDataType3;
	delete DataType;
	delete Item;
}
