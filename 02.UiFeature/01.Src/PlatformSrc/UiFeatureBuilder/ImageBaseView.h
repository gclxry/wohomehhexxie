
#pragma once
#include "DialogViewBase.h"


// CImageBaseView dialog

class CImageBaseView : public CDialogViewBase
{
	DECLARE_DYNAMIC(CImageBaseView)

public:
	CImageBaseView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageBaseView();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
