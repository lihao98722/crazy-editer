// CodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CodeDlg.h"
#include "afxdialogex.h"


 CString CCodeDlg::strCode = NULL;
// CCodeDlg 对话框

IMPLEMENT_DYNAMIC(CCodeDlg, CDialogEx)

CCodeDlg::CCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCodeDlg::IDD, pParent)
	, str_EditCode(_T(""))
	, str_EditCodeAgain(_T(""))
{

}

CCodeDlg::~CCodeDlg()
{
}

void CCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, str_EditCode);
	DDV_MaxChars(pDX, str_EditCode, 10);
	DDX_Text(pDX, IDC_EDIT3, str_EditCodeAgain);
	DDV_MaxChars(pDX, str_EditCodeAgain, 10);
}


BEGIN_MESSAGE_MAP(CCodeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCodeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCodeDlg 消息处理程序


void CCodeDlg::OnBnClickedOk()
{
	UpdateData (TRUE);    //读取两次输入的密码；
	if(str_EditCode == str_EditCodeAgain){
		strCode = str_EditCode;  //保存密码
		CDialogEx::OnOK();
	}else{
		MessageBox("两次输入密码不一致,请重新输入","错误");
	}
	
	
}
