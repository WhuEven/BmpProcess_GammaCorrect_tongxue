#pragma once
#include "BmpProcessDoc.h"

// HistGram 对话框

class HistGram : public CDialog
{
	DECLARE_DYNAMIC(HistGram)

public:
	HistGram(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HistGram();
	int nCount[256];
	HistGram(int nCount[256],CWnd* pParent = NULL);   // 标准构造函数
// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	// DDX/DDV 支持
	CBmpProcessDoc *m_pDoc;
	DWORD DIBNumColors(LPBYTE lpDIB);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	INT_PTR DoModalmain(CBmpProcessDoc * ptest){m_pDoc = ptest;return DoModal();}//用于获取当前文档指针
	int *m_IHist;
};
