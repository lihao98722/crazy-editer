#pragma once


// CCountString 对话框

class CCountString : public CDialogEx
{
	DECLARE_DYNAMIC(CCountString)

public:
	CCountString(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCountString();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//EditControl的value型控件变量
	CString m_StringToCount;		//此对话框编辑区里的内容，即需要统计的字符串
	UINT resultOfCount;				//字符串个数

	//程序主编辑区内容
	CString text;				

	//获取主编辑区内容的处理函数
	void SetText (CString);

	afx_msg void OnBnClickedCountstring();
};
