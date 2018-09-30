// BmpProcessDoc.h : CBmpProcessDoc ��Ľӿ�
//


#pragma once


class CBmpProcessDoc : public CDocument
{
public: // �������л�����
	CBmpProcessDoc();
	DECLARE_DYNCREATE(CBmpProcessDoc)

protected:
	HANDLE OpenImageBMP(LPCTSTR lpzsPathName,HGLOBAL *phdib, CPalette *ppal);

// ����
public:
	HANDLE m_hDIB;
	UINT nImgWidth; 
	UINT nImgHeight;
	WORD DIBNumColors(LPBYTE lpDIB);

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// ʵ��
public:
	CPalette * ppal;
	HGLOBAL * phdib;
	virtual ~CBmpProcessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
};


