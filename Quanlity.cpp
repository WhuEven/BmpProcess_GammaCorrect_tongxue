// Quanlity.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BmpProcess.h"
#include "Quanlity.h"
#include "afxdialogex.h"


// Quanlity �Ի���

IMPLEMENT_DYNAMIC(Quanlity, CDialogEx)

Quanlity::Quanlity(CWnd* pParent /*=NULL*/)
	: CDialogEx(Quanlity::IDD, pParent)
{

	m_huidu = 0.0f;
	m_junfanggen = 0.0f;

	m_shang = 0.0f;
}

Quanlity::~Quanlity()
{
}

void Quanlity::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_huidujunzhi, m_huidu);
	DDX_Text(pDX, IDC_junfanggen, m_junfanggen);
	/*DDX_Text(pDX, IDC_xinzaobi, m_xinzaobi);*/
	DDX_Control(pDX, IDCANCEL, m_QCancel);
	DDX_Control(pDX, IDOK, m_QOK);
	DDX_Text(pDX, IDC_shanzhi, m_shang);
}


BEGIN_MESSAGE_MAP(Quanlity, CDialogEx)
	ON_STN_CLICKED(IDC_shanzhi, &Quanlity::OnStnClickedshanzhi)
END_MESSAGE_MAP()


// Quanlity ��Ϣ�������


void Quanlity::OnStnClickedshanzhi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
