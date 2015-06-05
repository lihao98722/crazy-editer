
// CrazyEditerDlg.h : ͷ�ļ�
//

#pragma once
#include"MyRichEditCtrl.h"

// CCrazyEditerDlg �Ի���
class CCrazyEditerDlg : public CDialogEx
{
// ����
public:
	CCrazyEditerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	friend class CMyRichEditCtrl;//��Ϊ��Ԫ��,Ϊ��ʵ�ּ������еĹ���,��������û��ʵ��
	void ShowCursorPosition(long x, long y);//��ʾ����(û�ɹ�ʵ��)
	
	HACCEL m_hAccel;		//���ټ�
	CMenu m_Menu;			//�˵���
	CStatusBar m_StatusBar; //״̬��
	CToolBar m_ToolBar;		//������
	CReBar m_ReBar;			//ͨ��ReBar�����ù����������ȽϷ���

	CMyRichEditCtrl *m_RichEdit;   //editcontrol�ؼ�����,������̬�����༭��Ͳ����༭��
	CString strEdit;		//�����ı�����
	BOOL isNew;				//��¼���ı��Ƿ����½���
	CString SavePath;		//��¼�ļ���ȡ·��
	BOOL isModified;		//�жϱ༭�����ı��Ƿ��޸�

	BOOL isChecked;			//�ж��Զ������Ƿ�ѡ��
	BOOL code_IsChecked;    //�жϸ��ļ��Ƿ��ѱ�����

	//����/�滻ʱʹ�õı���
	CFindReplaceDialog* dlg;//����"����/�滻"�Ի���ָ��
	int nindex;				//�����ַ�������ʼλ��
	int index;				//�ҵ����ַ�����λ��
	BOOL firstReplace;		//�ж��Ƿ�Ϊ��һ���滻
	BOOL find;				//�ж��Ƿ���в���

	//������ɫ����������(����Ϊȫ�ֱ���ʱΪ�����л��Զ�����ʱ,�ؽ�����ʱ�ܱ����������Ժͱ�����ɫ����)
	COLORREF m_BackgroundColor;  //������ɫ
	CHARFORMAT cf;				//��������

// �Ի�������
	enum { IDD = IDD_CRAZYEDITER_DIALOG };

	protected:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//Ϊ���жϼ�����Ϣ(��ʾ��д������״̬)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuSaveas();
	afx_msg void OnMenuFindReplace();
    afx_msg long OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuFont();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuAbout();
	afx_msg void OnClose();
	afx_msg void OnMenuCopy();
    afx_msg void OnMenuPaste();
	afx_msg void OnMenuCut();
	afx_msg void OnMenuDelete();
	afx_msg void OnMenuUndo();
	afx_msg void OnMenuSelectAll();
	afx_msg void OnMenuCountString();
	afx_msg void OnMenuCountAll();
	afx_msg void OnMenuHelp();
	afx_msg void OnInsertTime();
	afx_msg void OnFontColor();
	afx_msg void OnBackgroundColor(); 
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct); 
	afx_msg void OnPrint();
	afx_msg void OnAutoReturn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void Register();
	afx_msg void Code();
	DECLARE_MESSAGE_MAP()

public:
	
	 
	 
};
