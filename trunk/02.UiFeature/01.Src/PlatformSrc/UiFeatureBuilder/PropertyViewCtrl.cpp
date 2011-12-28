#include "StdAfx.h"
#include "PropertyViewCtrl.h"

CPropertyViewCtrl::CPropertyViewCtrl(void)
{
	m_pPropGroup = NULL;
}

CPropertyViewCtrl::~CPropertyViewCtrl(void)
{
}

void CPropertyViewCtrl::ClearAll()
{
	m_pPropGroup = NULL;
	this->RemoveAll();
}

void CPropertyViewCtrl::SetShowPropGroup(IPropertyGroup *pPropGroup)
{
	ClearAll();
	if (pPropGroup == NULL)
		return;

	m_pPropGroup = pPropGroup;

}
