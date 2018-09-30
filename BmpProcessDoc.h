// BmpProcessDoc.h : CBmpProcessDoc 类的接口
//


#pragma once


class CBmpProcessDoc : public CDocument
{
public: // 仅从序列化创建
	CBmpProcessDoc();
	DECLARE_DYNCREATE(CBmpProcessDoc)

protected:
	HANDLE OpenImageBMP(LPCTSTR lpzsPathName,HGLOBAL *phdib, CPalette *ppal);

// 属性
public:
	HANDLE m_hDIB;
	UINT nImgWidth; 
	UINT nImgHeight;
	WORD DIBNumColors(LPBYTE lpDIB);

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// 实现
public:
	CPalette * ppal;
	HGLOBAL * phdib;
	virtual ~CBmpProcessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
};


