// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
	, text(_T(""))
{
	text += "一.运行环境\r\n";
	text += "\r\n";
    text += "      Windows 32/64位操作系统\r\n";
	text += "\r\n";

	text += "二.程序使用简介\r\n\r\n";
    text += "     1.程序包含菜单栏、工具栏、编辑框、状态栏。\r\n";
	text += "\r\n";
    text += "     2.菜单栏、工具栏操作对应的快捷键如下：\r\n";
	text += "\r\n";
    text += "            新建：Ctrl+N        打开：Ctrl+O\r\n";
    text += "            保存：Ctrl+S        另存为：Ctrl+Alt+S\r\n";
	text += "            打印：Ctrl+P        退出：Ctrl+P\r\n";
	text += "            撤销：Ctrl+Z        全选：Ctrl+A\r\n";
    text += "            剪切：Ctrl+X        复制：Ctrl+C\r\n";
    text += "            粘贴：Ctrl+V        查找替换：Ctrl+F\r\n";
    text += "            字体：Alt+F         帮助：Ctrl+H\r\n";
	text += "\r\n";
	text += "     3.状态栏：显示光标所在行列数、大写锁定状态、\r\n";
	text += "                        当前时间\r\n";

	text += "\r\n";
	text += "三.特殊功能\r\n";
	text += "\r\n";
    text += "     1.查找/替换：\r\n";
	text += "\r\n";
    text += "        ①在查找替换界面,可以从光标位置逐个查找\r\n";
	text += "          相应内容,用户可以选择是否替换当前\r\n";
	text += "          字符串或者全部替换为指定字符串。\r\n";
	text += "\r\n";
	text += "     2.统计：\r\n";
	text += "\r\n";
	text += "        ①统计所有字符：\r\n";
	text += "          可以统计出当前文本内全部字符的个数,还能\r\n";
	text += "          精确地统计出文本内中文字符、英文、数字、\r\n";
	text += "          空白符、半角标点符号的个数。\r\n";
	text += "\r\n";
	text += "        ②统计字符串：\r\n";
	text += "          可以统计用户所要统计的字符串在文本中出现\r\n";
	text += "          的次数,如果要统计的字符串不在文本中还会\r\n";
	text += "          有相应的提示。\r\n";
	text += "\r\n";
    text += "     3.字体：\r\n";
	text += "\r\n";
	text += "        ①在字体设置的对话框中,可以设置字体\r\n";
	text += "          的字形、大小等基本属性。\r\n";
	text += "\r\n";
	text += "        ②可以任意设定字体颜色。\r\n";
	text += "\r\n";
	text += "     4.背景颜色：\r\n";
	text += "\r\n";
	text += "        ①可以任意设定编辑框的背景颜色。\r\n";
	text += "\r\n";
	text += "     5.安全：\r\n";
	text += "\r\n";
	text += "        ①写入注册表：向注册表添加CrazyEditer文件关\r\n";
	text += "          联，改变文本（.txt）文件图标，并\r\n";
	text += "          使文本（.txt）文件可单击右键后选\r\n";
	text += "          择用本程序打开(部分功能重启或注\r\n";
	text += "          销后方能生效)。\r\n";
	text += "\r\n";
	text += "        ②加密：在程序界面内，用户可以对当前文本\r\n";
	text += "          进行加密，加密后，文本会隐藏，而且当前编辑框\r\n";
	text += "          变成不可编辑的状态，只有当用户正确解密后才能\r\n";
	text += "          继续编辑。\r\n";
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, text);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


