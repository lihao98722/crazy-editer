#pragma once


// CDecodeDlg �Ի���

class CDecodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDecodeDlg)

public:
	CDecodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDecodeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditDecode;
	afx_msg void OnBnClickedOk();
	bool checkCode();
};
