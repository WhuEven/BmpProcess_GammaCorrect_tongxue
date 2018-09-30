// BmpProcessDoc.cpp : CBmpProcessDoc 类的实现
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


// CBmpProcessDoc 构造/析构

CBmpProcessDoc::CBmpProcessDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBmpProcessDoc::~CBmpProcessDoc()
{
}

BOOL CBmpProcessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CBmpProcessDoc 序列化

void CBmpProcessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CBmpProcessDoc 诊断

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
		AfxMessageBox("不支持这种格式的文件!");
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
		// 失败
		ReportSaveLoadException(lpzsPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);

		// 返回FALSE
		return FALSE;
	}

	//定义一些变量存储文件信息
	BITMAPFILEHEADER bmpHeader;          //文件头
	DWORD dwBitsSize;                    //为件长度
	UINT  nNumColors;
	HANDLE hDib;
	HANDLE hDIBtmp;
	LPBITMAPINFOHEADER lpbi;            //文件信息头(指针类型)
	DWORD offBits;                      //位图数据距文件头的偏移量

	dwBitsSize=BmpFile.GetLength();


	hDib=::GlobalAlloc(GMEM_MOVEABLE,(DWORD)(sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD))); 
	if (hDib==0) return false; 
	lpbi=(LPBITMAPINFOHEADER)GlobalLock(hDib);
	if(!lpbi)
	{
		GlobalFree(hDib);
		return FALSE;
	}

	// 尝试读取DIB文件头
	if (BmpFile.Read((LPSTR)&bmpHeader, sizeof(bmpHeader)) != sizeof(bmpHeader))
	{
		// 大小不对，返回NULL。
		return NULL;
	}
	// 判断是否是BMP对象，检查头两个字节是否是"BM"
	if (bmpHeader.bfType != 0x4d42)
	{
		// 非BMP对象，返回NULL。
		AfxMessageBox("不是合法的BMP文件！");
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
		AfxMessageBox("文件打不开");
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
	// TODO: 在此添加命令处理程序代码

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