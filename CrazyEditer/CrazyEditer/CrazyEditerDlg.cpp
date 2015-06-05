
// CrazyEditerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CrazyEditerDlg.h"
#include "afxdialogex.h"
#include "Welcome.h"
#include "CountAllDlg.h"
#include "CountString.h"
#include "HelpDlg.h"
#include "CodeDlg.h"
#include "DecodeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT BASED_CODE indicators[]={ ID_INDICATOR_NISH,ID_INDICATOR_CAPTICAL ,ID_INDICATOR_TIME};  //状态栏信息
static UINT WM_FINDMESSAGE = RegisterWindowMessage(FINDMSGSTRING);   //定义“查找/替换”消息

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCrazyEditerDlg 对话框


CCrazyEditerDlg::CCrazyEditerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrazyEditerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_hAccel=::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR1));//根据所创建的加速键表加载加速键

	//设置初始化时的背景颜色
	/*
	虽然在编辑框中本来就是白色背景，但是这里也必须要初始化m_BackgroundColor
	为白色。因为在切换自动换行时要销毁窗口再重建，而重建的窗口必须和之前窗口
	的背景颜色一样，所以需要在重建完后调用SetBackgroundColor（）来设置背景颜色，
	只有m_BackgroundColor默认为白色，再本来就是白色背景的条件下（也就是背景颜色
	还未被改变的条件下），重建窗口时SetBackgroundColor（false,m_BackgroundColor）
	才能保持白色背景，所以必须初始化。
	*/
	m_BackgroundColor = RGB(255,255,255);   //默认白色背景

	/*
	设置默认的字体属性，同需要设置默认背景颜色一样，每次切换自动换行重建窗口时需要
	保持和上一个窗口一样的字体属性，如果没有默认的字体属性的话，第一次切换自动换行时
	m_RichEdit->SetDefaultCharFormat(cf);会导致字体属性并不是原来的，经测验，字体将会
	变得特别大，所以必须设置默认字体属性。
	*/
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_SIZE;
	cf.yHeight = 300;
	
	strEdit = "";  //初始化文本内容为空
	isChecked = true;  //默认自动换行选中
	code_IsChecked = false; //默认该文件未被加密

}

void CCrazyEditerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCrazyEditerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(WM_FINDMESSAGE, OnFindReplace)
	ON_COMMAND(ID_MENU_FIND_REPLACE, OnMenuFindReplace)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_SAVEAS, OnMenuSaveas)
	ON_COMMAND(ID_MENU_PRINT, OnPrint)
	ON_COMMAND(ID_MENU_AUTORETURN, OnAutoReturn)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_COMMAND(ID_MENU_COPY, OnMenuCopy)
	ON_COMMAND(ID_MENU_PASTE, OnMenuPaste)
	ON_COMMAND(ID_MENU_CUT, OnMenuCut)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	ON_COMMAND(ID_MENU_COUNT_STRING, OnMenuCountString)
	ON_COMMAND(ID_MENU_COUNT_ALL, OnMenuCountAll)
	ON_COMMAND(ID_MENU_HELP, OnMenuHelp)
	ON_COMMAND(ID_MENU_EXIT, OnClose)      
	ON_COMMAND(ID_MENU_INSERTTIME, OnInsertTime)
	ON_COMMAND(ID_MENU_FONT, OnMenuFont)
	ON_COMMAND(ID_MENU_BACKGROUNDCOLOR, OnBackgroundColor)
	ON_COMMAND(ID_MENU_WRITETOREGISTER, Register)
	ON_COMMAND(ID_MENU_CODE, Code)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCrazyEditerDlg 消息处理程序

