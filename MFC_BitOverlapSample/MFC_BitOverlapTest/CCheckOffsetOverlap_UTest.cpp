#include "gtest/gtest.h"
#include "CDataOffset.h"
#include "CCheckOffsetOverlap.h"
#include <atlstr.h>

TEST(CCheckOffsetOverlap, RunCheck_001)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0001, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_002)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0001, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_003)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 1);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0003, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_004)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 1);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x01FF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_005)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x00FF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_006)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 7);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x00FF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_007)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_008)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 1);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFE, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_009)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 7);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x7FFF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_010)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFF00, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_011)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
}

TEST(CCheckOffsetOverlap, RunCheck_012)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0x0F);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
	ASSERT_EQ(0x0000, *(DataArray + 1));
}

TEST(CCheckOffsetOverlap, RunCheck_013)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlap, RunCheck_014)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_015)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 2, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_016)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD, 1, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_017)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x00FF, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_018)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 0, 8);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFF00, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_019)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 1, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_020)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 1, 8);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_021)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 2, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_022)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 2, 8);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
}

TEST(CCheckOffsetOverlap, RunCheck_023)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 3, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0000, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
	ASSERT_EQ(0x00FF, *(DataArray + 3));
}

TEST(CCheckOffsetOverlap, RunCheck_024)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 2, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
	ASSERT_EQ(0xFFFF, *(DataArray + 3));
}

TEST(CCheckOffsetOverlap, RunCheck_025)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_FALSE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0xFFFF, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
	ASSERT_EQ(0x0000, *(DataArray + 3));
}

TEST(CCheckOffsetOverlap, RunCheck_026)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 10, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 0, 0);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));
}

TEST(CCheckOffsetOverlap, RunCheck_027)
{
	CDataOffset TestInput_001(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 0, 0);
	CDataOffset TestInput_002(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD, 1, 0);
	CDataOffset TestInput_003(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 3, 0);
	CDataOffset TestInput_004(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 3, 1);
	CDataOffset TestInput_005(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 3, 2);
	CDataOffset TestInput_006(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL, 3, 3);
	CDataOffset TestInput_007(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE, 3, 4);
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(TestInput_001);
	DataToCheck.Add(TestInput_002);
	DataToCheck.Add(TestInput_003);
	DataToCheck.Add(TestInput_004);
	DataToCheck.Add(TestInput_005);
	DataToCheck.Add(TestInput_006);
	DataToCheck.Add(TestInput_007);

	CCheckOffsetOverlap TestData;

	ASSERT_TRUE(TestData.RunCheck(DataToCheck));

	WORD* DataArray = TestData.GetDataArray();
	ASSERT_EQ(0x0001, *DataArray);
	ASSERT_EQ(0xFFFF, *(DataArray + 1));
	ASSERT_EQ(0xFFFF, *(DataArray + 2));
	ASSERT_EQ(0x0FFF, *(DataArray + 3));
}
