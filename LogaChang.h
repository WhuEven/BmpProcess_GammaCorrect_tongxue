#pragma once


// LogaChang �Ի���

class LogaChang : public CDialogEx
{
	DECLARE_DYNAMIC(LogaChang)

public:
	LogaChang(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogaChang();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_a;
	double m_b;
	double m_c;
	CButton m_Cancel;
	CButton m_OK;
};