BOOL CCrazyEditerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	
	//动态创建编辑框,默认可以自动换行
	m_RichEdit = new CMyRichEditCtrl();
	m_RichEdit->Create(WS_VISIBLE|WS_CHILD|ES_MULTILINE
		|ES_WANTRETURN|ES_AUTOVSCROLL|WS_VSCROLL|WS_BORDER,CRect(5,65,665,735),this,IDC_EDIT1);//要调整窗口大小到合适为止
	m_RichEdit->SetDefaultCharFormat(cf);  //设置默认字体属性
	m_RichEdit->SetBackgroundColor(false,m_BackgroundColor); //设置默认背景颜色（白色）
	//设置对话框大小
	ModifyStyle(WS_THICKFRAME, 0); //让对话框在运行的过程中不可以调整大小
	

	//“菜单”的实现
	m_Menu.CreateMenu();   //创建菜单窗口
   
	//“文件”菜单
	CMenu m_PopMenu1;                     //定义菜单对象
	m_PopMenu1.CreatePopupMenu();         //创建菜单的弹出窗口
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu1.m_hMenu,"文件(&F)");     //插入菜单和其在菜单状态下的快捷键
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_NEW,"新建(&N)   Ctrl+N");    //插入子菜单
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_OPEN,"打开(&O)   Ctrl+O");  
	m_PopMenu1.AppendMenu(MF_SEPARATOR);                                 //插入分割线
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVE,"保存(&S)    Ctrl+S");   
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVEAS,"另存为     Ctrl+ALT+S");        
	m_PopMenu1.AppendMenu(MF_SEPARATOR);
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_PRINT,"打印(&P)    Ctrl+P");   
	m_PopMenu1.AppendMenu(MF_SEPARATOR);
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_EXIT,"退出(&Q)   Ctrl+Q");  
	
	//“编辑”菜单
	CMenu m_PopMenu2;
	m_PopMenu2.CreatePopupMenu();                                  
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu2.m_hMenu,"编辑(&E)");     
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_UNDO,"撤销(&U)   Ctrl+Z");          
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_DELETE,"删除(&D)");
	m_PopMenu2.AppendMenu(MF_SEPARATOR);
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_SELECT_ALL,"全选(&A)   Ctrl+A");
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_CUT,"剪贴(&T)   Ctrl+X");		  
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_COPY,"复制(&C)   Ctrl+C");         
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_PASTE,"粘贴(&V)   Ctrl+V");
	m_PopMenu2.AppendMenu(MF_SEPARATOR); 
    m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_INSERTTIME,"插入当前日期/时间"); 
	

	//“格式”菜单
	CMenu m_PopMenu3;
	m_PopMenu3.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu3.m_hMenu,"格式");
	m_PopMenu3.AppendMenu(MF_BYPOSITION|MF_CHECKED,ID_MENU_AUTORETURN,"自动换行"); //默认自动换行选中
	m_PopMenu3.AppendMenu(MF_SEPARATOR);
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FONT,"字体设置(&S)   Alt+F");
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_BACKGROUNDCOLOR,"背景颜色");
	m_PopMenu3.AppendMenu(MF_SEPARATOR);
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FIND_REPLACE,"查找/替换(&F)   Ctrl+F");
	
	//“统计”菜单
	CMenu m_PopMenu4;
	m_PopMenu4.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu4.m_hMenu,"统计");
	m_PopMenu4.AppendMenu(MF_STRING,ID_MENU_COUNT_ALL,"统计字数(&C)");
	m_PopMenu4.AppendMenu(MF_STRING,ID_MENU_COUNT_STRING,"统计字符串");

	//“安全”菜单
	CMenu m_PopMenu5;
	m_PopMenu5.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu5.m_hMenu,"安全");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_WRITETOREGISTER,"写入注册表");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_CODE,"加密/解密");

	//“帮助”菜单
	CMenu m_PopMenu6;
	m_PopMenu6.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu6.m_hMenu,"帮助(&H)");
	m_PopMenu6.AppendMenu(MF_STRING,ID_MENU_ABOUT,"关于CrazyEditer(&A)");
	m_PopMenu6.AppendMenu(MF_STRING,ID_MENU_HELP,"查看帮助(&H)   Ctrl+H");

	

	//分离菜单的句柄
	m_PopMenu1.Detach();
	m_PopMenu2.Detach();
	m_PopMenu3.Detach();
	m_PopMenu4.Detach();
	m_PopMenu5.Detach();
	m_PopMenu6.Detach();

	SetMenu(&m_Menu); //将菜单和窗口进行关联


	//工具栏的实现
	if (!m_ToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC))
	{
		return FALSE;
	}
	CImageList ImageList;			//声明图像列表对象
	ImageList.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);			//创建图像列表
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONNEW));			//设置图标
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONOPEN));										
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONSAVE));										
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONPRINT));										
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONFONT));					
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONBACKGROUND));										
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONFIND));									
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONCOUNT));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONCODE));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONHELP));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICONEXIT));	
 
	m_ToolBar.GetToolBarCtrl().SetImageList(&ImageList);		//关联图像列表
	ImageList.Detach();					//释放图像列表
	m_ToolBar.SetButtons(NULL,11);		//设置工具栏按钮

	m_ToolBar.SetButtonInfo(0,ID_MENU_NEW,TBSTYLE_BUTTON,0);		//设置工具栏信息
	m_ToolBar.SetButtonText(0,"新建文件");							//设置工具栏文本
	m_ToolBar.SetButtonInfo(1,ID_MENU_OPEN,TBSTYLE_BUTTON,1);
	m_ToolBar.SetButtonText(1,"打开文件");
	m_ToolBar.SetButtonInfo(2,ID_MENU_SAVE,TBSTYLE_BUTTON,2);
	m_ToolBar.SetButtonText(2,"保存文件");
	m_ToolBar.SetButtonInfo(3,ID_MENU_PRINT,TBSTYLE_BUTTON,3);
	m_ToolBar.SetButtonText(3,"打印文本");
	m_ToolBar.SetButtonInfo(4,ID_MENU_FONT,TBSTYLE_BUTTON,4);
	m_ToolBar.SetButtonText(4,"字体设置");
	m_ToolBar.SetButtonInfo(5,ID_MENU_BACKGROUNDCOLOR,TBSTYLE_BUTTON,5);
	m_ToolBar.SetButtonText(5,"背景颜色");
	m_ToolBar.SetButtonInfo(6,ID_MENU_FIND_REPLACE,TBSTYLE_BUTTON,6);
	m_ToolBar.SetButtonText(6,"查找替换");
	m_ToolBar.SetButtonInfo(7,ID_MENU_COUNT_ALL,TBSTYLE_BUTTON,7);
	m_ToolBar.SetButtonText(7,"统计字数");
	m_ToolBar.SetButtonInfo(8,ID_MENU_CODE,TBSTYLE_CHECK,8);
	m_ToolBar.SetButtonText(8,"加密/解密");
	m_ToolBar.SetButtonInfo(9,ID_MENU_HELP,TBSTYLE_BUTTON,9);
	m_ToolBar.SetButtonText(9,"帮助提示"); 
	m_ToolBar.SetButtonInfo(10,ID_MENU_EXIT,TBSTYLE_BUTTON,10);
	m_ToolBar.SetButtonText(10,"退出程序"); 

	m_ToolBar.SetSizes(CSize(60,60),CSize(32,32));				//设置按钮大小

	m_ReBar.Create(this);	
	//设置目标工具栏,同时设置背景为白色(因为按钮也是白色背景)，这样做可以美化
	m_ReBar.AddBar(&m_ToolBar,NULL,RGB(255,255,255));
    m_ReBar.RedrawWindow();			//重绘窗口
	REBARBANDINFO info;																		
	info.cbSize = sizeof(info);					//设置结构大小
	info.fMask = RBBIM_BACKGROUND;										//设置标记
	m_ToolBar.ModifyStyle(0,TBSTYLE_TRANSPARENT);						//设置工具栏风格
	m_ReBar.GetReBarCtrl().SetBandInfo(0,&info);						//访问工具栏
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);	//显示工具栏


	//“状态栏”的实现
	m_StatusBar.Create(this);//创建状态栏  
	m_StatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)); //设置状态栏数目  
	CRect rect;  
	GetClientRect(&rect);  
	//设置各栏长度  
	m_StatusBar.SetPaneInfo(0, ID_INDICATOR_NISH, SBPS_NORMAL, 300);
	m_StatusBar.SetPaneInfo(1, ID_INDICATOR_CAPTICAL, SBPS_NORMAL, 200);
	m_StatusBar.SetPaneInfo(2, ID_INDICATOR_TIME, SBPS_STRETCH, 0);	

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_TIME);//在屏幕上绘制状态栏

	m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(180,180,180));  //设置状态栏背景为灰色

	/*设置初始时大写锁定的状态*/
	
		int check = GetKeyState(VK_CAPITAL);//获取键盘大写锁定键的状态
		if(check == 0){  //判断初始时状态，输出对应的状态消息
			m_StatusBar.SetPaneText(1,"大写锁定： 关");
		}else if(check >0){
			m_StatusBar.SetPaneText(1,"大写锁定： 开");
		};

	SetTimer(100,1000,NULL);  //设置定时器（为了在状态栏显示时间）

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCrazyEditerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCrazyEditerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCrazyEditerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//加载启动画面
int CCrazyEditerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	Welcome::ShowWelcomeScreen(this);							//显示启动画面
	Sleep(2000);				 								//设置启动画面显示时间
    /* 要调整到差不多的时候，不然会出现程序已经启动了但是启动画面还在的情况*/
	
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DragAcceptFiles(TRUE);

	return 0;
}

