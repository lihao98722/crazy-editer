#pragma once


// Welcome

/*
Welcome 这个类是用来实现在程序开始时显示欢迎界面。

在声明变量和方法时充分考虑了作用域，从而将一些实现细节隐藏起来（protected）
*/

class Welcome : public CWnd
{
	DECLARE_DYNAMIC(Welcome)

public:
	Welcome();
	virtual ~Welcome();
	//必须设为public作为接口
	virtual void PostNcDestroy(); 
	static void EnableWelcomeScreen(BOOL bEnable = TRUE);
	static void ShowWelcomeScreen(CWnd* pParentWnd = NULL);

protected:
	//因为都是在类的成员函数里调用的，所以把这些实现细节设置为protected
	CBitmap m_bitmap; //位图变量
	static BOOL c_bShowWelcomeWnd;  //设置为static,因为其实也就一个Welcome类的对象
	static Welcome* c_pWelcomeWnd;  //指向对象的指针
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideWelcomeScreen();
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};


