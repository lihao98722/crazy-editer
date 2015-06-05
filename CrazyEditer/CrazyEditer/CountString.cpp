// CountString.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "CountString.h"
#include "afxdialogex.h"


// CCountString �Ի���

IMPLEMENT_DYNAMIC(CCountString, CDialogEx)

CCountString::CCountString(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountString::IDD, pParent)
	, m_StringToCount(_T(""))
	, resultOfCount(0)
{
	//Ĭ�ϳ�ʼ��������
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


// CCountString ��Ϣ�������


//��ȡ���༭������
void CCountString::SetText (CString str)
{
	text = str;
}


//ͳ���ַ���
/*
�ڲ���ǰ�����ж����༭���Լ�ͳ���ַ����༭���������; �����༭���ͳ���ַ�
�༭���ﶼ��Ϊ�գ�����в���; ����ʱ�����ҵ���һ�γ��ִ�ͳ���ַ����ĵط���
Ȼ���ü�����+1�������������ò��ҵ���ʼλ�ã����ǰ���ʼλ�����ڲ��ҵ����ַ������ֵ�
�ط�֮�󣩣�һֱѭ��ֱ�����ҽ���
*/
void CCountString::OnBnClickedCountstring()
{
	UpdateData(TRUE);    //��ȡ��ѯ�༭������
	resultOfCount = 0;   //ͳ�ƴ������¹���
	int length = m_StringToCount.GetLength();  //��ͳ��String�ĳ���
	int totalLength = text.GetLength();    //���༭���ı����ܳ���
	int i = 0;
	int index = 0;

	//����ǰ���ж����༭���Լ�ͳ���ַ����༭���������

	if(totalLength == 0){                        //�༭��������
		MessageBox("�༭��û�����ݣ�");
		resultOfCount = 0;
	}
	else if(length == 0){						 //ͳ���ַ����༭��������
		MessageBox("��������Ҫͳ�Ƶ��ַ�����");
		resultOfCount = 0;
	}else{

		//ѭ��ͳ���ַ�����

		for (i = 0,index = 0; index + length < totalLength && index != -1; i = index + 1){

			index = text.Find(m_StringToCount, i);  //�����ַ���

			if (index != -1){
				resultOfCount ++;                     //�ҵ��������1
				if (text.GetAt(index)>255||text.GetAt(index)<0){
					index ++;					 //������һ������λ��
				}
			}

		}
	}
	//������ɺ��жϽ��

	if(totalLength !=0 && length !=0 && resultOfCount == 0){      //���û���ҵ��κη��ϵ��ַ���
		MessageBox("��Ҫͳ�Ƶ��ַ��������ı��У�");
		resultOfCount = 0;
	}
	
	UpdateData (FALSE);						 //����ͳ�ƽ��
}
