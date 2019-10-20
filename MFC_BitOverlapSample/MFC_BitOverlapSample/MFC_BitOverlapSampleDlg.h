
// MFC_BitOverlapSampleDlg.h : ヘッダー ファイル
//

#pragma once


// CMFCBitOverlapSampleDlg ダイアログ
class CMFCBitOverlapSampleDlg : public CDialogEx
{
// コンストラクション
public:
	CMFCBitOverlapSampleDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_BITOVERLAPSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRunCheck();
};
