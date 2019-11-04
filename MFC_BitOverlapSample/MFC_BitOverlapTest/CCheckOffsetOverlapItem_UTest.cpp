#include "gtest/gtest.h"
#include "CDataOffset.h"
#include "CCheckOffsetOverlap.h"
#include "CCheckOffsetOverlapItem.h"
#include <atlstr.h>

TEST(CCheckOffsetOverlapItem, RunCheck_001)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 1);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlapItem TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlapItem, RunCheck_002)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 1, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 1, 1);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);

	CCheckOffsetOverlapItem TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlapItem, RunCheck_003)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 1, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 2, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);

	CCheckOffsetOverlapItem TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlapItem, RunCheck_004)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 1, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 1, 8);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);

	CCheckOffsetOverlapItem TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlapItem, RunCheck_005)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 1, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 2, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);

	CCheckOffsetOverlapItem TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlapItem, RunCheck_006)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 2, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);

	CCheckOffsetOverlapItem TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));
}
