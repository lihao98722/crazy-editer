// Welcome.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "Welcome.h"


// Welcome

IMPLEMENT_DYNAMIC(Welcome, CWnd)

Welcome::Welcome()
{

}

Welcome::~Welcome()
{
	// delete指针变量并设为NULL
	ASSERT(c_pWelcomeWnd == this);
	c_pWelcomeWnd = NULL;
}


BEGIN_MESSAGE_MAP(Welcome, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER() //定时器
END_MESSAGE_MAP()



// Welcome 消息处理程序

BOOL Welcome::c_bShowWelcomeWnd;
Welcome* Welcome::c_pWelcomeWnd;

//允许欢迎画面，在初始化程序，即InitInstance()时需要调用到
void Welcome::EnableWelcomeScreen(BOOL bEnable)
{
	c_bShowWelcomeWnd = bEnable;
}

//显示欢迎界面
void Welcome::ShowWelcomeScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowWelcomeWnd || c_pWelcomeWnd != NULL)
		return;

	// 创建一个Welcome的对象，然后创建窗口
	c_pWelcomeWnd = new Welcome;
	if (!c_pWelcomeWnd->Create(pParentWnd))
		delete c_pWelcomeWnd;
	else
		c_pWelcomeWnd->UpdateWindow();
}

//创建窗口
BOOL Welcome::Create(CWnd* pParentWnd)
{
	if (!m_bitmap.LoadBitmap(IDB_Welcome)) //加载欢迎位图
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

//销毁窗口
void Welcome::HideWelcomeScreen()
{
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();   //更新主窗口
}

//释放
void Welcome::PostNcDestroy()
{
	delete this;
}

int Welcome::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow();  //窗口在屏幕的中央
	SetTimer(1, 2000, NULL);  //设置定时器，到时间后销毁欢迎窗口
	return 0;
}

void Welcome::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	//画图
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

//定时器，再时间到后销毁窗口
void Welcome::OnTimer(UINT nIDEvent)
{
	HideWelcomeScreen();
}

