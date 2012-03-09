#pragma once


// CWindowTreeToolBar

class CWindowTreeToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CWindowTreeToolBar)

public:
	CWindowTreeToolBar();
	virtual ~CWindowTreeToolBar();

	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }

protected:
	DECLARE_MESSAGE_MAP()
};


