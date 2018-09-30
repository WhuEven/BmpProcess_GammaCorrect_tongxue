// BmpProcessView.cpp : CBmpProcessView ���ʵ��
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "Corr.h"
#include "BmpProcessDoc.h"
#include "BmpProcessView.h"
#include "math.h"
#include "LogaChang.h"
#include "HistGram.h" 
#include "Quanlity.h"
#include "ImgEvaluation.h"

 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// �����������Ŀ��
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)

// �����������ĸ߶�
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// �ж��Ƿ���Win 3.0��DIB
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
// DIB����
#define PALVERSION   0x300


// CBmpProcessView

IMPLEMENT_DYNCREATE(CBmpProcessView, CView)

BEGIN_MESSAGE_MAP(CBmpProcessView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Corr, &CBmpProcessView::OnCorr)
	ON_COMMAND(ID_32774, &CBmpProcessView::On32774)
	ON_COMMAND(ID_FILE_SAVE_AS, &CBmpProcessView::OnFileSaveAs)
	ON_COMMAND(ID_32775, &CBmpProcessView::On32775)
	/*ON_COMMAND(ID_32776, &CBmpProcessView::OnZHIFANGTU)*/
	/*ON_COMMAND(ID_32778, &CBmpProcessView::On32778)*/
	ON_COMMAND(ID_32780, &CBmpProcessView::On32780)
	ON_COMMAND(ID_32779, &CBmpProcessView::Onzhifangtu)
	/*ON_COMMAND(ID_32781, &CBmpProcessView::OnTwo)*/
	ON_COMMAND(ID_32782, &CBmpProcessView::On32782)
	ON_COMMAND(ID_Evaluation, &CBmpProcessView::OnEvaluation)
	ON_COMMAND(ID_xinhaobi, &CBmpProcessView::Onxinhaobi)
END_MESSAGE_MAP()

// CBmpProcessView ����/����

CBmpProcessView::CBmpProcessView()
{
	// TODO: �ڴ˴���ӹ������

}

CBmpProcessView::~CBmpProcessView()
{
}

BOOL CBmpProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBmpProcessView ����

void CBmpProcessView::OnDraw(CDC *pDC)
{
	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	PaintDIB(pDC->GetSafeHdc(),m_rcDIB,pDoc->m_hDIB,m_rcDIB,NULL,SRCCOPY);
}

BOOL CBmpProcessView::PaintDIB(HDC hDC,LPRECT lpDCRect,HANDLE hDIB,LPRECT lpDIBRect,HPALETTE hPal,DWORD dwRop)
{
	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	BOOL bSuccess = false;
	HPALETTE hOldPal = NULL;

	if(!hDIB)
		return FALSE;

	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr+sizeof(BITMAPINFOHEADER)+DIBNumColors(lpDIBHdr)*sizeof(RGBQUAD);

	if(!hPal)
		hPal= CreateDIBPalette(lpDIBHdr);
	if(hPal)
	{
		hOldPal =SelectPalette(hDC,hPal,TRUE);
		RealizePalette(hDC);
	}

	SetStretchBltMode(hDC,COLORONCOLOR);

	bSuccess = StretchDIBits(hDC,lpDCRect->left,lpDCRect->top,
		RECTWIDTH(lpDCRect),
		RECTHEIGHT(lpDCRect),lpDIBRect->left,
		((LPBITMAPINFOHEADER)lpDIBHdr)->biHeight-lpDIBRect->top-RECTHEIGHT(lpDIBRect),
		RECTWIDTH(lpDIBRect),
		RECTHEIGHT(lpDIBRect),
		lpDIBBits,
		(LPBITMAPINFO)lpDIBHdr,
		DIB_RGB_COLORS,
		SRCCOPY);

	GlobalUnlock(hDIB);
	if(hOldPal)
		SelectPalette(hDC,hOldPal,FALSE);
	GlobalUnlock(hDIB);

	return bSuccess;

}

WORD CBmpProcessView::DIBNumColors(LPBYTE lpDIB)
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

