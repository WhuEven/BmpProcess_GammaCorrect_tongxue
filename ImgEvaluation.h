#pragma once


// ImgEvaluation 对话框

class ImgEvaluation : public CDialogEx
{
	DECLARE_DYNAMIC(ImgEvaluation)

public:
	ImgEvaluation(CWnd* pParent = NULL);   // 标准构造函数
	ImgEvaluation(CString imgpath,CWnd* pParent=NULL);//重载函数
	virtual ~ImgEvaluation();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
