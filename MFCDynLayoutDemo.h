
#pragma once

#include <afxwin.h>

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

class CMFCDynLayoutDemoApp : public CWinApp
{
public:
	CMFCDynLayoutDemoApp();
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};

extern CMFCDynLayoutDemoApp theApp;