HPALETTE CBmpProcessView::CreateDIBPalette(LPBYTE lpbi)
{
	LPLOGPALETTE lpPal;
	HANDLE hLogPal;
	HPALETTE hPal = NULL;
	LPBITMAPINFO lpbmi;

	// �����Ƿ���Win3.0 DIB�ı��
	BOOL bWinStyleDIB;

	int i,wNumColors;

	if(!lpbi)
		return NULL;
	lpbmi =(LPBITMAPINFO)lpbi;
	wNumColors =DIBNumColors(lpbi);

	// �ж��Ƿ���WIN3.0��DIB
	bWinStyleDIB = IS_WIN30_DIB(lpbi);

	if(wNumColors)
	{
		hLogPal = GlobalAlloc(GHND,sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*wNumColors);

		if(!hLogPal)
			return NULL;

		lpPal = (LPLOGPALETTE)GlobalLock(hLogPal);

		lpPal->palVersion = 0x300;
		lpPal->palNumEntries = wNumColors;



		for(i=0;i<wNumColors;i++)
		{	if (bWinStyleDIB)
		{
			lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed;
			lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
			lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue;
			lpPal->palPalEntry[i].peFlags = 0;}
		}

		hPal =CreatePalette(lpPal);
		if(!hPal)
		{
			GlobalUnlock(hLogPal);
			GlobalFree(hLogPal);
			return NULL;
		}
	}
	GlobalUnlock(hLogPal);
	GlobalFree(hLogPal);
	return hPal;
}

void CBmpProcessView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSize sizeTotal;
	if(pDoc->m_hDIB!=NULL)
	{
		LPBITMAPINFOHEADER lpDIB = (LPBITMAPINFOHEADER)GlobalLock(pDoc->m_hDIB);

		m_rcDIB.left = 0;
		m_rcDIB.top = 0;
		sizeTotal.cx = m_rcDIB.right =((LPBITMAPINFOHEADER)lpDIB)->biWidth;
		sizeTotal.cy = m_rcDIB.bottom = ((LPBITMAPINFOHEADER)lpDIB)->biHeight;
		GlobalUnlock(pDoc->m_hDIB);
	}
	else 
	{
		m_rcDIB.SetRectEmpty();
		sizeTotal.cx = sizeTotal.cy = 100;
	}

}


// CBmpProcessView ��ӡ

BOOL CBmpProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBmpProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBmpProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CBmpProcessView ���

#ifdef _DEBUG
void CBmpProcessView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpProcessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpProcessDoc* CBmpProcessView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpProcessDoc)));
	return (CBmpProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CBmpProcessView ��Ϣ�������

void CBmpProcessView::OnCorr()
{
	// TODO: �ڴ���������������
	CCorr dlg;
   if(dlg.DoModal()==IDOK)
   {
	   
	CBmpProcessDoc* ppt = GetDocument();
	ASSERT_VALID(ppt);
	ImgWidth = ppt->nImgWidth;
	ImgHeight = ppt->nImgHeight;

	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	int x,y;
	float r;
    r=dlg.m_Corr;

	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = ppt->m_hDIB;

	if(!hDIB)
		return;

	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr+sizeof(BITMAPINFOHEADER)+DIBNumColors(lpDIBHdr)*sizeof(RGBQUAD);


	for(x = 0; x < ImgHeight; x++)
	{
		// ÿ��
		for(y = 0; y < ImgWidth; y++)
		{
			*(lpDIBBits+x*ImgWidth+y) = 255*pow(*(lpDIBBits+x*ImgWidth+y)/255.0,1.0/r);

		}
	}

	ppt->UpdateAllViews(NULL);	
	  
   }
	
}


void CBmpProcessView::On32774()
{
	// TODO: �ڴ���������������

	  
}


void CBmpProcessView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	CBmpProcessDoc*pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	CFileDialog DlgFileSave(FALSE);
	DlgFileSave.m_ofn.lpstrTitle="���Ϊ";
	DlgFileSave.m_ofn.lpstrFilter="Bmp File(*.bmp)\0*.bmp\0Raw File(*.raw)\0*.raw\0\0";
	DlgFileSave.m_ofn.lpstrDefExt="bmp";
	if (DlgFileSave.DoModal()==IDOK);
	{
		pDoc->OnSaveDocument(DlgFileSave.GetPathName());
	}

}


