#pragma once


// ImgEvaluation �Ի���

class ImgEvaluation : public CDialogEx
{
	DECLARE_DYNAMIC(ImgEvaluation)

public:
	ImgEvaluation(CWnd* pParent = NULL);   // ��׼���캯��
	ImgEvaluation(CString imgpath,CWnd* pParent=NULL);//���غ���
	virtual ~ImgEvaluation();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_reference;
	CButton m_target;
	CButton m_OnImgevaluate;
	float m_Mse;
	float m_Psnr;

	afx_msg void OnBnClickedtarget();
	afx_msg void OnBnClickedreference();
	afx_msg void OnBnClickedImgevaluate();

	CString TargetPath;
	CString ReferPath;
};
