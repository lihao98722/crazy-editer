// Welcome.cpp : ʵ���ļ�
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
	// deleteָ���������ΪNULL
	ASSERT(c_pWelcomeWnd == this);
	c_pWelcomeWnd = NULL;
}


BEGIN_MESSAGE_MAP(Welcome, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER() //��ʱ��
END_MESSAGE_MAP()



// Welcome ��Ϣ�������

BOOL Welcome::c_bShowWelcomeWnd;
Welcome* Welcome::c_pWelcomeWnd;

//����ӭ���棬�ڳ�ʼ�����򣬼�InitInstance()ʱ��Ҫ���õ�
void Welcome::EnableWelcomeScreen(BOOL bEnable)
{
	c_bShowWelcomeWnd = bEnable;
}

//��ʾ��ӭ����
void Welcome::ShowWelcomeScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowWelcomeWnd || c_pWelcomeWnd != NULL)
		return;

	// ����һ��Welcome�Ķ���Ȼ�󴴽�����
	c_pWelcomeWnd = new Welcome;
	if (!c_pWelcomeWnd->Create(pParentWnd))
		delete c_pWelcomeWnd;
	else
		c_pWelcomeWnd->UpdateWindow();
}

//��������
BOOL Welcome::Create(CWnd* pParentWnd)
{
	if (!m_bitmap.LoadBitmap(IDB_Welcome)) //���ػ�ӭλͼ
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

//���ٴ���
void Welcome::HideWelcomeScreen()
{
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();   //����������
}

//�ͷ�
void Welcome::PostNcDestroy()
{
	delete this;
}

int Welcome::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow();  //��������Ļ������
	SetTimer(1, 2000, NULL);  //���ö�ʱ������ʱ������ٻ�ӭ����
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

	//��ͼ
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

//��ʱ������ʱ�䵽�����ٴ���
void Welcome::OnTimer(UINT nIDEvent)
{
	HideWelcomeScreen();
}

