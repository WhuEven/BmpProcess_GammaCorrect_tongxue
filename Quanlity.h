#pragma once


// Quanlity �Ի���

class Quanlity : public CDialogEx
{
	DECLARE_DYNAMIC(Quanlity)

public:
	Quanlity(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Quanlity();

// �Ի�������
	enum { IDD = IDD_zhiliang };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_huidu;
	float m_junfanggen;
	CButton m_QCancel;
	CButton m_QOK;
	float m_shang;
	afx_msg void OnStnClickedshanzhi();
};
