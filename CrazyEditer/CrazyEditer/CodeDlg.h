#pragma once


// CCodeDlg �Ի���

class CCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCodeDlg)

public:
	CCodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCodeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString str_EditCode;
	CString str_EditCodeAgain;
	afx_msg void OnBnClickedOk();
	static CString strCode;
};
