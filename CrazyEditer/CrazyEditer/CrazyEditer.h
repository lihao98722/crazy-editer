
// CrazyEditer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCrazyEditerApp:
// �йش����ʵ�֣������ CrazyEditer.cpp
//

class CCrazyEditerApp : public CWinApp
{
public:
	CCrazyEditerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCrazyEditerApp theApp;