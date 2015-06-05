// CountString.cpp : 实现文件
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CountString.h"
#include "afxdialogex.h"


// CCountString 对话框

IMPLEMENT_DYNAMIC(CCountString, CDialogEx)

CCountString::CCountString(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountString::IDD, pParent)
	, m_StringToCount(_T(""))
	, resultOfCount(0)
{
	//默认初始化就行了
}

CCountString::~CCountString()
{
}

void CCountString::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StringToCount);
	DDX_Text(pDX, IDC_EDIT2, resultOfCount);
}


BEGIN_MESSAGE_MAP(CCountString, CDialogEx)
	ON_BN_CLICKED(IDCOUNTSTRING, &CCountString::OnBnClickedCountstring)
END_MESSAGE_MAP()


// CCountString 消息处理程序


//获取主编辑区内容
void CCountString::SetText (CString str)
{
	text = str;
}


//统计字符串
/*
在查找前，先判断主编辑框以及统计字符串编辑框里的内容; 若主编辑框和统计字符
编辑框里都不为空，则进行查找; 查找时，先找到第一次出现待统计字符串的地方，
然后让计数器+1，接着重新设置查找的起始位置（就是把起始位置设在查找到的字符串出现的
地方之后），一直循环直到查找结束
*/
void CCountString::OnBnClickedCountstring()
{
	UpdateData(TRUE);    //获取查询编辑框内容
	resultOfCount = 0;   //统计次数重新归零
	int length = m_StringToCount.GetLength();  //待统计String的长度
	int totalLength = text.GetLength();    //主编辑框文本的总长度
	int i = 0;
	int index = 0;

	//查找前先判断主编辑框以及统计字符串编辑框里的内容

	if(totalLength == 0){                        //编辑区无内容
		MessageBox("编辑框没有内容！");
		resultOfCount = 0;
	}
	else if(length == 0){						 //统计字符串编辑框无内容
		MessageBox("请输入您要统计的字符串！");
		resultOfCount = 0;
	}else{

		//循环统计字符个数

		for (i = 0,index = 0; index + length < totalLength && index != -1; i = index + 1){

			index = text.Find(m_StringToCount, i);  //查找字符串

			if (index != -1){
				resultOfCount ++;                     //找到则计数加1
				if (text.GetAt(index)>255||text.GetAt(index)<0){
					index ++;					 //设置下一个查找位置
				}
			}

		}
	}
	//查找完成后判断结果

	if(totalLength !=0 && length !=0 && resultOfCount == 0){      //如果没有找到任何符合的字符串
		MessageBox("您要统计的字符串不在文本中！");
		resultOfCount = 0;
	}
	
	UpdateData (FALSE);						 //更新统计结果
}
