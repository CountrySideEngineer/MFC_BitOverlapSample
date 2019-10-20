
// MFC_BitOverlapSample.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCBitOverlapSampleApp:
// このクラスの実装については、MFC_BitOverlapSample.cpp を参照してください
//

class CMFCBitOverlapSampleApp : public CWinApp
{
public:
	CMFCBitOverlapSampleApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCBitOverlapSampleApp theApp;
