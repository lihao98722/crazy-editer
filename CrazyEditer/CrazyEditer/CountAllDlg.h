#pragma once
#include "afxwin.h"


// CCountAllDlg �Ի���

class CCountAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCountAllDlg)

public:
	CCountAllDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCountAllDlg();
	
// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	//������ʾ���ֵı༭���value�Ϳؼ�����,��Ϊ����ʾ�ַ�����������ΪUINT��
	/*
	��value�Ϳؼ���������ֱ����EditControl����ʾ����ֵ���������control�͵Ŀؼ�����
	����Ҫsetwindowtext����
	*/
	UINT m_AllChar;			//�����ַ���
	UINT m_ChineseChar;		//�����ַ���
	UINT m_EnglishChar;		//Ӣ����ĸ��
	UINT m_DigitChar;		//�����ַ���
	UINT m_SpaceChar;		//�ո���
	UINT m_NotationChar;	//��Ƿ���������û�а�ȫ�Ƿ����������棩

	//��ʾͳ�ƽ��
	void DisplayResult(UINT all,UINT Chinese,UINT English,UINT number,UINT blank, UINT notation);  
	
};
