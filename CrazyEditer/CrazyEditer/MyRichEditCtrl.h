#pragma once

// CMyRichEditCtrl

class CMyRichEditCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CMyRichEditCtrl)

public:
	CMyRichEditCtrl();
	virtual ~CMyRichEditCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
