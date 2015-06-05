// DecodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "DecodeDlg.h"
#include "afxdialogex.h"
#include "CodeDlg.h"

// CDecodeDlg 对话框

IMPLEMENT_DYNAMIC(CDecodeDlg, CDialogEx)

CDecodeDlg::CDecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDecodeDlg::IDD, pParent)
	, m_EditDecode(_T(""))
{

}

CDecodeDlg::~CDecodeDlg()
{
}

void CDecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EditDecode);
	DDV_MaxChars(pDX, m_EditDecode, 10);
}


BEGIN_MESSAGE_MAP(CDecodeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDecodeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDecodeDlg 消息处理程序


void CDecodeDlg::OnBnClickedOk()
{
	if(checkCode()){
		CDialogEx::OnOK();
	}else{
		MessageBox("密码错误！请再输一遍！","错误");
	}
	
}




bool CDecodeDlg::checkCode()
{
	UpdateData (TRUE);    //读取解密的密码
	return (m_EditDecode == CCodeDlg::strCode);
}
