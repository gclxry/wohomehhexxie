#pragma once
#include "afxpropertygridctrl.h"
#include "..\..\Inc\IPropertyGroup.h"

class CPropertyViewCtrl : public CMFCPropertyGridCtrl
{
public:
	CPropertyViewCtrl(void);
	~CPropertyViewCtrl(void);

	void ClearAll();
	void SetShowPropGroup(IPropertyGroup *pPropGroup);

private:
	IPropertyGroup *m_pPropGroup;
};
