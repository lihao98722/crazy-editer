// MyRichEditCtrl.cpp : ʵ���ļ�
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



// CMyRichEditCtrl ��Ϣ�������



void CMyRichEditCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CWnd* pWnd = AfxGetApp()->GetMainWnd();//��ȡ������
	CCrazyEditerDlg *dlg;
	dlg = (CCrazyEditerDlg *)pWnd;
	dlg->ShowCursorPosition(point.x,point.y);  //������ʾ���еĺ���
	CRichEditCtrl::OnLButtonDown(nFlags, point);
}


