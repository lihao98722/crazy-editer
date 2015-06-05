#pragma once
#include "afxwin.h"


// CCountAllDlg 对话框

class CCountAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCountAllDlg)

public:
	CCountAllDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCountAllDlg();
	
// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	//各个显示数字的编辑框的value型控件变量,因为是显示字符个数，所以为UINT型
	/*
	用value型控件变量可以直接在EditControl上显示出数值，而如果用control型的控件变量
	还需要setwindowtext（）
	*/
	UINT m_AllChar;			//所有字符数
	UINT m_ChineseChar;		//中文字符数
	UINT m_EnglishChar;		//英文字母数
	UINT m_DigitChar;		//数字字符数
	UINT m_SpaceChar;		//空格数
	UINT m_NotationChar;	//半角符号数（并没有把全角符号算在里面）

	//显示统计结果
	void DisplayResult(UINT all,UINT Chinese,UINT English,UINT number,UINT blank, UINT notation);  
	
};
