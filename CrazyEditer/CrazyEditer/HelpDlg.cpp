// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrazyEditer.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg �Ի���

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
	, text(_T(""))
{
	text += "һ.���л���\r\n";
	text += "\r\n";
    text += "      Windows 32/64λ����ϵͳ\r\n";
	text += "\r\n";

	text += "��.����ʹ�ü��\r\n\r\n";
    text += "     1.��������˵��������������༭��״̬����\r\n";
	text += "\r\n";
    text += "     2.�˵�����������������Ӧ�Ŀ�ݼ����£�\r\n";
	text += "\r\n";
    text += "            �½���Ctrl+N        �򿪣�Ctrl+O\r\n";
    text += "            ���棺Ctrl+S        ���Ϊ��Ctrl+Alt+S\r\n";
	text += "            ��ӡ��Ctrl+P        �˳���Ctrl+P\r\n";
	text += "            ������Ctrl+Z        ȫѡ��Ctrl+A\r\n";
    text += "            ���У�Ctrl+X        ���ƣ�Ctrl+C\r\n";
    text += "            ճ����Ctrl+V        �����滻��Ctrl+F\r\n";
    text += "            ���壺Alt+F         ������Ctrl+H\r\n";
	text += "\r\n";
	text += "     3.״̬������ʾ�����������������д����״̬��\r\n";
	text += "                        ��ǰʱ��\r\n";

	text += "\r\n";
	text += "��.���⹦��\r\n";
	text += "\r\n";
    text += "     1.����/�滻��\r\n";
	text += "\r\n";
    text += "        ���ڲ����滻����,���Դӹ��λ���������\r\n";
	text += "          ��Ӧ����,�û�����ѡ���Ƿ��滻��ǰ\r\n";
	text += "          �ַ�������ȫ���滻Ϊָ���ַ�����\r\n";
	text += "\r\n";
	text += "     2.ͳ�ƣ�\r\n";
	text += "\r\n";
	text += "        ��ͳ�������ַ���\r\n";
	text += "          ����ͳ�Ƴ���ǰ�ı���ȫ���ַ��ĸ���,����\r\n";
	text += "          ��ȷ��ͳ�Ƴ��ı��������ַ���Ӣ�ġ����֡�\r\n";
	text += "          �հ׷�����Ǳ����ŵĸ�����\r\n";
	text += "\r\n";
	text += "        ��ͳ���ַ�����\r\n";
	text += "          ����ͳ���û���Ҫͳ�Ƶ��ַ������ı��г���\r\n";
	text += "          �Ĵ���,���Ҫͳ�Ƶ��ַ��������ı��л���\r\n";
	text += "          ����Ӧ����ʾ��\r\n";
	text += "\r\n";
    text += "     3.���壺\r\n";
	text += "\r\n";
	text += "        �����������õĶԻ�����,������������\r\n";
	text += "          �����Ρ���С�Ȼ������ԡ�\r\n";
	text += "\r\n";
	text += "        �ڿ��������趨������ɫ��\r\n";
	text += "\r\n";
	text += "     4.������ɫ��\r\n";
	text += "\r\n";
	text += "        �ٿ��������趨�༭��ı�����ɫ��\r\n";
	text += "\r\n";
	text += "     5.��ȫ��\r\n";
	text += "\r\n";
	text += "        ��д��ע�����ע������CrazyEditer�ļ���\r\n";
	text += "          �����ı��ı���.txt���ļ�ͼ�꣬��\r\n";
	text += "          ʹ�ı���.txt���ļ��ɵ����Ҽ���ѡ\r\n";
	text += "          ���ñ������(���ֹ���������ע\r\n";
	text += "          ��������Ч)��\r\n";
	text += "\r\n";
	text += "        �ڼ��ܣ��ڳ�������ڣ��û����ԶԵ�ǰ�ı�\r\n";
	text += "          ���м��ܣ����ܺ��ı������أ����ҵ�ǰ�༭��\r\n";
	text += "          ��ɲ��ɱ༭��״̬��ֻ�е��û���ȷ���ܺ����\r\n";
	text += "          �����༭��\r\n";
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


// CHelpDlg ��Ϣ�������


