
// MFC_BitOverlapSampleDlg.h : ヘッダー ファイル
//

#pragma once
#include "CDataType.h"
#include "CBOSCommandManager.h"

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

	virtual void RunCommand(ACommand* Command, CString CommandName = _T(""));

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	virtual void EditNewDataTypeInfo();
	virtual void EditNewDataTypeInfo(CDataType* DataType);
	virtual void DeleteDataTypeInfo();
	virtual void DeleteDataTypeInfo(INT_PTR TargetDataIndex);
	virtual void EditDataTypeInfo();
	virtual void EditDataTypeInfo(INT_PTR TargetDataIndex, CDataType* DataType);
	virtual void UpdateView();
	virtual void UpdateTable();
	virtual void UpdateButton();
	virtual void UpdateButton(BOOL IsEnable);
	virtual BOOL RunOverlapCheck(INT_PTR& TaregetRowIndex, INT_PTR& CompRowIndex);

protected:
	CArray<CDataType*> m_DataTypeCollection;

	CListCtrl m_DataTypeListView;
	CBOSCommandManager m_CommandManager;
	CButton m_AddItemButton;
	CButton m_DeleteItemButton;
	CButton m_ValidateItemButton;
	CButton m_ExportDataInfoButton;
	CButton m_EditDataButton;

public:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonRunCheck();
	afx_msg void OnBnClickedButtonAddItem();
	afx_msg void OnBnClickedButtonDeleteItem();
	afx_msg void OnBnClickedButtonEditData();
	afx_msg void OnBnClickedButtonCheckItem();
	afx_msg void OnBnClickedButtonExportData();
};
