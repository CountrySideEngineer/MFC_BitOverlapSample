
// MFC_BitOverlapSampleDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFC_BitOverlapSample.h"
#include "MFC_BitOverlapSampleDlg.h"
#include "afxdialogex.h"
#include "CDataOffset.h"
#include "CCheckOffsetOverlap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBitOverlapSampleDlg ダイアログ



CMFCBitOverlapSampleDlg::CMFCBitOverlapSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_BITOVERLAPSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBitOverlapSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBitOverlapSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN_CHECK, &CMFCBitOverlapSampleDlg::OnBnClickedButtonRunCheck)
END_MESSAGE_MAP()


// CMFCBitOverlapSampleDlg メッセージ ハンドラー

BOOL CMFCBitOverlapSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCBitOverlapSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCBitOverlapSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCBitOverlapSampleDlg::OnBnClickedButtonRunCheck()
{
	CDataOffset DataOffset1;
	DataOffset1.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	DataOffset1.SetOffset(_T("0.0"));
	DataOffset1.SetOffset(_T(".0"));
	DataOffset1.SetOffset(_T("0."));
	DataOffset1.SetOffset(_T("0.00"));
	DataOffset1.SetOffset(_T("0.0.0"));
	DataOffset1.SetOffset(_T("0.9"));
	DataOffset1.SetOffset(_T("0.A"));
	DataOffset1.SetOffset(_T("0.F"));
	DataOffset1.SetOffset(_T("0.G"));
	DataOffset1.SetOffset(_T("10.F"));
	CDataOffset DataOffset2;
	DataOffset2.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	DataOffset2.SetOffset(_T("0.1"));
	CDataOffset DataOffset3;
	DataOffset3.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BOOL);
	DataOffset3.SetOffset(_T("0.2"));
	CDataOffset DataOffset4;
	DataOffset4.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_BYTE);
	DataOffset4.SetOffset(_T("3.3"));
	CDataOffset DataOffset5;
	DataOffset5.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_WORD);
	DataOffset5.SetOffset(_T("10.0"));
	CDataOffset DataOffset6;
	DataOffset6.SetDataType(CDataOffset::CDATA_OFFSET_DATA_TYPE_DWORD);
	DataOffset6.SetOffset(_T("9.8"));
	CArray<CDataOffset> DataToCheck;
	DataToCheck.Add(DataOffset4);
	DataToCheck.Add(DataOffset5);
	DataToCheck.Add(DataOffset6);
	DataToCheck.Add(DataOffset1);
	DataToCheck.Add(DataOffset2);
	DataToCheck.Add(DataOffset3);

	CCheckOffsetOverlap CheckOffsetOverlap;

	BOOL bCheckResult = CheckOffsetOverlap.RunCheck(DataToCheck);
	if (TRUE == bCheckResult) {
		AfxMessageBox(_T("重複なし"), MB_OK);
	}
	else {
		AfxMessageBox(_T("重複あり"), MB_OK);
	}
}
