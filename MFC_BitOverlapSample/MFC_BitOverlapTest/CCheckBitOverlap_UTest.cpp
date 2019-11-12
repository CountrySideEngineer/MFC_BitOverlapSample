#include "gtest/gtest.h"
#include "CCheckBitOverlap.h"
#include "CDataType.h"
#include "CDataTypeInfo.h"
#include <atlstr.h>

TEST(CCheckBitOverlap, CheckOverlap_001)
{
	CDataType Target;
	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_FALSE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_002)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);

	CDataType Target2;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(1);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_FALSE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_003)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);

	CDataType Target2;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_004)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(0);
	Target2.SetBitOffset(1);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_005)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_FALSE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_006)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(0);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_WORD);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_007)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_WORD);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_FALSE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_008)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_WORD);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_009)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_WORD);

	CDataType Target2;
	Target2.SetDataOffset(2);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_FALSE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_010)
{
	CDataType Target1;
	Target1.SetDataOffset(1);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(0);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_WORD);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
}

TEST(CCheckBitOverlap, CheckOverlap_011)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(0);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
	ASSERT_EQ(0, CheckBitOverlap.GetTargetRowIndex());
	ASSERT_EQ(1, CheckBitOverlap.GetCompRowIndex());
}

TEST(CCheckBitOverlap, CheckOverlap_012)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target3;
	Target3.SetDataOffset(0);
	Target3.SetBitOffset(0);
	Target3.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	DataToCheck.Add(&Target3);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
	ASSERT_EQ(0, CheckBitOverlap.GetTargetRowIndex());
	ASSERT_EQ(2, CheckBitOverlap.GetCompRowIndex());
}

TEST(CCheckBitOverlap, CheckOverlap_013)
{
	CDataType Target1;
	Target1.SetDataOffset(1);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target3;
	Target3.SetDataOffset(0);
	Target3.SetBitOffset(0);
	Target3.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	DataToCheck.Add(&Target3);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
	ASSERT_EQ(0, CheckBitOverlap.GetTargetRowIndex());
	ASSERT_EQ(1, CheckBitOverlap.GetCompRowIndex());
}

TEST(CCheckBitOverlap, CheckOverlap_014)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(1);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target3;
	Target3.SetDataOffset(1);
	Target3.SetBitOffset(0);
	Target3.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	DataToCheck.Add(&Target3);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
	ASSERT_EQ(1, CheckBitOverlap.GetTargetRowIndex());
	ASSERT_EQ(2, CheckBitOverlap.GetCompRowIndex());
}

TEST(CCheckBitOverlap, CheckOverlap_015)
{
	CDataType Target1;
	Target1.SetDataOffset(0);
	Target1.SetBitOffset(0);
	Target1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target2;
	Target2.SetDataOffset(0);
	Target2.SetBitOffset(0);
	Target2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CDataType Target3;
	Target3.SetDataOffset(0);
	Target3.SetBitOffset(0);
	Target3.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);

	CArray<CDataType*> DataToCheck;
	DataToCheck.RemoveAll();
	DataToCheck.Add(&Target1);
	DataToCheck.Add(&Target2);
	DataToCheck.Add(&Target3);
	CCheckBitOverlap CheckBitOverlap;

	ASSERT_TRUE(CheckBitOverlap.CheckOverlap(&DataToCheck));
	ASSERT_EQ(0, CheckBitOverlap.GetTargetRowIndex());
	ASSERT_EQ(1, CheckBitOverlap.GetCompRowIndex());
}
