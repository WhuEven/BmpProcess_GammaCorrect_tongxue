#pragma once


// LogaChang 对话框

class LogaChang : public CDialogEx
{
	DECLARE_DYNAMIC(LogaChang)

public:
	LogaChang(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LogaChang();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_a;
	double m_b;
	double m_c;
	CButton m_Cancel;
	CButton m_OK;
};
