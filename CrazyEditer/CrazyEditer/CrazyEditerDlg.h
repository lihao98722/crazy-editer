
// CrazyEditerDlg.h : 头文件
//

#pragma once
#include"MyRichEditCtrl.h"

// CCrazyEditerDlg 对话框
class CCrazyEditerDlg : public CDialogEx
{
// 构造
public:
	CCrazyEditerDlg(CWnd* pParent = NULL);	// 标准构造函数

	friend class CMyRichEditCtrl;//设为友元类,为了实现计算行列的功能,但是最终没有实现
	void ShowCursorPosition(long x, long y);//显示行列(没成功实现)
	
	HACCEL m_hAccel;		//加速键
	CMenu m_Menu;			//菜单栏
	CStatusBar m_StatusBar; //状态栏
	CToolBar m_ToolBar;		//工具栏
	CReBar m_ReBar;			//通过ReBar来设置工具栏背景比较方便

	CMyRichEditCtrl *m_RichEdit;   //editcontrol控件变量,用来动态创建编辑框和操作编辑框
	CString strEdit;		//保存文本内容
	BOOL isNew;				//记录该文本是否是新建的
	CString SavePath;		//记录文件存取路径
	BOOL isModified;		//判断编辑框内文本是否被修改

	BOOL isChecked;			//判断自动换行是否选中
	BOOL code_IsChecked;    //判断该文件是否已被加密

	//查找/替换时使用的变量
	CFindReplaceDialog* dlg;//声明"查找/替换"对话框指针
	int nindex;				//查找字符串的起始位置
	int index;				//找到的字符串的位置
	BOOL firstReplace;		//判断是否为第一次替换
	BOOL find;				//判断是否进行查找

	//背景颜色和字体属性(设置为全局变量时为了在切换自动换行时,重建窗口时能保持字体属性和背景颜色不变)
	COLORREF m_BackgroundColor;  //背景颜色
	CHARFORMAT cf;				//字体属性

// 对话框数据
	enum { IDD = IDD_CRAZYEDITER_DIALOG };

	protected:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//为了判断键盘信息(显示大写锁定的状态)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
