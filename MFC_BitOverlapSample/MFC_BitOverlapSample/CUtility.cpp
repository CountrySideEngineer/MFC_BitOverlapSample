#include "pch.h"
#include "CUtility.h"
#include "CRegex.h"
#include <regex>

/**
 *	データオフセットの文字列から、データ/ビットのオフセットを取得する。
 *
 *	@param	OffsetString	オフセットを示す文字列
 *	@param[out]	DataOffset	抜き出したデータオフセットの格納先
 *							処理が正常に完了しなかった場合には、-1がセットされる。
 *	@param[out]	BitOffset	抜き出したビットオフセットの格納先
 *							処理が正常に完了しなかった場合には、-1がセットされる。
 */
void CUtility::ExtractOffset(CString OffsetString, INT_PTR& DataOffset, INT_PTR& BitOffset)
{
	//フォーマットの確認
	if (FALSE == this->CheckBitOffsetFormat(OffsetString)) {
		TRACE(_T("Offset format ERROR!\n"));

		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}

	INT_PTR TokenIndex = OffsetString.Find(_T("."));
	INT_PTR DataOffsetTemp = this->ExtractOffset(OffsetString,
		0,
		TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//データのインデックスは、10進数表記
	if ((-1) == DataOffsetTemp) {
		/*
		 *	変換に失敗した場合には、エラー値を設定して処理を終了する。
		 *	(本来、ここは到達不可能のはず。念のためにエラー処理を実装しておく。
		 */
		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}
	INT_PTR BitOffsetTmp = this->ExtractOffset(OffsetString,
		TokenIndex + 1,
		OffsetString.GetLength() - TokenIndex,
		CDATA_OFFSET_BASE_DECIMAL);	//ビットのインデックスは、10進数表記
	if ((-1) == BitOffsetTmp) {
		/*
		 *	変換に失敗した場合には、エラー値を設定して処理を終了する。
		 *	(本来、ここは到達不可能のはず。念のためにエラー処理を実装しておく。
		 */
		DataOffset = (-1);
		BitOffset = (-1);
		return;
	}

	DataOffset = DataOffsetTemp;
	BitOffset = BitOffsetTmp;
}

/**
 *	ビットオフセットのフォーマットを確認する。
 *	フォーマットが正しい場合にはTRUE、正しくない場合にはFALSEを返す。
 *
 *	@param	BitOffset	オフセット情報の文字列
 *						[ワードオフセット(10進数)].[ビットオフセット(16進数)]の
 *						フォーマットであること。
 */
BOOL CUtility::CheckBitOffsetFormat(CString BitOffset)
{
	std::regex pattern(_T("[0-9]{1,}(\.[0-7])"));
	std::cmatch Match;
	TCHAR* PatternEnd = BitOffset.GetBuffer() + BitOffset.GetLength();
	LPTSTR Buffer = BitOffset.GetBuffer();

	return std::regex_match((const TCHAR*)Buffer, (const TCHAR*)PatternEnd, Match, pattern);
}

/**
 *	オフセットの文字列から、対応するオフセット値を抜き出す。
 *
 *	@param	BitOffset	オフセットを示す文字列
 *	@param	StartIndex	文字列の抜き出し開始位置
 *	@param	DataLen		抜き出す文字列の長さ
 *	@param	Base		オフセットのデータの基数
 *	@return	オフセット値
 */
INT_PTR CUtility::ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base)
{
	CString DataOffset = BitOffset.Mid(StartIndex, DataLen);

	TCHAR* EndChar = NULL;
	INT_PTR OffsetValue = _tcstol(DataOffset, &EndChar, Base);
	if ((NULL != EndChar) && (NULL != _doserrno)) {
		TRACE(_T("FormatError\r\n"));
		return (-1);
	}
	return OffsetValue;
}

/**
 *	データ/ビットのオフセットの値に対応する文字列を生成する。
 *
 *	@param	DataOffset	データオフセット値
 *	@param	BitOffset	ビットオフセット値
 *	@return	オフセット値に対応した文字列を返す。
 *			入力する値が不正であった場合には、空文字を返す。
 */
CString CUtility::SetupOffset(const INT_PTR DataOffset, const INT_PTR BitOffset)
{
	CString OffsetString = _T("");

	if ((DataOffset < 0) ||
		((BitOffset < 0) || (7 < BitOffset)))
	{
		/*
		 *	データオフセットは、0以上でなければならない。
		 *	また、ビットオフセットは1バイト以内(0～7)でなければならない。
		 *	上記以上の範囲の場合には「変換不可」として、空文字を返す。
		 *	@ToDo:例外を投げる。
		 */
		return _T("");
	}
	OffsetString.Format(_T("%d.%d"), (int)DataOffset, (int)BitOffset);
	return OffsetString;
}