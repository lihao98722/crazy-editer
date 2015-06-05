
]// CountAllDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CountAllDlg.h"
#include "afxdialogex.h"


// CCountAllDlg �Ի���

IMPLEMENT_DYNAMIC(CCountAllDlg, CDialogEx)

CCountAllDlg::CCountAllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountAllDlg::IDD, pParent)
	, m_AllChar(0)
	, m_ChineseChar(0)
	, m_EnglishChar(0)
	, m_DigitChar(0)
	, m_SpaceChar(0)
	, m_NotationChar(0)
{
	//Ĭ�ϳ�ʼ��������
}

CCountAllDlg::~CCountAllDlg()
{
}

void CCountAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ALLCHAR, m_AllChar);
	DDX_Text(pDX, IDC_CHINESECHAR, m_ChineseChar);
	DDX_Text(pDX, IDC_ENGLISHCHAR, m_EnglishChar);
	DDX_Text(pDX, IDC_DIGITCHAR, m_DigitChar);
	DDX_Text(pDX, IDC_SPACECHAR, m_SpaceChar);
	DDX_Text(pDX, IDC_NOTATIONCHAR, m_NotationChar);
}

//��ʾͳ�ƽ��
void CCountAllDlg::DisplayResult(UINT all,UINT Chinese,UINT English,UINT number,UINT blank, UINT natation)
{
	m_AllChar = all;
	m_ChineseChar = Chinese;
	m_EnglishChar = English;
	m_DigitChar = number;
	m_SpaceChar = blank;
	m_NotationChar = natation;
}


BEGIN_MESSAGE_MAP(CCountAllDlg, CDialogEx)
END_MESSAGE_MAP()


// CCountAllDlg ��Ϣ�������



