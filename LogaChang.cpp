// LogaChang.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "LogaChang.h"
#include "afxdialogex.h"


// LogaChang 对话框

IMPLEMENT_DYNAMIC(LogaChang, CDialogEx)

LogaChang::LogaChang(CWnd* pParent /*=NULL*/)
	: CDialogEx(LogaChang::IDD, pParent)
{

	m_a = 0.0;
	m_b = 0.0;
	m_c = 0.0;
}

LogaChang::~LogaChang()
{
}

void LogaChang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_a, m_a);
	DDX_Text(pDX, IDC_b, m_b);
	DDX_Text(pDX, IDC_c, m_c);
	DDV_MinMaxDouble(pDX, m_c, 0, 255);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_OK);
}


BEGIN_MESSAGE_MAP(LogaChang, CDialogEx)
END_MESSAGE_MAP()


// LogaChang 消息处理程序
