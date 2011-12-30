
#include "stdafx.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyFont::IPropertyFont()
{
}

IPropertyFont::~IPropertyFont()
{

}

bool IPropertyFont::IsRightData()
{
	return (GetRelevancyProp() != NULL);
}

IPropertyFontBase* IPropertyFont::GetFontBaseProp()
{
	return dynamic_cast<IPropertyFontBase*>(GetRelevancyProp());
}

void IPropertyFont::SetFontBaseProp(IPropertyFontBase *pFontProp)
{
	if (pFontProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pFontProp);
	SetRelevancyProp(pPropBase);
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

// Ð´Èëxml
bool IPropertyFont::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode("item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	pPropNode->AddAttribute("fontbasename", GetRelevancyPropName());
	return true;
}