//新建文件的处理函数
void CCrazyEditerDlg::OnMenuNew()
{
	//新建前对现有的文本进行处理
	isModified = m_RichEdit->GetModify();	//获取修改标记
	m_RichEdit->GetWindowText(strEdit);		//把编辑框的内容读入strEdit中
	if (isNew && strEdit.IsEmpty()){		//若是新建文本而起文本为空,则不做任何操作
		;
	}else if(isModified){			//如果文本已经被修改，则询问用户是否需要保存
	    int Choice = MessageBox("当前文本已被修改，是否需要保存？","系统提示",
			MB_YESNO|MB_ICONQUESTION);		//获取用户的选择
	    if(Choice==IDYES){			
			OnMenuSave();	//如果选择为“是”，则调用保存函数进行保存
		}
	}
    
	//新建文本
	m_RichEdit->SetSel(0, -1);		//选中编辑框内的全部文本内容
	m_RichEdit->Clear();				//删除编辑框内的文本内容
	strEdit.Empty();             //清空文本内容（如果没有清空的话，两个不同文件的文本内容会合在一起）
	isNew = TRUE;				//说明此文本为新建文本
	m_RichEdit->SetModify(FALSE);		//说明此文本未被修改
}

//打开文件的处理函数
void CCrazyEditerDlg::OnMenuOpen()
{
	//打开前对现有的文本进行处理
	isModified = m_RichEdit->GetModify();	//获取修改标记
	m_RichEdit->GetWindowText(strEdit);		//把编辑框的内容读入strEdit中
	if (isNew && strEdit.IsEmpty()){		//若此文本是新建文本而起文本为空,则不做任何操作
		;
	}else if(isModified){			//如果文本已经被修改，则询问用户是否需要保存
	    int Choice = MessageBox("当前文本已被修改，是否需要保存？","系统提示",
			MB_YESNO|MB_ICONQUESTION);		//获取用户的选择
	    if(Choice==IDYES){			
			OnMenuSave();	//如果选择为“是”，则调用保存函数进行保存
		}
	}

	//打开文件
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||",AfxGetMainWnd());		//构造“文件打开”的对话框

	CString strPath="";
	if(dlg.DoModal() == IDOK){			//如果用户选择打开
		strPath = SavePath = dlg.GetPathName();		//获取文件的路径
		CFile file(strPath,CFile::modeReadWrite);		//“读写”方式打开文件
		/*
		一定要等用户选择打开的时候才能把strEdit清空，否则如果用户不选择打开就把
		strEdit清空，本来的文本内容就被清空了（虽然在编辑框内没被清空）
		*/
		strEdit.Empty();   //将strEdit清空（）
		char read[50000];
		file.Read(read,50000);		//读取文件内容
		for(unsigned i=0;i<file.GetLength();i++){
			strEdit += read[i];			//把文件内容赋给strEdit
		}		
		file.Close();		//关闭文件
		m_RichEdit->SetWindowText(strEdit);	//显示文件内容，即strText的内容
		m_RichEdit->SetModify(FALSE);	//因为是新读的内容，所以要说明此文本未被修改
		isNew = FALSE;		//说明此文本不是新文本
	}
}

