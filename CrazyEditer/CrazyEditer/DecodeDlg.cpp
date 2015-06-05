// DecodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "DecodeDlg.h"
#include "afxdialogex.h"
#include "CodeDlg.h"

// CDecodeDlg �Ի���

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


// CDecodeDlg ��Ϣ�������


void CDecodeDlg::OnBnClickedOk()
{
	if(checkCode()){
		CDialogEx::OnOK();
	}else{
		MessageBox("�������������һ�飡","����");
	}
	
}




bool CDecodeDlg::checkCode()
{
	UpdateData (TRUE);    //��ȡ���ܵ�����
	return (m_EditDecode == CCodeDlg::strCode);
}
