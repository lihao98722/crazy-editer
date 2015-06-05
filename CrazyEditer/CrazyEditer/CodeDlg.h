#pragma once


// CCodeDlg 对话框

class CCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCodeDlg)

public:
	CCodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCodeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString str_EditCode;
	CString str_EditCodeAgain;
	afx_msg void OnBnClickedOk();
	static CString strCode;
};
