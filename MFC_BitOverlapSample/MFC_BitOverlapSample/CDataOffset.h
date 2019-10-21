#pragma once
class CDataOffset
{
public:

	enum {
		CDATA_OFFSET_BASE_DECIMAL = 10	//10進数
	};
	enum {
		CDATA_OFFSET_BASE_HEX_DECIMAL = 16	//16進数
	};

	enum {
		CDATA_OFFSET_DATA_TYPE_BOOL = 1,
		CDATA_OFFSET_DATA_TYPE_BYTE,
		CDATA_OFFSET_DATA_TYPE_WORD,
		CDATA_OFFSET_DATA_TYPE_DWORD,
		CDATA_OFFSET_DATA_TYPE_INT8,
		CDATA_OFFSET_DATA_TYPE_INT16,
		CDATA_OFFSET_DATA_TYPE_INT32,
		CDATA_OFFSET_DATA_TYPE_UINT8,
		CDATA_OFFSET_DATA_TYPE_UINT16,
		CDATA_OFFSET_DATA_TYPE_UINT32,
		CDATA_OFFSET_DATA_TYPE_MAX,
	};

	static const UINT32 DataBitArray_01bit = 0x00000001;
	static const UINT32 DataBitArray_08bit = 0x000000FF;
	static const UINT32 DataBitArray_16bit = 0x0000FFFF;
	static const UINT32 DataBitArray_32bit = 0xFFFFFFFF;
	static const INT_PTR DataSize_01bit = 1;
	static const INT_PTR DataSize_08bit = 8;
	static const INT_PTR DataSize_16bit = 16;
	static const INT_PTR DataSize_32bit = 32;

public:
	CDataOffset();
	virtual ~CDataOffset() {}

	virtual INT_PTR GetDataType() const { return this->m_DataType; }
	virtual void SetDataType(INT_PTR DataType);
	virtual CString GetDataName() const { return this->m_DataName; }
	virtual void SetDataName(CString DataName) { this->m_DataName = DataName; }
	virtual INT_PTR GetDataOffset() const { return this->m_DataOffset; }
	virtual void SetDataOffset(INT_PTR DataOffset) { this->m_DataOffset = DataOffset; }
	virtual INT_PTR GetBitOffset() const { return this->m_BitOffset; }
	virtual void SetBitOffset(INT_PTR BitOffset) { this->m_BitOffset = BitOffset; }

	virtual INT_PTR GetDataSize() const { return this->m_DataSize; }	//データ型から決定
	virtual void SetOffset(CString BitOffset);

protected:
	static void InitMap();

	virtual BOOL CheckFormat(CString BitOffset);
	virtual INT_PTR ExtractOffset(CString BitOffset, INT_PTR StartIndex, INT_PTR DataLen, int Base);

protected:
	INT_PTR m_DataType;
	CString m_DataName;
	INT_PTR m_DataSize;
	INT_PTR m_BitArray;
	INT_PTR m_DataOffset;
	INT_PTR m_BitOffset;

public:
	static CMap<INT_PTR, INT_PTR, UINT32, UINT32> TypeBitArrayMap;
	static CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> TypeBitSizeMap;
	static CMap<INT_PTR, INT_PTR, INT_PTR, INT_PTR> TypeDataSizeMap;

protected:
	static BOOL IsInit;
};

