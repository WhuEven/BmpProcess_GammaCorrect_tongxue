#pragma once


// CCorr 对话框

class CCorr : public CDialog
{
	DECLARE_DYNAMIC(CCorr)

public:
	CCorr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCorr();
// 对话框数据
	enum { IDD = IDD_DLGCORR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_Corr;
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnEnChangeCorrvalue();
	CButton m_btnCancel;
	CButton m_btnOK;
	afx_msg void OnCorr();
};
