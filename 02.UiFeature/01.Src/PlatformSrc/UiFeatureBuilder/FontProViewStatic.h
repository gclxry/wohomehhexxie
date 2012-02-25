#pragma once
#include "..\..\inc\IPropertyFontBase.h"


// CFontProViewStatic

class CFontProViewStatic : public CStatic
{
	DECLARE_DYNAMIC(CFontProViewStatic)

	void RedrawView(IPropertyFontBase* pFontBaseProp);

private:
	IPropertyFontBase* m_pFontBaseProp;
	CDrawingBoard m_MemDc;

public:
	CFontProViewStatic();
	virtual ~CFontProViewStatic();

	string m_strText;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