void CBmpProcessView::On32775()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	 LogaChang dlg;
   if(dlg.DoModal()==IDOK)
   {
	   
	CBmpProcessDoc* ppt = GetDocument();
	ASSERT_VALID(ppt);
	ImgWidth = ppt->nImgWidth;
	ImgHeight = ppt->nImgHeight;

	LPBYTE lpDIBHdr;
	LPBYTE lpDIBBits;
	int x,y;
	double a,b,c;
	a=dlg.m_a;
	b=dlg.m_b;
	c=dlg.m_c;


	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = ppt->m_hDIB;

	if(!hDIB)
		return;

	lpDIBHdr = (LPBYTE)GlobalLock(hDIB);
	lpDIBBits = lpDIBHdr+sizeof(BITMAPINFOHEADER)+DIBNumColors(lpDIBHdr)*sizeof(RGBQUAD);


	for(x = 0; x < ImgHeight; x++)
	{
		// ÿ��
		for(y = 0; y < ImgWidth; y++)
		{
			*(lpDIBBits+x*ImgWidth+y) =a+log(double(*(lpDIBBits+x*ImgWidth+y)+1))/(b*log(c));
				
		}
	}

	ppt->UpdateAllViews(NULL);	
	  
   }
	
}



void CBmpProcessView::On32780()
{
	// TODO: �ڴ���������������
	
	//��ȡͼ������ָ��
	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ImgWidth = pDoc->nImgWidth;
	ImgHeight = pDoc->nImgHeight;


	LPBYTE lpDIBBits;
	int i,j;

	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = pDoc->m_hDIB;

	if(!hDIB)
		return;

	//��ȡ��ǰͼ������ָ�룬����һ
	LPBITMAPINFOHEADER lpBI;
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock(pDoc->m_hDIB);//��ȡBItMapInfo�ṹ������
	lpDIBBits = (LPBYTE)lpBI+sizeof(BITMAPINFOHEADER)+DIBNumColors((LPBYTE)lpBI)*sizeof(RGBQUAD);

	
	//����ͼ��ֱ��ͼ
	// ֱ��ͼ
	int	nCount[256]; 
	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
	{
		// ����
		nCount[i] = 0;
	}
	// ��������Ҷ�ֵ�ļ��������õ�ֱ��ͼ
	for (i = 0; i < ImgHeight; i ++)
	{
		for (j = 0; j < ImgWidth; j ++)
		{
			BYTE GrayValue = *(lpDIBBits+i*ImgWidth+j);

			// ������1
			nCount[GrayValue]++;
		}
	}

	//�����ۻ�ֱ��ͼ
	unsigned int nByMap[256];
	long ImgSize=ImgWidth*ImgHeight;
	unsigned int nTemp;			
	for (int i=0;i<256;i++)
	{
		nTemp=0;
		for (int j=0;j<=i;j++)
		{
			nTemp+=nCount[j];
		}
		nByMap[i]=(BYTE)(nTemp/(double)ImgSize*255);
	}

	//�Ҷ�ӳ��
	BYTE BGrayValue;
	for (int i=0;i<ImgHeight;i++)
		for (int j=0;j<ImgWidth;j++)
		{
			BGrayValue=*(lpDIBBits+i*ImgWidth+j);
			*(lpDIBBits+i*ImgWidth+j)=nByMap[BGrayValue];
		}

	pDoc->UpdateAllViews(NULL);

}


