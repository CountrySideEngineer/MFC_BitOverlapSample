
// MFC_BitOverlapSampleDlg.h : ヘッダー ファイル
//

#pragma once
#include "CDataType.h"

// CMFCBitOverlapSampleDlg ダイアログ
class CMFCBitOverlapSampleDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCBitOverlapSampleDlg(CWnd* pParent = nullptr);	// 標準コンストラクター
	virtual ~CMFCBitOverlapSampleDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_BITOVERLAPSAMPLE_DIALOG };
#endif
	enum {
		DATA_TYPE_TABLE_COL_INDEX_NO = 0,		//No.
		DATA_TYPE_TABLE_COL_INDEX_DATA_TYPE,	//データ型
		DATA_TYPE_TABLE_COL_INDEX_NAME,			//名前列
		DATA_TYPE_TABLE_COL_INDEX_OFFSET,		//オフセット列
		DATA_TYPE_TABLE_COL_INDEX_REMARKS,		//備考列
		DATA_TYPE_TABLE_COL_INDEX_MAX,
	};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	virtual BOOL SetupTable();
	virtual BOOL SetupDataTypeTable();

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	virtual void OpenEditDataTypeDlg();
	virtual void AddNewDataType(CDataType* Src);
	virtual void UpdateTable();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunCheck();
	afx_msg void OnBnClickedButtonAddItem();

protected:
	CArray<CDataType*> m_DataTypeCollection;

	CListCtrl m_DataTypeListView;
};
