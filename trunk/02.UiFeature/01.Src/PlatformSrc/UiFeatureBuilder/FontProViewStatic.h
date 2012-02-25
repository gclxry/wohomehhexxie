#pragma once
#include "..\..\inc\IPropertyFontBase.h"


// CFontProViewStatic

class CFontProViewStatic : public CStatic
{
	DECLARE_DYNAMIC(CFontProViewStatic)

	void RedrawView(IPropertyFontBase* pFontBaseProp);

private:
	IPropertyFontBase* m_pFontBaseProp;

public:
	CFontProViewStatic();
	virtual ~CFontProViewStatic();

protected:
	DECLARE_MESSAGE_MAP()
};