//保存文本的处理函数
void CCrazyEditerDlg::OnMenuSave()
{
    if (isNew){		//如果是新建且未保存的文本，必须调用“另存为”来进行保存，因为本来没有这个文件
		OnMenuSaveas();		//另存新建的文本
	}
	else{
		char write[50000];		
		CFile file(_T(SavePath),CFile::modeCreate|CFile::modeReadWrite);//以“读写”方式创建文件
		/*
		这时候一定要把编辑器的内容赋给strEdit，否则修改完后内容根本没办法保存下来。
		弄得差点吐血，后来通过断点调试，然后追踪变量的值才查到原因.
		*/
		m_RichEdit->GetWindowText(strEdit);  //把编辑器里面的内容赋给strEdit

		//m_RichEdit->SetWindowText(strEdit); 
		/*
		本来这个函数写错了，太粗心了，写成了SetWindowText（），后来又是靠断点调试解决的。
		*/
		strcpy_s(write,strEdit);         //将文本内容（即编辑框的内容）赋给字符串数组
		file.Write(write,strEdit.GetLength());    //将内容写入文件
		file.Close();				//关闭文件
		m_RichEdit->SetModify(FALSE);	//说明此文件未被修改（因为已经保存了）
		/*
		保存文件并不需要把文本内容(strEdit)清空，因为有可能要继续使用；
		只有等到要新建文件或者打开文件的时候才需要把原来的文本内容（strEdit）清空
		*/
	}
	m_RichEdit->SetSel(0,0);
}

//“另存为”的处理函数
void CCrazyEditerDlg::OnMenuSaveas()
{
	CFileStatus fs;				//文件存在的状态

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.txt)|*.txt||",AfxGetMainWnd());    //构造“另存为”对话框
	CString strPath="";
	/*
	这时候一定要把编辑器的内容赋给strEdit，否则修改完后内容根本没办法保存下来。
	弄得差点吐血，后来通过断点调试，然后追踪变量的值才查到原因.
	*/
	m_RichEdit->GetWindowText(strEdit);  //把编辑器里面的内容赋给strEdit

	//m_RichEdit->SetWindowText(strEdit); 
	/*
	本来这个函数写错了，太粗心了，写成了SetWindowText（），后来又是靠断点调试解决的。
	*/
	char write[50000];
	if(dlg.DoModal() == IDOK){                          //若“确定”要另存为
		strPath = dlg.GetPathName();                    //获取文件要另存为的路径
		if(strPath.Right(4) != ".txt"){
			strPath += ".txt";                          //拓展名为 “txt”
		}

		if(CFile::GetStatus(_T(strPath),fs)){			//如果本来文件就存在  
			CString info = strPath;
			info += "文件已存在，是否要替换它？";
			int nChoice = MessageBox (info,"另存为",MB_ICONWARNING|MB_YESNO);	//弹出确认替换的消息
			if (nChoice == IDYES){			//如果用户要替换
				
				SavePath = strPath;		//获取保存新建文本的路径
		
				CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite); //创建文件（是以“写”的方式）
				strcpy_s(write,strEdit);		//将文本内容赋给数组					
				file.Write(write,strEdit.GetLength());		//将文本写入文件
				file.Close();			//关闭文件
				isNew = FALSE;			//说明此文件已不是新文件
				m_RichEdit->SetModify(FALSE);   //说明此文件未被修改
			}else{			//如果不需要替换的话
				OnMenuSaveas();			//弹出另存为对话框
			 }
		}else{				//如果文件不存在
			SavePath = strPath;				//获取新建文本的路径

			CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);		//创建文件（是以“写”的方式）
			strcpy_s(write,strEdit);		//将文本内容赋给字符串数组
			file.Write(write,strEdit.GetLength());		//把文本写入文件
			file.Close();			//关闭文件
			isNew = FALSE;			//说明此文件已不是新文件
			m_RichEdit->SetModify(FALSE);   //说明此文件未被修改
			/*
			另存为的时候和保存一样，并不需要把文本内容（strEdit）清空
			*/
		 }									
	}
	m_RichEdit->SetSel(0,0);
}

//撤销
void CCrazyEditerDlg::OnMenuUndo(){
	m_RichEdit->Undo();
}

//全选
void CCrazyEditerDlg::OnMenuSelectAll(){
	m_RichEdit->SetSel(0,-1);
}

//复制
void CCrazyEditerDlg::OnMenuCopy(){
	m_RichEdit->Copy();
}

//粘贴
void CCrazyEditerDlg::OnMenuPaste(){
	m_RichEdit->Paste();
}

//剪切
void CCrazyEditerDlg::OnMenuCut(){
	m_RichEdit->Cut();
}

//删除
void CCrazyEditerDlg::OnMenuDelete(){
	m_RichEdit->Clear();
}

