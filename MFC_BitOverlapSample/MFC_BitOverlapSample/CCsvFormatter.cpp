#include "pch.h"
#include "CCsvFormatter.h"
#include "CDataTypeInfo.h"
#include "CUtility.h"

const CString CCsvFormatter::Separator = _T(",");
const CString CCsvFormatter::CrLf = _T("\r\n");
const CString CCsvFormatter::Lf = _T("\n");
const CString CCsvFormatter::DoubleQuotation = _T("\"");

/**
 *	データ型情報から、ファイル出力用フォーマットを作成する。
 *
 *	@param[in]	Src	ファイルに出力したいデータ型情報へのポインタ
 *	@return	出力情報へのポインタ
 */
CString CCsvFormatter::Format(CArray<CDataType*>* Src)
{
	ASSERT(NULL != Src);
	ASSERT(0 < Src->GetCount());

	CString FormattedString = _T("");
	for (INT_PTR Index = 0; Index < Src->GetCount(); Index++) {
		CDataType* SrcItem = Src->GetAt(Index);
		FormattedString += this->Format(SrcItem);
	}
	return FormattedString;
}

/**
 *	データ型情報から、ファイルに出力するCSV形式の文字列を生成する。
 *
 *	@param[in]	Src	CSV(１行分)に出力する文字列データ
 */
CString CCsvFormatter::Format(CDataType* Src)
{
	ASSERT(NULL != Src);

	CDataTypeInfo* Instance = CDataTypeInfo::GetInstance();
	CString DataTypeName = Instance->GetTypeName(Src->GetDataTypeId());
	CString DataDesc = Src->GetDataDesc();
	CUtility Util;
	CString Offset = Util.SetupOffset(Src->GetDataOffset(), Src->GetBitOffset());
	CString Remarks = Src->GetRemarks();
	if (0 < Remarks.Find(CrLf)) {
		//備考に改行があった場合、改行コードを変更したうえで「"」で囲む。
		Remarks.Replace(CrLf, Lf);
		Remarks = DoubleQuotation + Remarks + DoubleQuotation;
	}

	CString FormattedString = _T("");
	FormattedString += (DataTypeName + Separator);
	FormattedString += (DataDesc + Separator);
	FormattedString += (Offset + Separator);
	FormattedString += (Remarks + CrLf);

	return FormattedString;
}