
#include "stdafx.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

IPropertyFont::IPropertyFont()
{
	SetObjectType(PROP_TYPE_FONT_NAME);
}

IPropertyFont::~IPropertyFont()
{

}

const char * IPropertyFont::GetFontBaseName()
{
	return GetRelevancyPropName();
}

bool IPropertyFont::IsRightData()
{
	return (GetRelevancyProp() != NULL);
}

IPropertyFontBase* IPropertyFont::GetFontBaseProp()
{
	return dynamic_cast<IPropertyFontBase*>(GetRelevancyProp());
}

void IPropertyFont::SetNeedRedraw()
{
	if (GetOwnerObject() == NULL)
		return;

	IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(GetOwnerObject());
	if (pCtrlBase == NULL)
		return;

	pCtrlBase->RedrawControl();
}

void IPropertyFont::SetFontBaseProp(IPropertyFontBase *pFontProp)
{
	if (pFontProp == NULL)
	{
		SetRelevancyProp(NULL);
		SetNeedRedraw();
		return;
	}

	IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pFontProp);
	SetRelevancyProp(pPropBase);
	SetNeedRedraw();
}

bool IPropertyFont::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_fontbasename = JabberXmlGetAttrValue(pXmlNode, "fontbasename");
	if (psz_id == NULL || psz_name == NULL || psz_fontbasename == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	SetRelevancyPropName(psz_fontbasename);

	return true;
}

// 写入xml
bool IPropertyFont::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	// 如果是无效属性，不写入XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	pPropNode->AddAttribute("fontbasename", GetRelevancyPropName());
	return true;
}