//自动换行
void CCrazyEditerDlg::OnAutoReturn(){

	/*
	因为切换自动换行时销毁重建,虽然原来的文本被记录下又显示出来,但是并不知道
	之前的文本被修改了没有,所以需要进行判断,否则新建的编辑框的modified状态为
	false,也就是说会造成在切换自动换行后,直接退出程序时并不会提示用户进行保存
	已修改了的文本.
	*/
	CString curStrEdit;
	m_RichEdit->GetWindowText(curStrEdit);
	bool modified = (curStrEdit==strEdit)?false:true;  //判断是否被修改

	m_RichEdit->GetWindowText(strEdit);		//获取编辑框中的文本内容，以便显示在新建的编辑框中

	if(isChecked){  //更改菜单项的选中状态，切换“自动换行/不自动换行”

		GetMenu()->GetSubMenu(2)->CheckMenuItem(ID_MENU_AUTORETURN,MF_UNCHECKED);	 //设置为未选中
		
		m_RichEdit->DestroyWindow();	//销毁编辑框
		m_RichEdit->Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|WS_HSCROLL|ES_WANTRETURN
			|WS_VSCROLL|WS_BORDER|ES_MULTILINE,CRect(5,65,665,735),this,0); //创建不自动换行的编辑框（因为默认是自动换行）
	
		isChecked = false;  //说明“自动换行”为未选中状态

	}else{
		GetMenu()->GetSubMenu(2)->CheckMenuItem(ID_MENU_AUTORETURN,MF_CHECKED);    //设置为选中

		m_RichEdit->DestroyWindow();	//销毁编辑框
		m_RichEdit->Create(WS_VISIBLE|WS_CHILD|ES_MULTILINE
			|ES_WANTRETURN|ES_AUTOVSCROLL|WS_VSCROLL|WS_BORDER,CRect(5,65,665,735),this,0);	//创建自动换行的编辑框

		isChecked = true;		//说明“自动换行”为选中状态
	}
	
	m_RichEdit->SetWindowText(strEdit);//将原本编辑框内的内容显示出来
	/*
	设置修改标记一定要放在m_RichEdit->SetWindowText(strEdit);之后，
	否则在退出程序那里判断modified状态时照样是显示未修改,所以并不会提示
	用户进行保存。（之前把这句语句放在m_RichEdit->SetWindowText(strEdit);之前
	造成了这个bug,后来仔细查阅RchEdit的getModify()函数的原理之后终于巧妙解决了这个
	BUG）
	*/
	m_RichEdit->SetModify(modified);		//设置修改标记
	m_RichEdit->SetDefaultCharFormat(cf);   //恢复字体属性
	m_RichEdit->SetBackgroundColor(false,m_BackgroundColor); //恢复背景颜色
	m_RichEdit->SetFocus();   //编辑框获取焦点
	m_RichEdit->SetSel(-1,-1);   //设置焦点在文本后
}

//打印功能
/*
由于没有打印机，所以没办法测试打印的功能是不是能实现，但是应该没什么问题
*/
void CCrazyEditerDlg::OnPrint(){
	CPrintDialog print(false);
	if(print.DoModal() == IDOK){
		CDC printcd;
		printcd.Attach(print.GetPrinterDC());
		DOCINFO pdoc;
		pdoc.cbSize=sizeof(pdoc);
		pdoc.lpszDocName="pdoc";
		pdoc.lpszDatatype=NULL;
		pdoc.fwType=NULL;
		pdoc.lpszOutput=NULL;
		if(printcd.StartDoc(&pdoc) >= 0){
			LOGFONT logfont;
			memset(&logfont,0,sizeof(LOGFONT));
			logfont.lfHeight=75;
			CFont font;
			CFont *oldfont=NULL;
			if(font.CreateFontIndirect(&logfont));
			oldfont=(CFont *)printcd.SelectObject(&font);
			for(int i=1;i<3;i++){
				CString str;
				str.Format(_T("第%d页 test print file %d"),i,i);
				printcd.StartPage();
				printcd.TextOut(0,100,str);
				printcd.EndPage();
			}
			font.DeleteObject();
			if(oldfont != NULL){
				printcd.SelectObject(oldfont);
			}
			printcd.EndDoc();
		}
		printcd.DeleteDC();
	}
}


//字体的处理函数
void CCrazyEditerDlg::OnMenuFont(){

	LOGFONT lf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	memset(&lf, 0, sizeof(LOGFONT));

	/*
	得到当前字体的属性;
	如果没有这个函数的话，设置完字体的属性之后，再去点开字体的设置对话框
	时，对话框的字体的选中状态并不是当前字体的属性，而是Default的属性。
	*/
	m_RichEdit->GetSelectionCharFormat(cf);

	//得到相关字体属性
	BOOL bIsBold = cf.dwEffects & CFE_BOLD;
	BOOL bIsItalic = cf.dwEffects & CFE_ITALIC;
	BOOL bIsUnderline = cf.dwEffects & CFE_UNDERLINE;
	BOOL bIsStrickout = cf.dwEffects & CFE_STRIKEOUT;
	//设置属性
	lf.lfCharSet = cf.bCharSet;
	lf.lfHeight = cf.yHeight/15;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	lf.lfItalic = bIsItalic;
	lf.lfWeight = bIsBold ? FW_BOLD : FW_NORMAL;
	lf.lfUnderline = bIsUnderline;
	lf.lfStrikeOut = bIsStrickout;
	sprintf_s(lf.lfFaceName, cf.szFaceName);

	CFontDialog dlg(&lf); //显示字体设置对话框
	dlg.m_cf.rgbColors = cf.crTextColor;  //设置字体颜色
	if (dlg.DoModal() == IDOK){
		dlg.GetCharFormat(cf); //获得所选的字体属性，如字体、颜色、大小等
		m_RichEdit->SetDefaultCharFormat(cf); //设置输入框内所有字符的字体，包括已经输入的和将要输入的字符	
	}
	m_RichEdit->SetSel(-1,-1);		//设置焦点在文字的最后面
}


//背景颜色的处理函数
void CCrazyEditerDlg::OnBackgroundColor(){
	CColorDialog dlg;   //颜色选择窗口
	if(dlg.DoModal() == IDOK){
		m_BackgroundColor=dlg.GetColor(); //获取用户选择的颜色
		m_RichEdit->SetBackgroundColor(FALSE,m_BackgroundColor);  //设置背景颜色
		m_RichEdit->SetSel(-1,-1);		//设置焦点在文字的最后面
	}
}

//插入当前时间
void CCrazyEditerDlg::OnInsertTime() 
{
    CTime time = CTime::GetCurrentTime();  //获取当前时间
	CString strtime;
	strtime = time.Format("%Y-%m-%d %H:%M:%S");  //设定格式

	m_RichEdit->GetWindowText(strEdit);	
	strEdit += strtime;			//插入时间
	m_RichEdit->SetWindowText(strEdit);					//在编辑框中显示文件内容
	m_RichEdit->SetModify(TRUE);			//文本修改标记设为已修改
	UpdateData(FALSE);   
	m_RichEdit->SetSel(-1,-1);   //设置焦点
}



