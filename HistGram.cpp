// HistGram.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "HistGram.h"
#include "afxdialogex.h"
#include "math.h"


// HistGram �Ի���

IMPLEMENT_DYNAMIC(HistGram, CDialogEx)

HistGram::HistGram(CWnd* pParent /*=NULL*/)
	: CDialog(HistGram::IDD, pParent)
{

}

HistGram::HistGram(int nCount[256],CWnd* pParent /*=NULL*/)
	: CDialog(HistGram::IDD, pParent)
{
	
	
		m_IHist=nCount;
	
}

HistGram::~HistGram()
{
}

void HistGram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HistGram, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HistGram ��Ϣ�������


void HistGram::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CPen *pPenBlue = new CPen; //�������ʶ���
	pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0,255)); //��ɫ����
	CPen *pPenBlack = new CPen;
	pPenBlack->CreatePen(PS_SOLID,1,RGB(0,0,0));
	//ѡ�к�ɫ���ʣ������浱ǰ����
	CGdiObject *pOldPen = dc.SelectObject(pPenBlack);
	int i = 0;
	CString str;
	//��������ϵ
	CPoint OPos(50,500),NowPos;
	//����x������
	dc.MoveTo(OPos);
	NowPos.x = 580;
	NowPos.y = 500;
	dc.LineTo(NowPos);
	//���Ƽ�ͷ
	dc.LineTo(575,495);
	dc.MoveTo(575,505);
	//����x������ϵ��
	for (i = 0;i < 256;i++)
	{
		if (i % 10 == 0)
		{
			dc.MoveTo(OPos.x+2*i,OPos.y);
			dc.LineTo(CPoint(OPos.x+2*i,OPos.y-5));
		}
		if (i % 20 == 0)
		{
			str.Format("%d",i);
			dc.TextOut(OPos.x+2*i,OPos.y+1,str);
		}
	}
	//����y������ϵ��
	dc.MoveTo(OPos);
	NowPos.x = OPos.x;
	NowPos.y = 0;
	dc.LineTo(NowPos);
	//���Ƽ�ͷ
	dc.LineTo(NowPos.x-5,NowPos.y+5);
	dc.MoveTo(NowPos);
	dc.LineTo(NowPos.x+5,NowPos.y+5);
	//Ѱ��������������
	int max = 0;
	for (i = 0; i < 256; i++)
	{
		if (max < m_IHist[i])
		{
			max = m_IHist[i];
		}
	}
	//y������ϵ�������ݲ���
	int Tstep = max;
	//y������ϵ���Ŀ̶Ȳ���
	int Ystep = 500/21;
	//��ʾY����Ŀ̶Ⱥ�ϵ��
	for (i = 1; i < 22; i++)
	{
		dc.MoveTo(OPos.x,OPos.y-Ystep*i);
		dc.LineTo(CPoint(OPos.x+5,OPos.y-Ystep*i));
		if (i % 2 == 0)
		{
			str.Format("%d",Tstep*i/2);
			dc.TextOut(0,OPos.y - Ystep*i-10,str);
		}
	}
	//���ƻҶ�ֱ��ͼ
	dc.SelectObject(pPenBlue); //ѡ����ɫ����
	for (i = 0;i < 256;i++)
	{
		NowPos.x = OPos.x + (2 * i);
		NowPos.y = OPos.y;
		dc.MoveTo(NowPos);
		/*NowPos.y = 500 - 500.0f * 20.0f * ImageData[i] / (max * 21);*/
		//y����ֵ����500���¼�
		NowPos.y = 500 - ((float)Ystep*21)* 20.0f * m_IHist[i] / (max * 21);
		dc.LineTo(NowPos);
	}
	//�ָ���ǰ�Ļ���
	dc.SelectObject(pOldPen);
	delete pPenBlue;
	delete pPenBlack;
}
