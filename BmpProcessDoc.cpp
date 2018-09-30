// BmpProcessDoc.cpp : CBmpProcessDoc ���ʵ��
//

#include "stdafx.h"
#include "BmpProcess.h"

#include "BmpProcessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)
#endif


// CBmpProcessDoc

IMPLEMENT_DYNCREATE(CBmpProcessDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpProcessDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE_AS, &CBmpProcessDoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CBmpProcessDoc ����/����

CBmpProcessDoc::CBmpProcessDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CBmpProcessDoc::~CBmpProcessDoc()
{
}

BOOL CBmpProcessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


// CBmpProcessDoc ���л�

void CBmpProcessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CBmpProcessDoc ���

#ifdef _DEBUG
void CBmpProcessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpProcessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

BOOL CBmpProcessDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	char szDrive[_MAX_DRIVE];
	char szDir[_MAX_DIR];
	char szFName[_MAX_FNAME];
	char szExt[_MAX_EXT];
	_splitpath(lpszPathName,szDrive,szDir,szFName,szExt);
	CString strExt=szExt;

	if(strExt==".bmp"||strExt==".BMP")
	{

		m_hDIB=OpenImageBMP(lpszPathName,phdib,ppal);
		if(m_hDIB == NULL)
			return FALSE;
	}
	else
	{
		AfxMessageBox("��֧�����ָ�ʽ���ļ�!");
		return FALSE;
	}
	SetPathName(lpszPathName);
	SetModifiedFlag(FALSE);
	return TRUE;
}

HANDLE CBmpProcessDoc::OpenImageBMP(LPCTSTR lpzsPathName,HGLOBAL *phdib, CPalette *ppal)
{
	CFile BmpFile;
	CFileException fe;
	if(!BmpFile.Open(lpzsPathName,CFile::modeRead,&fe))
	{
		// ʧ��
		ReportSaveLoadException(lpzsPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);

		// ����FALSE
		return FALSE;
	}

	//����һЩ�����洢�ļ���Ϣ
	BITMAPFILEHEADER bmpHeader;          //�ļ�ͷ
	DWORD dwBitsSize;                    //Ϊ������
	UINT  nNumColors;
	HANDLE hDib;
	HANDLE hDIBtmp;
	LPBITMAPINFOHEADER lpbi;            //�ļ���Ϣͷ(ָ������)
	DWORD offBits;                      //λͼ���ݾ��ļ�ͷ��ƫ����

	dwBitsSize=BmpFile.GetLength();


	hDib=::GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD))); 
	if (hDib==0) return false; 
	lpbi=(LPBITMAPINFOHEADER)GlobalLock(hDib);
	if(!lpbi)
	{
		GlobalFree(hDib);
		return FALSE;
	}

	// ���Զ�ȡDIB�ļ�ͷ
	if (BmpFile.Read((LPSTR)&bmpHeader, sizeof(bmpHeader)) != sizeof(bmpHeader))
	{
		// ��С���ԣ�����NULL��
		return NULL;
	}
	// �ж��Ƿ���BMP���󣬼��ͷ�����ֽ��Ƿ���"BM"
	if (bmpHeader.bfType != 0x4d42)
	{
		// ��BMP���󣬷���NULL��
		AfxMessageBox("���ǺϷ���BMP�ļ���");
		return NULL;
	}

	// read the remainder of the bitmap file.

	if(BmpFile.Read((LPBYTE)lpbi,sizeof(BITMAPINFOHEADER))!=sizeof(BITMAPINFOHEADER))
	{
		return NULL;
	}

	if(!(nNumColors=(UINT)lpbi->biClrUsed))
	{
		if(lpbi->biBitCount!=24)
			nNumColors=1<<lpbi->biBitCount;
	}

	if(lpbi->biClrUsed==0)
		lpbi->biClrUsed=nNumColors;
	if(lpbi->biSizeImage==0)
	{
		lpbi->biSizeImage=((((lpbi->biWidth*(DWORD)lpbi->biBitCount)+31)&~31)>>3)*lpbi->biHeight;

	}

	nImgWidth = lpbi->biWidth;
	nImgHeight = lpbi->biHeight;


	GlobalUnlock(hDib);

	hDIBtmp =GlobalReAlloc(hDib,lpbi->biSize+nNumColors*sizeof(RGBQUAD)+lpbi->biSizeImage,0);
	if(!hDIBtmp)
	{
		GlobalFree(hDib);
		return NULL;
	}
	else
		hDib=hDIBtmp;
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);

	if(BmpFile.Read((LPBYTE)(lpbi)+lpbi->biSize,nNumColors*sizeof(RGBQUAD))!=nNumColors*sizeof(RGBQUAD))
	{
		return NULL;
	}

	offBits=lpbi->biSize+nNumColors*sizeof(RGBQUAD);
	if(bmpHeader.bfOffBits!=0L)
		BmpFile.Seek(bmpHeader.bfOffBits,CFile::begin);
	if(BmpFile.Read((LPBYTE)(lpbi)+offBits,lpbi->biSizeImage))
	{
		GlobalUnlock(hDib);
		return hDib;
	}

	return hDib;

}
BOOL CBmpProcessDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFile file;
	CFileException fe;
	BITMAPFILEHEADER bmfHdr;
	LPBITMAPINFOHEADER lpBI;
	DWORD dwDIBSize;

	//CString lpszPathName=filename;
	//HANDLE m_hDIB=m_hDIB;
	if(!file.Open(lpszPathName,CFile::modeCreate|CFile::modeReadWrite|CFile::shareExclusive,&fe))
	{
		AfxMessageBox("�ļ��򲻿�");
	}
	BOOL bSuccess=FALSE;
	BeginWaitCursor();
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock(m_hDIB);
	if(lpBI==NULL)
	{
		return false;
	}
	dwDIBSize=*(LPDWORD)lpBI+256*sizeof(RGBQUAD);
	DWORD dwBmBitsSize;
	dwBmBitsSize= WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount))*lpBI->biHeight;
	dwDIBSize+=dwBmBitsSize;
	lpBI->biSizeImage=dwBmBitsSize;
	bmfHdr.bfType=0x4d42;
	bmfHdr.bfSize=dwDIBSize+sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;
	bmfHdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+lpBI->biSize+256*sizeof(RGBQUAD);
	file.Write((LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER));
	file.Write(lpBI,dwDIBSize);
	EndWaitCursor();
	SetModifiedFlag(FALSE);
	return TRUE;

	return CDocument::OnSaveDocument(lpszPathName);	
}

void CBmpProcessDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������

}


WORD CBmpProcessDoc::DIBNumColors(LPBYTE lpDIB)
{
	WORD wBitCount;
	DWORD dwClrUsed;
	dwClrUsed = ((LPBITMAPINFOHEADER)lpDIB)->biClrUsed;
	if(dwClrUsed)
		return (WORD)dwClrUsed;
	wBitCount =((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	switch(wBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}