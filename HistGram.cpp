// HistGram.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "HistGram.h"
#include "afxdialogex.h"
#include "math.h"


// HistGram 对话框

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


// HistGram 消息处理程序


void HistGram::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CPen *pPenBlue = new CPen; //创建画笔对象
	pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0,255)); //蓝色画笔
	CPen *pPenBlack = new CPen;
	pPenBlack->CreatePen(PS_SOLID,1,RGB(0,0,0));
	//选中黑色画笔，并保存当前画笔
	CGdiObject *pOldPen = dc.SelectObject(pPenBlack);
	int i = 0;
	CString str;
	//绘制坐标系
	CPoint OPos(50,500),NowPos;
	//绘制x坐标轴
	dc.MoveTo(OPos);
	NowPos.x = 580;
	NowPos.y = 500;
	dc.LineTo(NowPos);
	//绘制箭头
	dc.LineTo(575,495);
	dc.MoveTo(575,505);
	//绘制x轴坐标系数
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
	//绘制y轴坐标系数
	dc.MoveTo(OPos);
	NowPos.x = OPos.x;
	NowPos.y = 0;
	dc.LineTo(NowPos);
	//绘制箭头
	dc.LineTo(NowPos.x-5,NowPos.y+5);
	dc.MoveTo(NowPos);
	dc.LineTo(NowPos.x+5,NowPos.y+5);
	//寻求数组最大的数据
	int max = 0;
	for (i = 0; i < 256; i++)
	{
		if (max < m_IHist[i])
		{
			max = m_IHist[i];
		}
	}
	//y轴坐标系数的数据步长
	int Tstep = max;
	//y轴坐标系数的刻度步长
	int Ystep = 500/21;
	//显示Y坐标的刻度和系数
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
	//绘制灰度直方图
	dc.SelectObject(pPenBlue); //选择蓝色画笔
	for (i = 0;i < 256;i++)
	{
		NowPos.x = OPos.x + (2 * i);
		NowPos.y = OPos.y;
		dc.MoveTo(NowPos);
		/*NowPos.y = 500 - 500.0f * 20.0f * ImageData[i] / (max * 21);*/
		//y坐标值，以500往下减
		NowPos.y = 500 - ((float)Ystep*21)* 20.0f * m_IHist[i] / (max * 21);
		dc.LineTo(NowPos);
	}
	//恢复以前的画笔
	dc.SelectObject(pOldPen);
	delete pPenBlue;
	delete pPenBlack;
}
