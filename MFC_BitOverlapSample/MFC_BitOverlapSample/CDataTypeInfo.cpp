#include "pch.h"
#include "CDataTypeInfo.h"

/**
 *	CDataTypeInfo�̃V���O���g���C���X�^���X���擾����B
 */
CDataTypeInfo* CDataTypeInfo::GetInstance()
{
	static CDataTypeInfo Instance;

	return (CDataTypeInfo*)(&Instance);
}