#include "pch.h"
#include "CBOSFile.h"
#include "CCsvFormatter.h"
#include "CUtility.h"

/**
 *	デフォルトコンストラクタ
 */
CBOSFile::CBOSFile()
	: m_FilePath(_T(""))
{}

/**
 *	引数ありのコンストラクタ
 */
CBOSFile::CBOSFile(CString FilePath)
	: m_FilePath(FilePath)
{}

/**
 *	デストラクタ
 */
CBOSFile::~CBOSFile() {}

/**
 *	データ型情報をファイルに出力する。
 *
 *	@param[in]	Src	ファイルに出力したいデータ型情報へのポインタ
 */
void CBOSFile::WriteData(CArray<CDataType*>* Src)
{
	CString DataToWrite = this->GetDataToWrite(Src);

	CFile File;
	void* BufferToData = (void*)(DataToWrite.GetBuffer());
	UINT Count = DataToWrite.GetLength() * sizeof(TCHAR);

	File.Open(this->m_FilePath, CFile::modeWrite | CFile::modeCreate);
	File.Write(BufferToData, Count);
	File.Close();//ここは同じ
}

/**
 *	ファイルに出力するデータを生成する。
 *
 *	@param[in]	Src	データの生成元へのポインタ
 *	@return	ファイルに出力する文字列データ
 */
CString CBOSFile::GetDataToWrite(CArray<CDataType*>* Src)
{
	CCsvFormatter* Formatter = this->CreateFormatter();
	UINT Count = 0;
	CString DataToWrite = Formatter->Format(Src);
	CUtility Util;
	Util.Release(&Formatter);

	return DataToWrite;
}

/**
 *	設定されているファイルパスから、ファイルの拡張子を取得する。
 */
CString CBOSFile::ExtractExtention()
{
	ASSERT(0 < this->m_FilePath.GetLength());

	INT_PTR DotIndex = this->m_FilePath.ReverseFind(Dot);
	if ((-1) == DotIndex) {
		//@ToDo:例外を投げる
		return _T("");	//Dotが見つからない場合には、空文字を返す。
	}
	else {
		return this->m_FilePath.Mid(DotIndex + 1);//「.」を含まない拡張子を抽出する。
	}
}

/**
 *	拡張子に対応するデータフォーマッタを返す。
 *
 *	@param	現在
 */
CCsvFormatter* CBOSFile::CreateFormatter()
{
	CString Extention = this->ExtractExtention();
	CCsvFormatter* Formatter = NULL;

	if (AVAILABLE_FILE_EXTENTION_CSV == Extention) {
		Formatter = new CCsvFormatter();
	}
	else {
		//拡張子がCSV以外の場合には何もしない。
	}
	return Formatter;
}