// BmpProcess.h : BmpProcess Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBmpProcessApp:
// �йش����ʵ�֣������ BmpProcess.cpp
//

class CBmpProcessApp : public CWinApp
{
public:
	CBmpProcessApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
};

extern CBmpProcessApp theApp;