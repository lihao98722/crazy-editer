#pragma once


// CDecodeDlg 对话框

class CDecodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDecodeDlg)

public:
	CDecodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDecodeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditDecode;
	afx_msg void OnBnClickedOk();
	bool checkCode();
};
