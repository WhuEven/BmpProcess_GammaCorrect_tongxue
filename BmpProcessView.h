// BmpProcessView.h : CBmpProcessView 类的接口
//


#pragma once


class CBmpProcessView : public CView
{
protected: // 仅从序列化创建
	CBmpProcessView();
	DECLARE_DYNCREATE(CBmpProcessView)

// 属性
public:
	CBmpProcessDoc* GetDocument() const;
	CPalette * ppal;
	HGLOBAL * hdib;
	CRect m_rcDIB;
// 操作
public:
	UINT ImgHeight;
	UINT ImgWidth;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual BOOL PaintDIB(HDC cDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect,HPALETTE hPal,DWORD dwRop);//用于画图


// 实现
public:
	HPALETTE CreateDIBPalette(LPBYTE lpbi);
	WORD DIBNumColors(LPBYTE lpDIB);
	virtual ~CBmpProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCorr();
	afx_msg void On32774();
	afx_msg void OnFileSaveAs();
	afx_msg void On32775();
	/*afx_msg void OnZHIFANGTU();*/
	/*afx_msg void On32778();*/
	afx_msg void On32780();
	afx_msg void Onzhifangtu();
	/*afx_msg void OnTwo();*/
	afx_msg void On32782();
	afx_msg void OnEvaluation();
	afx_msg double OnGetGrayMean();
	afx_msg void Onxinhaobi();
}; 

#ifndef _DEBUG  // BmpProcessView.cpp 中的调试版本
inline CBmpProcessDoc* CBmpProcessView::GetDocument() const
   { return reinterpret_cast<CBmpProcessDoc*>(m_pDocument); }
#endif

