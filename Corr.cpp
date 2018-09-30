// Corr.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "Corr.h"


// CCorr 对话框

IMPLEMENT_DYNAMIC(CCorr, CDialog)

CCorr::CCorr(CWnd* pParent /*=NULL*/)
	: CDialog(CCorr::IDD, pParent)
	, m_Corr(0)
{

}

CCorr::~CCorr()
{
}

void CCorr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CorrValue, m_Corr);
	DDV_MinMaxDouble(pDX, m_Corr, 0, 1);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CCorr, CDialog)
	ON_EN_CHANGE(IDC_CorrValue, &CCorr::OnEnChangeCorrvalue)
	ON_COMMAND(ID_Corr, &CCorr::OnCorr)
END_MESSAGE_MAP()


// CCorr 消息处理程序
void CCorr::OnOK()
{
	CDialog::OnOK();
}

void CCorr::OnCancel()
{
	CDialog::OnCancel();

}

void CCorr::OnEnChangeCorrvalue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCorr::OnCorr()
{
	// TODO: 在此添加命令处理程序代码


}
