#include "gtest/gtest.h"
#include "CDataType.h"
#include "CDataTypeInfo.h"
#include "CCsvFormatter.h"
#include <atlstr.h>
TEST(CCsvFormatter, Format_001)
{
	CDataType DataType;
	DataType.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);
	DataType.SetDataDesc(_T("BOOL type data"));
	DataType.SetDataOffset(0);
	DataType.SetBitOffset(0);
	DataType.SetRemarks(_T("This is remark."));
	CArray<CDataType*> DataSrc;
	DataSrc.RemoveAll();
	DataSrc.Add(&DataType);

	CCsvFormatter DataFormatter;
	CString FormattedData = DataFormatter.Format(&DataSrc);
	CString ExpectData = _T("BOOL,BOOL type data,0.0,This is remark.\r\n");

	ASSERT_STREQ(ExpectData, FormattedData);
}

TEST(CCsvFormatter, Format_002)
{
	CDataType DataType1;
	DataType1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);
	DataType1.SetDataDesc(_T("BOOL type data"));
	DataType1.SetDataOffset(0);
	DataType1.SetBitOffset(0);
	DataType1.SetRemarks(_T("This is remark."));
	CDataType DataType2;
	DataType2.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BYTE);
	DataType2.SetDataDesc(_T("BYTE type data"));
	DataType2.SetDataOffset(1);
	DataType2.SetBitOffset(1);
	DataType2.SetRemarks(_T("This is BYTE remark."));
	CArray<CDataType*> DataSrc;
	DataSrc.RemoveAll();
	DataSrc.Add(&DataType1);
	DataSrc.Add(&DataType2);

	CCsvFormatter DataFormatter;
	CString FormattedData = DataFormatter.Format(&DataSrc);
	CString ExpectData = _T("BOOL,BOOL type data,0.0,This is remark.\r\n");
	ExpectData += _T("BYTE,BYTE type data,1.1,This is BYTE remark.\r\n");

	ASSERT_STREQ(ExpectData, FormattedData);
}

TEST(CCsvFormatter, Format_003)
{
	CDataType DataType1;
	DataType1.SetDataTypeID(CDataTypeInfo::DATA_TYPE_INFO_NAME_BOOL);
	DataType1.SetDataDesc(_T("BOOL type data."));
	DataType1.SetDataOffset(0);
	DataType1.SetBitOffset(0);
	DataType1.SetRemarks(_T("This is remark.\r\nMultiLine"));
	CArray<CDataType*> DataSrc;
	DataSrc.RemoveAll();
	DataSrc.Add(&DataType1);

	CCsvFormatter DataFormatter;
	CString FormattedData = DataFormatter.Format(&DataSrc);
	CString ExpectData = _T("BOOL,BOOL type data.,0.0,\"This is remark.\nMultiLine\"\r\n");

	ASSERT_STREQ(ExpectData, FormattedData);
}