//“查找/替换”的菜单响应函数，只是负责响应菜单，显示“查找/替换”对话框，
//具体实现细节在处理函数中
void CCrazyEditerDlg::OnMenuFindReplace()
{
	nindex = 0;
	firstReplace = FALSE;
	index = 0;
	dlg = new CFindReplaceDialog();			//声明“查找/替换”对话框指针
	dlg->Create(FALSE,NULL);				//创建“替换”对话框
	dlg->ShowWindow(SW_SHOW);				//显示“替换”对话框
}


//“查找/替换”的处理函数
/*
查找/替换 的处理，关键是调用了系统的查找替换窗口，然后分别获取要查找/替换的
字符串和编辑框里的内容。然后判断用户的请求，如果是查找，那么就让需要查找的字符串
和strEdit进行匹配（原理和统计功能是一样的），找到后在编辑框中标示出，然后重新设置
下一次查找的起始位置。如果需要替换全部，则通过Replace()函数就能进行全部替换，
若是要替换一个，则把需要替换的字符的左右字符串分别保存起来，然后把字符替换掉后
在把3个字符串merge成新的文本。最后重新设定文本修改标记即可。(记得替换完后需要重新获取编辑框的
内容保存到strEdit中，否则无法接着进行下一次查找/替换)
*/
long CCrazyEditerDlg::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
	CString strText,repText;						//声明字符串变量
	strText = dlg->GetFindString();					//获得查找字符串
	m_RichEdit->GetWindowText(strEdit);				//获得编辑框中是文本

	int len;		//查找的字符串的长度

	if(dlg->ReplaceAll()){	//判断是否全部替换

		strText = dlg->GetFindString();				//获得查找字符串
		repText = dlg->GetReplaceString();			//获得替换字符串
		len = repText.GetLength();					//获得替换字符串长度
		strEdit.Replace(strText,repText);			//使用替换字符串替换查找字符串
		m_RichEdit->SetWindowText(strEdit);				//将替换后的字符串显示在编辑框中
		nindex =0;									//设置查找位置为0
		m_RichEdit->SetModify(TRUE);				//说明文本已被修改
		m_RichEdit->SetSel(0,-1);
	}
	
	if(dlg->ReplaceCurrent()){				//若是选择替换当前内容
		find = FALSE;     //进行替换
	}else{
		find = TRUE;						//进行查找
	 }

	if(find){		//判断是查找还是替换
		len = strText.GetLength();				//获得要查找字符串的长度
	}else{
		CString left,right;			
		int num   = strText.GetLength();		//获得查找字符串的长度
		int strnum = strEdit.GetLength();		//获得编辑框中文本长度	
		
		if(!firstReplace){				//判断为第一次替换
			index = strEdit.Find(strText,nindex);	//获得查找字符串在编辑框文本中的位置
		}
		if(index < 0){
			nindex = 0;
			firstReplace = FALSE;
			return 1;
		}		

		left = strEdit.Left(index);						//获得替换字符串左侧的字符串
		right = strEdit.Right(strnum-index-num);		//获得替换字符串右侧的字符串
		repText = dlg->GetReplaceString();			//获得替换字符串
		len = repText.GetLength();					//获得替换字符串长度
		strEdit = left + repText + right;				//组合成新的字符串
		m_RichEdit->SetWindowText(strEdit);				//在编辑框中显示新的字符串
		m_RichEdit->SetModify(TRUE);		        //说明文本已被修改
	}
	
	strText = dlg->GetFindString();				//获得查找字符串
	m_RichEdit->GetWindowText(strEdit);			//获得编辑框中是文本

	index = strEdit.Find (strText,nindex);			//获得查找字符串在编辑框文本中的位置
	
	m_RichEdit->SetSel(index,index+strText.GetLength());	//选中查找或替换的字符串

	nindex = index+len;					//设置起始查找位置

	if (index >= 0){
		firstReplace = TRUE;
	}else{
		firstReplace = FALSE;
		nindex = 0;
	}

	m_RichEdit->SetFocus();				//编辑框获得焦点
	m_RichEdit->SetSel(-1,-1);	
	return 0;
}


