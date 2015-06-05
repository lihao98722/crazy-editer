// CodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CodeDlg.h"
#include "afxdialogex.h"


 CString CCodeDlg::strCode = NULL;
// CCodeDlg �Ի���

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


// CCodeDlg ��Ϣ�������


void CCodeDlg::OnBnClickedOk()
{
	UpdateData (TRUE);    //��ȡ������������룻
	if(str_EditCode == str_EditCodeAgain){
		strCode = str_EditCode;  //��������
		CDialogEx::OnOK();
	}else{
		MessageBox("�����������벻һ��,����������","����");
	}
	
	
}
