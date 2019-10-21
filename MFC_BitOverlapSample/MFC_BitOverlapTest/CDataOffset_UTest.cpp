#include "gtest/gtest.h"
#include "CDataOffset.h"
#include <atlstr.h>

TEST(CDataOffset, Constructor_001)
{
	CDataOffset TestData;

	ASSERT_EQ(0, TestData.GetDataType());
	ASSERT_STREQ(_T(""), TestData.GetDataName());
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
	ASSERT_EQ(1, TestData.GetBitMask());
	ASSERT_EQ(1, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_001)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);

	ASSERT_EQ(0xFF, TestData.GetBitMask());
	ASSERT_EQ(8, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_002)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD);

	ASSERT_EQ(0xFFFF, TestData.GetBitMask());
	ASSERT_EQ(16, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_003)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD);

	ASSERT_EQ(0xFFFFFFFF, TestData.GetBitMask());
	ASSERT_EQ(32, TestData.GetBitSize());
	ASSERT_EQ(32, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_004)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT8);

	ASSERT_EQ(0xFF, TestData.GetBitMask());
	ASSERT_EQ(8, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_005)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT16);

	ASSERT_EQ(0xFFFF, TestData.GetBitMask());
	ASSERT_EQ(16, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_006)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT32);

	ASSERT_EQ(0xFFFFFFFF, TestData.GetBitMask());
	ASSERT_EQ(32, TestData.GetBitSize());
	ASSERT_EQ(32, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_007)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT8);

	ASSERT_EQ(0xFF, TestData.GetBitMask());
	ASSERT_EQ(8, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_008)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT16);

	ASSERT_EQ(0xFFFF, TestData.GetBitMask());
	ASSERT_EQ(16, TestData.GetBitSize());
	ASSERT_EQ(16, TestData.GetDataSize());
}

TEST(CDataOffset, SetDataType_009)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);

	ASSERT_EQ(0xFFFFFFFF, TestData.GetBitMask());
	ASSERT_EQ(32, TestData.GetBitSize());
	ASSERT_EQ(32, TestData.GetDataSize());
}

TEST(CDataOffset, SetOffset_001)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_002)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("0.F"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(15, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_003)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("1.0"));

	ASSERT_EQ(1, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_004)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("1.1"));

	ASSERT_EQ(1, TestData.GetDataOffset());
	ASSERT_EQ(1, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_005)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_006)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);
	TestData.SetOffset(_T("0.1"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(1, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_007)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);
	TestData.SetOffset(_T("0.8"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(8, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_008)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);
	TestData.SetOffset(_T("0.9"));

	//エラーと判定されていることを確認したい。
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_009)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_010)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD);
	TestData.SetOffset(_T("0.1"));

	//エラーと判定されていることを確認したい。
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_011)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_012)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD);
	TestData.SetOffset(_T("0.1"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_013)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT8);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_014)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT8);
	TestData.SetOffset(_T("0.7"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(7, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_015)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT8);
	TestData.SetOffset(_T("0.8"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(8, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_016)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT8);
	TestData.SetOffset(_T("0.9"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_017)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT16);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_018)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT16);
	TestData.SetOffset(_T("0.1"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_019)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT32);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_020)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_INT32);
	TestData.SetOffset(_T("0.1"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_021)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT8);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_022)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT8);
	TestData.SetOffset(_T("0.7"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(7, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_023)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT8);
	TestData.SetOffset(_T("0.8"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(8, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_024)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT8);
	TestData.SetOffset(_T("0.9"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_025)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT16);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_026)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT16);
	TestData.SetOffset(_T("0.1"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_027)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T("0.0"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_028)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T("0.1"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_029)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T(".0"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_030)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T("0."));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_031)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T("0.00"));

	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_032)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_UINT32);
	TestData.SetOffset(_T("10.0"));

	ASSERT_EQ(10, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_033)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("0.A"));

	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(10, TestData.GetBitOffset());
}

TEST(CDataOffset, SetOffset_034)
{
	CDataOffset TestData;

	TestData.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	TestData.SetOffset(_T("A.A"));
	
	//エラーと判定されることを期待
	ASSERT_EQ(0, TestData.GetDataOffset());
	ASSERT_EQ(0, TestData.GetBitOffset());
}
