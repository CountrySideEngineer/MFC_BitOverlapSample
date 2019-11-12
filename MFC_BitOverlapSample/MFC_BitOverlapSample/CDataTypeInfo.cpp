#include "pch.h"
#include "CDataTypeInfo.h"

/**
 *	CDataTypeInfoのシングルトンインスタンスを取得する。
 */
CDataTypeInfo* CDataTypeInfo::GetInstance()
{
	static CDataTypeInfo Instance;

	return (CDataTypeInfo*)(&Instance);
}