//统计字符数的处理函数
/*
关键在于要先判断是半角字符还是全角字符，才能计算出中文字符的个数，从而得到真正的总的字符个数。
但是因为全角符号的ASCII码并没有明确的范围，而且不同的字符集，中文字符的编码范围又不一样，所以
也没办法通过 全角符号=总全角字符-中文字符  来进行计算，所以判断的符号数只能是半角符号数，用来
方便英文写作的时候得知所用符号的多少
*/
void CCrazyEditerDlg::OnMenuCountAll(){
	
	UINT nTotalLength = 0;					//总共字数 
	UINT nCLength = 0;						//中文   
	UINT nELength = 0;						//英文  
	UINT nDLength = 0;						//数字
	UINT nNLength = 0;						//半角符号
	UINT nBLength = 0;						//空格
	UINT nEnLength = 0;						//半角字符
	UINT nEnterLength = 0;					//回车
	int i=0;////
	m_RichEdit->GetWindowText(strEdit);    //获取编辑框的文本内容
	int Length = strEdit.GetLength();	   //文本内容的长度

	for(int i=0;i<Length;i++){		//对文本内容字符逐个进行判断

		char c = strEdit.GetAt(i);    
        
		if(c<0 || c>255){    //中文字符
			continue;
		} else{    //英文字符 
			if(c == '\r'){					//回车符
				i++;						//跳过"\n"
				nEnterLength++;				//回车符计数加1
			}else{
				nEnLength ++;
				if (c == ' ')				//空格数加1
					nBLength ++;
				else if (c>='0' && c<='9')	//数字字符加1
					nDLength ++;
				else if ((c>='a'&&c<='z')||(c>='A' && c <= 'Z'))
					nELength ++;				//英文字符数加1
			 }
		 }
	}    
	//计算中文字符数   
	/*
	因为中文字符占两个字节，所以需要用 总长度-半角字符长度=全角字符长度，然后
	全角字符长度/2 才是真正的全角字符数
	*/
	nCLength = (Length-nEnLength)/2-nEnterLength;
	nTotalLength = nCLength + nEnLength; //总长度并不是strEdit的长度，而是全角字符+半角字符
	nNLength = nEnLength - nELength	- nDLength - nBLength;		//计算半角符号数 = 半角字符数-英文字符数-数字字符数-换行字符数-空格字符数
	CCountAllDlg dlg;	   //声明统计字数对话框类对象
	dlg.DisplayResult(nTotalLength,nCLength,nELength,nDLength,nBLength,nNLength); //显示统计结果
	dlg.DoModal();		   //显示对话框  
	m_RichEdit->SetSel(-1,-1);  //设置光标位置在文本之后
}


//统计字符串的处理函数
/*
真正的实现函数是在统计字符串的类中实现的，这个函数只是负责把
编辑框内的文本，即strEdit传递给统计字符串类中用来保存主编辑框
文本的变量text，然后显示统计字符串的对话框，交给CCountString类
处理
*/
void CCrazyEditerDlg::OnMenuCountString()
{
	m_RichEdit->GetWindowText(strEdit);				//获取编辑框中的文本
	CCountString dlg;							//声明统计字符串对话框类对象
    dlg.SetText(strEdit);			//将编辑框中的文本传递给统计字符串的类的text变量
	dlg.DoModal();						//显示对话框
	m_RichEdit->SetSel(-1,-1);		//设置焦点
}

//“关于”菜单的处理函数
void CCrazyEditerDlg::OnMenuAbout()
{
	CAboutDlg dlg;       //声明系统关于对话框类对象
	dlg.DoModal();		 //显示对话框
}

//退出程序的处理程序
void CCrazyEditerDlg::OnClose()
{
	isModified = m_RichEdit->GetModify();				//获取文本修改标记
	CString string;
	m_RichEdit->GetWindowText(string);
	if (isNew && string.IsEmpty())					//若是新建文本且文本无内容内容
	{
		PostQuitMessage(0);
		//exit(0);
		//CDialog::OnClose();							//退出程序
	}
	/*
	问题是：为什么有时候CDialog：：OnClose（）可以，有时候需要exit（0）？
	后来用PostQuitMessage(0);解决了问题
	*/
	if(isModified)								//如果文本已被修改，分情况讨论
	{
	    int QuitChoice = MessageBox("当前文本已被修改，想保存吗？","系统提示",
			MB_YESNOCANCEL|MB_ICONQUESTION);		//弹出消息对话框询问
	    if(QuitChoice==IDYES)						//选择“是”
		{
			OnMenuSave();							//调用保存函数保存文件
			if (isModified = FALSE)
				//exit(0);
				PostQuitMessage(0);
				//CDialog::OnClose();					//退出程序
		}
		else if(QuitChoice==IDNO)					//选择“否”
		{
			PostQuitMessage(0);
			//exit(0);
			//CDialog::OnClose();					//退出程序
		}
		else
		{
		    return;									//选择“取消”时不退出
		}
	}
	else
	{
		PostQuitMessage(0);
	    //exit(0);
		//CDialog::OnClose();						//如果文本未被修改则直接退出程序
	}
}

//定时器（为了在状态栏显示当前时间）
void CCrazyEditerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==100)  
    {  
        CTime t1;  
        t1=CTime::GetCurrentTime();  //获取当前时间
        m_StatusBar.SetPaneText(2,t1.Format("当前时间：  %H:%M:%S"));	//设置状态栏的显示内容
    }  
	CDialogEx::OnTimer(nIDEvent);
}

/*
状态栏显示行列这个功能没能完成，问题出在没办法准确的获得字体高和宽的像素。

主要思路：本来在这个程序中是没有自定义的MyRichEditCtrl这个类的，只有在CCrazyEditerDlg
中定义了一个指向CRichEditCtrl的指针变量，然后动态创建窗口。但是由于动态创建的窗口
并没有办法有OnLButtonDown()响应函数（可以使可以动态绑定，但是太麻烦了），所以就通过
自定义的MyRichEditCtrl这个类来继承CRichEditCtrl，并且声明为对话框的友元类，然后定义
一个OnLButtonDown()响应函数，从而解决了问题。但是获取了point之后，是以像素点表示的，
必须知道字体高和宽的像素才有办法算出光标所在行列位置。（也试过GetSel（），但也没成功）
*/


void CCrazyEditerDlg::ShowCursorPosition(long x, long y)
{
	//功能没有实现
	CString s;  
	//long row = (y/cf.yHeight)+1;
	//long column;
	//m_RichEdit->GetSel(column,column);
	s.Format("行：%d   列：%d    (行列功能没有完成！)",0,0);  
    m_StatusBar.SetPaneText(0,s);

}


//显示大写锁定键的状态/加载加速键
/*
焦点在对话框的其他子窗体上，所以没办法用OnKeyDown()来处理消息，
就需要重载PreTranslateMessage()来实现响应keydown，从而显示出
大写锁定键的状态。
*/

