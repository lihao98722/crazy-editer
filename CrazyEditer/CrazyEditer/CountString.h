#pragma once


// CCountString �Ի���

class CCountString : public CDialogEx
{
	DECLARE_DYNAMIC(CCountString)

public:
	CCountString(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCountString();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//EditControl��value�Ϳؼ�����
	CString m_StringToCount;		//�˶Ի���༭��������ݣ�����Ҫͳ�Ƶ��ַ���
	UINT resultOfCount;				//�ַ�������

	//�������༭������
	CString text;				

	//��ȡ���༭�����ݵĴ�����
	void SetText (CString);

	afx_msg void OnBnClickedCountstring();
};
