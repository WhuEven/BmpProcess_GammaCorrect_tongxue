#pragma once


// CCorr �Ի���

class CCorr : public CDialog
{
	DECLARE_DYNAMIC(CCorr)

public:
	CCorr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCorr();
// �Ի�������
	enum { IDD = IDD_DLGCORR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
