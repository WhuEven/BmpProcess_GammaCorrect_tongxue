// ImgEvaluation.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "ImgEvaluation.h"
#include "afxdialogex.h"
#include "BmpProcessDoc.h"
#include "math.h"

// ImgEvaluation �Ի���

IMPLEMENT_DYNAMIC(ImgEvaluation, CDialogEx)

ImgEvaluation::ImgEvaluation(CWnd* pParent /*=NULL*/)
	: CDialogEx(ImgEvaluation::IDD, pParent)
{

	m_Mse = 0.0f;
	m_Psnr = 0.0f;
}

ImgEvaluation::~ImgEvaluation()
{
}

void ImgEvaluation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_reference, m_reference);
	DDX_Control(pDX, IDC_target, m_target);
	DDX_Control(pDX, IDC_Imgevaluate, m_OnImgevaluate);
	DDX_Text(pDX, IDC_mse, m_Mse);
	DDX_Text(pDX, IDC_psnr, m_Psnr);
	//  DDX_Control(pDX, IDOK, m_ImgOK);
	//  DDX_Control(pDX, IDCANCEL, m_ImgCancel);
}


BEGIN_MESSAGE_MAP(ImgEvaluation, CDialogEx)
	ON_BN_CLICKED(IDC_target, &ImgEvaluation::OnBnClickedtarget)
	ON_BN_CLICKED(IDC_reference, &ImgEvaluation::OnBnClickedreference)
	ON_BN_CLICKED(IDC_Imgevaluate, &ImgEvaluation::OnBnClickedImgevaluate)
END_MESSAGE_MAP()


// ImgEvaluation ��Ϣ�������


void ImgEvaluation::OnBnClickedtarget()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dialogOpen(TRUE);
	dialogOpen.m_ofn.lpstrFilter="BMP Files(*bmp)\*bmp";
	if  (dialogOpen.DoModal()==IDOK)
	{
		TargetPath=dialogOpen.GetPathName();
		m_target.SetWindowText(TargetPath);
	}
	else
	{
		m_target.SetWindowText("ѡ��Ŀ��ͼ��·��");

	}
}
void ImgEvaluation::OnBnClickedreference()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dialogOpen(TRUE);
	dialogOpen.m_ofn.lpstrFilter="BMP Files(*bmp)\*bmp";
	if  (dialogOpen.DoModal()==IDOK)
	{
		ReferPath=dialogOpen.GetPathName();
		m_reference.SetWindowText(ReferPath);
	}
	else
	{
		m_reference.SetWindowText("ѡ��ο�ͼ��·��");

	}
}


void ImgEvaluation::OnBnClickedImgevaluate()
{
	
	CBmpProcessDoc *ReferDoc= new CBmpProcessDoc();
	ReferDoc->OnOpenDocument(ReferPath.GetBuffer(0));

	unsigned int ReferImgWidth = ReferDoc->nImgWidth;
	unsigned int ReferImgHeight =  ReferDoc->nImgHeight;

	LPBYTE ReferimgHdr;  
	LPBYTE ReferimgBits;

	HANDLE ReferHandle;
	ReferHandle=ReferDoc->m_hDIB;
    if (!ReferHandle)
		return;
	
	ReferimgHdr = (LPBYTE)GlobalLock(ReferHandle);  
	ReferimgBits=(LPBYTE)ReferimgHdr+sizeof(BITMAPINFOHEADER)+ReferDoc->DIBNumColors((LPBYTE)ReferimgHdr)*sizeof(RGBQUAD);
  

	//----------------------------------
	CBmpProcessDoc *TargetDoc= new CBmpProcessDoc();
	TargetDoc->OnOpenDocument(TargetPath.GetBuffer(0));

    unsigned int TargetImgWidth =  ReferDoc->nImgWidth;
	unsigned int TargetImgHeight =  ReferDoc->nImgHeight;

    LPBYTE TargetimgHdr;  
	LPBYTE TargetimgBits; 
	HANDLE TargetHandle;
	TargetHandle=TargetDoc->m_hDIB;

	
	if (!TargetHandle)
		return;
    TargetimgHdr = (LPBYTE)GlobalLock(TargetHandle);  
    TargetimgBits=(LPBYTE)TargetimgHdr+sizeof(BITMAPINFOHEADER)+TargetDoc->DIBNumColors((LPBYTE)TargetimgHdr)*sizeof(RGBQUAD);

	if (ReferImgHeight!=TargetImgHeight||ReferImgWidth!=TargetImgWidth) 
	{
		MessageBox("�򿪵�����ͼ���С��ͬ");
			return;
	}
	if(TargetPath==""||ReferPath=="")
	{
		MessageBox("�ο�ͼ���Ŀ��ͼ��Ϊͬһ��ͼ��");
			return;
	}
	

	//����MSE
	 int i,j;
	 float MSE=0.0;
	 float Sum=0;
	for (i=0;i<ReferImgHeight;i++)
	{	
		for (j=0;j<ReferImgWidth;j++)
		{
			Sum+=pow((*(ReferimgBits+ReferImgWidth*i+j)-*(TargetimgBits+TargetImgWidth*i+j)),2.0);
		}
	}
	MSE=pow(Sum/(double)(ReferImgWidth*ReferImgHeight),0.5);

		float PSNR=0.0;
	PSNR=10*log10(255*255*ReferImgHeight*ReferImgWidth/(double)Sum);

	m_Mse=MSE;
	m_Psnr=PSNR;
	GlobalUnlock(ReferHandle);
	GlobalUnlock(TargetHandle);
	UpdateData(NULL);

}