void CBmpProcessView::Onzhifangtu()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	//////////////////////////////////////////////////////////////////////////
	//��ȡ��ǰͼ������ָ��

	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ImgWidth = pDoc->nImgWidth;
	ImgHeight = pDoc->nImgHeight;


	LPBYTE lpDIBBits;
	int i,j;

	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = pDoc->m_hDIB;

	if(!hDIB)
		return;

	//��ȡ��ǰͼ������ָ�룬����һ
	LPBITMAPINFOHEADER lpBI;
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock(pDoc->m_hDIB);//��ȡBItMapInfo�ṹ������
	lpDIBBits = (LPBYTE)lpBI+sizeof(BITMAPINFOHEADER)+DIBNumColors((LPBYTE)lpBI)*sizeof(RGBQUAD);

	//����ֱ��ͼ
	// ��ʱ����
	long nTemp;
	// ֱ��ͼ
	int	nCount[256]; 
	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
	{
		// ����
		nCount[i] = 0;
	}
	// ��������Ҷ�ֵ�ļ��������õ�ֱ��ͼ
	for (i = 0; i < ImgHeight; i ++)
	{
		for (j = 0; j < ImgWidth; j ++)
		{
			BYTE GrayValue = *(lpDIBBits+i*ImgWidth+j);

			// ������1
			nCount[GrayValue]++;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//������DLGHISTGRAM�Ի���
	HistGram dlgHist(nCount);
	dlgHist.DoModal();
	/*dlgHist.DoModalmain(pDoc);*/

	pDoc->UpdateAllViews(NULL);

}


void CBmpProcessView::On32782()
{
	// TODO: �ڴ���������������
	
	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ImgWidth = pDoc->nImgWidth;
	ImgHeight = pDoc->nImgHeight;


	LPBYTE lpDIBBits;
	int i,j;

	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = pDoc->m_hDIB;

	if(!hDIB)
		return;

	//��ȡ��ǰͼ������ָ�룬����һ
	LPBITMAPINFOHEADER lpBI;
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock(pDoc->m_hDIB);//��ȡBItMapInfo�ṹ������
	lpDIBBits = (LPBYTE)lpBI+sizeof(BITMAPINFOHEADER)+DIBNumColors((LPBYTE)lpBI)*sizeof(RGBQUAD);

	int Matrix[4][4]={{0,8,2,10},{4,12,6,14},{3,11,1,9},{7,15,5,13}};
	int m,n;
	for(i=0;i<ImgHeight;i++)
	{
		m=i%4;
		for(j=0;j<ImgWidth;j++)
		{
			n=j%4;
			if(*(lpDIBBits+i*ImgWidth+j)/255.0>=Matrix[m][n]/15.0)
			{
				*(lpDIBBits+i*ImgWidth+j)=255;
			}
			else
			{
				*(lpDIBBits+i*ImgWidth+j)=0;
			}
		 }
	}
	pDoc->UpdateAllViews(NULL);

}


void CBmpProcessView::OnEvaluation()
{
	// TODO: �ڴ���������������
	CBmpProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ImgWidth = pDoc->nImgWidth;
	ImgHeight = pDoc->nImgHeight;


	LPBYTE lpDIBBits;
	int i;

	HPALETTE hOldPal = NULL;
	HANDLE hDIB;
	hDIB = pDoc->m_hDIB;

	if(!hDIB)
		return;

	//��ȡ��ǰͼ������ָ�룬����һ
	LPBITMAPINFOHEADER lpBI;
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock(pDoc->m_hDIB);//��ȡBItMapInfo�ṹ������
	lpDIBBits = (LPBYTE)lpBI+sizeof(BITMAPINFOHEADER)+DIBNumColors((LPBYTE)lpBI)*sizeof(RGBQUAD);

	//////////////////////////////////////////////////////////////////////////
	//�ҶȾ�ֵ
    unsigned long GrayAmount=0;
    int a;
    for(a=0;a<ImgHeight*ImgWidth;a++)
    {
		GrayAmount+=*(lpDIBBits+a);
	
     }
    double GrayMean;
    GrayMean=(double)GrayAmount/ImgWidth/ImgHeight;


	//////////////////////////////////////////////////////////////////////////
	//������������
	double dVar=0.0;
	double dOffset=0.0;
	for(i=0;i<ImgWidth*ImgHeight;i++)
	{
		dOffset=*(lpDIBBits+i)-GrayMean;
		dVar+=dOffset*dOffset;
	}
	dVar=sqrt(dVar/ImgWidth/ImgHeight);

	float prob[256];
	for ( i=0;i<256;i++)
	{   
		prob[i]=(float)*(lpDIBBits+i)/(float)(ImgWidth*ImgHeight);
	}
	//////////////////////////////////////////////////////////////////////////
	//������Ϣ��

	float H =0.0;//��Ϣ��
	for ( i=0;i<256;i++)
	{
		if(*(lpDIBBits+i)!=0)
			H=H -(prob[i]*log(prob[i]))/log(2.0);
	}

	//////////////////////////////////////////////////////////////////////////
	//��������
	Quanlity qua;
	qua.m_huidu=GrayMean;
	qua.m_junfanggen=dVar;
	qua.m_shang=H;
	qua.DoModal();
    }



void CBmpProcessView::Onxinhaobi()
{
	// TODO: �ڴ���������������
	ImgEvaluation DIALOG3;
	DIALOG3.DoModal();
}
