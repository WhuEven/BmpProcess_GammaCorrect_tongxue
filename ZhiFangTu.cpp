// ZhiFangTu.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "ZhiFangTu.h"
#include "afxdialogex.h"


// ZhiFangTu 对话框

IMPLEMENT_DYNAMIC(ZhiFangTu, CDialogEx)

ZhiFangTu::ZhiFangTu(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZhiFangTu::IDD, pParent)
{

}

ZhiFangTu::~ZhiFangTu()
{
}

void ZhiFangTu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZhiFangTu, CDialogEx)
END_MESSAGE_MAP()


// ZhiFangTu 消息处理程序
