#pragma once
#include "BmpProcessDoc.h"

// HistGram �Ի���

class HistGram : public CDialog
{
	DECLARE_DYNAMIC(HistGram)

public:
	HistGram(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HistGram();
	int nCount[256];
	HistGram(int nCount[256],CWnd* pParent = NULL);   // ��׼���캯��
// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	// DDX/DDV ֧��
	CBmpProcessDoc *m_pDoc;
	DWORD DIBNumColors(LPBYTE lpDIB);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	INT_PTR DoModalmain(CBmpProcessDoc * ptest){m_pDoc = ptest;return DoModal();}//���ڻ�ȡ��ǰ�ĵ�ָ��
	int *m_IHist;
};
