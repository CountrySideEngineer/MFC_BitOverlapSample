#pragma once
#include "COffsetEdit.h"
#include "CDataType.h"

// CEditNewDataDlg ダイアログ

class CEditNewDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditNewDataDlg)

public:
	CEditNewDataDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CEditNewDataDlg();

	virtual void SetDataTypeStore(CDataType* DataType) { this->m_DataTypeBuff = DataType; }

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_INPUT_NEW_DATA_TYPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void UpdateDataType();

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_DataNameEdit;
	CEdit m_DataDescEdit;
	COffsetEdit m_OffsetEdit;
	CComboBox m_DataTypeComboBox;
	CDataType* m_DataTypeBuff;

	CString m_DataName;
	CString m_DataDesc;
	CString m_Offset;
	INT_PTR m_DataType;

public:
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
