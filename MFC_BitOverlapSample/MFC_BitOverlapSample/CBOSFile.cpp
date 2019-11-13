#include "pch.h"
#include "CBOSFile.h"
#include "CCsvFormatter.h"
#include "CUtility.h"

/**
 *	�f�t�H���g�R���X�g���N�^
 */
CBOSFile::CBOSFile()
	: m_FilePath(_T(""))
{}

/**
 *	��������̃R���X�g���N�^
 */
CBOSFile::CBOSFile(CString FilePath)
	: m_FilePath(FilePath)
{}

/**
 *	�f�X�g���N�^
 */
CBOSFile::~CBOSFile() {}

/**
 *	�f�[�^�^�����t�@�C���ɏo�͂���B
 *
 *	@param[in]	Src	�t�@�C���ɏo�͂������f�[�^�^���ւ̃|�C���^
 */
void CBOSFile::WriteData(CArray<CDataType*>* Src)
{
	CString DataToWrite = this->GetDataToWrite(Src);

	CFile File;
	void* BufferToData = (void*)(DataToWrite.GetBuffer());
	UINT Count = DataToWrite.GetLength() * sizeof(TCHAR);

	File.Open(this->m_FilePath, CFile::modeWrite | CFile::modeCreate);
	File.Write(BufferToData, Count);
	File.Close();//�����͓���
}

/**
 *	�t�@�C���ɏo�͂���f�[�^�𐶐�����B
 *
 *	@param[in]	Src	�f�[�^�̐������ւ̃|�C���^
 *	@return	�t�@�C���ɏo�͂��镶����f�[�^
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
 *	�ݒ肳��Ă���t�@�C���p�X����A�t�@�C���̊g���q���擾����B
 */
CString CBOSFile::ExtractExtention()
{
	ASSERT(0 < this->m_FilePath.GetLength());

	INT_PTR DotIndex = this->m_FilePath.ReverseFind(Dot);
	if ((-1) == DotIndex) {
		//@ToDo:��O�𓊂���
		return _T("");	//Dot��������Ȃ��ꍇ�ɂ́A�󕶎���Ԃ��B
	}
	else {
		return this->m_FilePath.Mid(DotIndex + 1);//�u.�v���܂܂Ȃ��g���q�𒊏o����B
	}
}

/**
 *	�g���q�ɑΉ�����f�[�^�t�H�[�}�b�^��Ԃ��B
 *
 *	@param	����
 */
CCsvFormatter* CBOSFile::CreateFormatter()
{
	CString Extention = this->ExtractExtention();
	CCsvFormatter* Formatter = NULL;

	if (AVAILABLE_FILE_EXTENTION_CSV == Extention) {
		Formatter = new CCsvFormatter();
	}
	else {
		//�g���q��CSV�ȊO�̏ꍇ�ɂ͉������Ȃ��B
	}
	return Formatter;
}