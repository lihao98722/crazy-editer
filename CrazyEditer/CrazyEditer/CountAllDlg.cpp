
]// CountAllDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CountAllDlg.h"
#include "afxdialogex.h"


// CCountAllDlg 对话框

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
	//默认初始化就行了
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

//显示统计结果
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


// CCountAllDlg 消息处理程序



