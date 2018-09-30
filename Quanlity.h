#pragma once


// Quanlity 对话框

class Quanlity : public CDialogEx
{
	DECLARE_DYNAMIC(Quanlity)

public:
	Quanlity(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Quanlity();

// 对话框数据
	enum { IDD = IDD_zhiliang };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_huidu;
	float m_junfanggen;
	CButton m_QCancel;
	CButton m_QOK;
	float m_shang;
	afx_msg void OnStnClickedshanzhi();
};
