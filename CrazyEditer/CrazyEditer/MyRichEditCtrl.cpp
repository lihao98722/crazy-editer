// MyRichEditCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CrazyEditerDlg.h"  
#include "MyRichEditCtrl.h"


// CMyRichEditCtrl

IMPLEMENT_DYNAMIC(CMyRichEditCtrl, CRichEditCtrl)

CMyRichEditCtrl::CMyRichEditCtrl()
{

}

CMyRichEditCtrl::~CMyRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyRichEditCtrl, CRichEditCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyRichEditCtrl 消息处理程序



void CMyRichEditCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CWnd* pWnd = AfxGetApp()->GetMainWnd();//获取主窗口
	CCrazyEditerDlg *dlg;
	dlg = (CCrazyEditerDlg *)pWnd;
	dlg->ShowCursorPosition(point.x,point.y);  //调用显示行列的函数
	CRichEditCtrl::OnLButtonDown(nFlags, point);
}