BOOL CCrazyEditerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		
		//获取键盘大写锁定键的状态
		int check = GetKeyState(VK_CAPITAL);
		//判断是否按下键盘大写锁定键
		if(pMsg->wParam==VK_CAPITAL)
		{
			if(check == 0){
				m_StatusBar.SetPaneText(1,"大写锁定： 关");
			}else if(check >0){
				m_StatusBar.SetPaneText(1,"大写锁定： 开");
			}	
		}
	}

	//加载加速键
	if(m_hAccel!=NULL)   
	if(::TranslateAccelerator(m_hWnd,m_hAccel,pMsg)){   //翻译加速键表
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



//写注册表的处理函数
/*
虽然写入注册表然后注销电脑之后，txt文本都会默认用本程序CrazyEditer来打开，
而且在打开选择程序的时候也有CrazyEditer的选项,但是打开的时候没办法打开
文本内容，而是新建了一个空文本，个人觉得我还需要一个函数来控制打开文件
的读取，但是时间有限，就先放弃了。
*/
void CCrazyEditerDlg::Register()
{
	int nChoice = MessageBox ("即将将此程序的信息写入系统注册表。\r\n确定要写入吗？","程序注册",MB_ICONWARNING|MB_YESNO);
	if(nChoice == IDYES)
	{
		HKEY hresult;   
		CString str1,str2;   
		long value;   
    
		LPCTSTR dataset1 = "txtfile\\shell\\OPEN";	//打开方式子键
		LPCTSTR dataset2 = "txtfile\\shell\\OPEN\\command";	//启用程序路径子键   
		LPCTSTR dataset3Icon = "txtfile\\DefaultIcon";	//关联图标子键   
    
		//获得三个子键要设置的内容
		str1="用Crazyzediter打开";  
		
		char buffModulPath[MAX_PATH];   
		GetModuleFileName(GetModuleHandle(NULL),buffModulPath,MAX_PATH);   
    
		str2.Format("%s",(LPCTSTR)buffModulPath);
		str2 = "\"" + str2 + "\" ";
		CString str3 = str2;   
		str2 += "\"%1\"";
		CString CTextName = "CrazyEditer.exe,10";					//关联后显示图标  
		

		for (int nPathEnd = strlen(buffModulPath) - 1; nPathEnd >= 0; nPathEnd --)	//获得程序路径
		{   
			if (buffModulPath[nPathEnd]=='\\')   
			{     
				buffModulPath[nPathEnd+1]='\0';   
  				strcat(buffModulPath,CTextName);   
    
  				break;   
			}   
		}   
		str3.Format("%s",(LPCTSTR)buffModulPath);   
    
		DWORD dwPos;   
    
		//创建“CrazyEditer应用程序”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset1,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“用CrazyEditer打开”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str1,str1.GetLength());   
		//创建“command”子键   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset2,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为SLW应用程序的路径   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str2,str2.GetLength());   
    
		//创建Default项。   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset3Icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//将该子键的“默认”数据项的数据设置为“CrazyEditer图标”   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str3,str3.GetLength());   
    
		::RegCloseKey(hresult);  

		MessageBox ("已将信息写入注册表，系统重启后生效。","系统提示");
	}
}

//加密的处理函数()
/*
通过销毁创建加密型(ES_PASSWORD|ES_READONLY)/非加密型的对话框 
来实现加密和解密。
问题：虽然成功写入注册表，但是并没有办法把加密的密码也写入，
所以当文件关闭的时候，加密效果就没有了。
*/
void CCrazyEditerDlg::Code(){

	if(!code_IsChecked){   //若文本未加密，则加密
		CCodeDlg dlg;
		if(dlg.DoModal() == IDOK){
			//m_ToolBar.CheckDlgButton(10,TBBS_CHECKBOX); 
			m_RichEdit->GetWindowText(strEdit);
			m_RichEdit->DestroyWindow();	//销毁编辑框
			m_RichEdit->Create(WS_VISIBLE|WS_CHILD|ES_PASSWORD|ES_READONLY|ES_AUTOHSCROLL|WS_HSCROLL|ES_WANTRETURN
				|WS_VSCROLL|WS_BORDER|ES_MULTILINE,CRect(5,65,665,735),this,0); //创建加密型的编辑框
			m_RichEdit->SetDefaultCharFormat(cf);   //恢复字体属性
			m_RichEdit->SetBackgroundColor(false,m_BackgroundColor); //恢复背景颜色
			m_RichEdit->SetWindowText(strEdit);
			m_RichEdit->SetModify(true);
			code_IsChecked = true;  //说明文本已加密
		};
	}else{   //若已加密，则解密
		CDecodeDlg dlg;
		if(dlg.DoModal() == IDOK){
			m_RichEdit->GetWindowText(strEdit);
			m_RichEdit->DestroyWindow();	//销毁编辑框
			m_RichEdit->Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|WS_HSCROLL|ES_WANTRETURN
				|WS_VSCROLL|WS_BORDER|ES_MULTILINE,CRect(5,65,665,735),this,0); //创建非加密型的编辑框
			m_RichEdit->SetDefaultCharFormat(cf);   //恢复字体属性
			m_RichEdit->SetBackgroundColor(false,m_BackgroundColor); //恢复背景颜色
			m_RichEdit->SetWindowText(strEdit);
			m_RichEdit->SetModify(true);
			code_IsChecked = false;  //说明文本未加密
		};
	}

}

//帮助的处理函数()
void CCrazyEditerDlg::OnMenuHelp(){
	CHelpDlg dlg;
	dlg.DoModal();
}