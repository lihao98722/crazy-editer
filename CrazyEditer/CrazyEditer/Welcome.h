#pragma once


// Welcome

/*
Welcome �����������ʵ���ڳ���ʼʱ��ʾ��ӭ���档

�����������ͷ���ʱ��ֿ����������򣬴Ӷ���һЩʵ��ϸ������������protected��
*/

class Welcome : public CWnd
{
	DECLARE_DYNAMIC(Welcome)

public:
	Welcome();
	virtual ~Welcome();
	//������Ϊpublic��Ϊ�ӿ�
	virtual void PostNcDestroy(); 
	static void EnableWelcomeScreen(BOOL bEnable = TRUE);
	static void ShowWelcomeScreen(CWnd* pParentWnd = NULL);

protected:
	//��Ϊ��������ĳ�Ա��������õģ����԰���Щʵ��ϸ������Ϊprotected
	CBitmap m_bitmap; //λͼ����
	static BOOL c_bShowWelcomeWnd;  //����Ϊstatic,��Ϊ��ʵҲ��һ��Welcome��Ķ���
	static Welcome* c_pWelcomeWnd;  //ָ������ָ��
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideWelcomeScreen();
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};


