#include "gtest/gtest.h"
#include "CUtility.h"
#include <atlstr.h>

TEST(CUtility, SetupOffset_001)
{
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T("0.0"), OffsetData);
}

TEST(CUtility, SetupOffset_002)
{
	INT_PTR DataOffset = 1;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T("1.0"), OffsetData);
}

TEST(CUtility, SetupOffset_003)
{
	INT_PTR DataOffset = 1;
	INT_PTR BitOffset = 2;
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T("1.2"), OffsetData);
}

TEST(CUtility, SetupOffset_004)
{
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T(""), OffsetData);
}

TEST(CUtility, SetupOffset_005)
{
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 8;
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T(""), OffsetData);
}

TEST(CUtility, SetupOffset_006)
{
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = 0;
	CUtility TestData;
	CString OffsetData = TestData.SetupOffset(DataOffset, BitOffset);

	ASSERT_STREQ(_T(""), OffsetData);
}

TEST(CUtility, ExtractOffset_001)
{
	CString OffsetString = _T("0.0");
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ(0, DataOffset);
	ASSERT_EQ(0, BitOffset);
}

TEST(CUtility, ExtractOffset_002)
{
	CString OffsetString = _T("1.0");
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ(1, DataOffset);
	ASSERT_EQ(0, BitOffset);
}

TEST(CUtility, ExtractOffset_003)
{
	CString OffsetString = _T("0.1");
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ(0, DataOffset);
	ASSERT_EQ(1, BitOffset);
}

TEST(CUtility, ExtractOffset_004)
{
	CString OffsetString = _T("0.7");
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ(0, DataOffset);
	ASSERT_EQ(7, BitOffset);
}

TEST(CUtility, ExtractOffset_005)
{
	CString OffsetString = _T("0.8");
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ((-1), DataOffset);
	ASSERT_EQ((-1), BitOffset);
}

TEST(CUtility, ExtractOffset_006)
{
	CString OffsetString = _T("9.0");
	INT_PTR DataOffset = (-1);
	INT_PTR BitOffset = (-1);
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ(9, DataOffset);
	ASSERT_EQ(0, BitOffset);
}

TEST(CUtility, ExtractOffset_007)
{
	CString OffsetString = _T("A.0");
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ((-1), DataOffset);
	ASSERT_EQ((-1), BitOffset);
}

TEST(CUtility, ExtractOffset_008)
{
	CString OffsetString = _T("0.");
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ((-1), DataOffset);
	ASSERT_EQ((-1), BitOffset);
}

TEST(CUtility, ExtractOffset_009)
{
	CString OffsetString = _T("0");
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ((-1), DataOffset);
	ASSERT_EQ((-1), BitOffset);
}

TEST(CUtility, ExtractOffset_010)
{
	CString OffsetString = _T("");
	INT_PTR DataOffset = 0;
	INT_PTR BitOffset = 0;
	CUtility TestData;
	TestData.ExtractOffset(OffsetString, DataOffset, BitOffset);

	ASSERT_EQ((-1), DataOffset);
	ASSERT_EQ((-1), BitOffset);
}

/**
 *	Releaseメソッドをテストするためのクラス 
 */
class CForTestRelease
{
public:
	CForTestRelease() {}
	virtual ~CForTestRelease() {}
};

TEST(CUtility, Release_001)
{
	CForTestRelease* ForTestRelease = new CForTestRelease();
	CUtility TestData;
	TestData.Release(&ForTestRelease);

	ASSERT_EQ(NULL, ForTestRelease);
}

TEST(CUtility, Release_002)
{
	CArray<CForTestRelease*> ForTestReleaseArray;
	CUtility TestData;
	TestData.Release(&ForTestReleaseArray);

	ASSERT_EQ(0, ForTestReleaseArray.GetCount());
}

TEST(CUtility, Release_003)
{
	CArray<CForTestRelease*> ForTestReleaseArray;
	ForTestReleaseArray.Add(new CForTestRelease());
	CUtility TestData;
	TestData.Release(&ForTestReleaseArray);

	ASSERT_EQ(0, ForTestReleaseArray.GetCount());
}

TEST(CUtility, Release_004)
{
	CArray<CForTestRelease*> ForTestReleaseArray;
	ForTestReleaseArray.Add(new CForTestRelease());
	ForTestReleaseArray.Add(new CForTestRelease());
	CUtility TestData;
	TestData.Release(&ForTestReleaseArray);

	ASSERT_EQ(0, ForTestReleaseArray.GetCount());
}
