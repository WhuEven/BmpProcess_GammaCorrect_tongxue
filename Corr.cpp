// Corr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "Corr.h"


// CCorr �Ի���

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


// CCorr ��Ϣ�������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CCorr::OnCorr()
{
	// TODO: �ڴ���������������


}
