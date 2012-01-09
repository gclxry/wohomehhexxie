
#include "stdafx.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyString::IPropertyString()
{
	SetObjectType(PROP_TYPE_STRING_NAME);
	Clear();
}

IPropertyString::~IPropertyString()
{

}

void IPropertyString::Clear()
{
	m_StringProp.strDefaultString = "";
	m_StringProp.nDefaultArea = AT_CN;
	m_StringProp.StringMap.clear();
}

bool IPropertyString::IsRightData()
{
	return (m_StringProp.strDefaultString.size() > 0);
}

void IPropertyString::SetArea(AREA_TYPE areaType)
{
	if (areaType > AT_NONE && areaType < AT_LAST)
	{
		m_StringProp.nDefaultArea = areaType;
		ResetDefaultString();
	}
}

bool IPropertyString::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	Clear();
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_counts = JabberXmlGetAttrValue(pXmlNode, "counts");
	char* psz_default = JabberXmlGetAttrValue(pXmlNode, "defaultarea");
	if (psz_id == NULL || psz_name == NULL || psz_counts == NULL || psz_default == NULL)
		return false;

	int nCtns = atoi(psz_counts);

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	m_StringProp.nDefaultArea = (AREA_TYPE)atoi(psz_default);
	if (m_StringProp.nDefaultArea <= AT_NONE || m_StringProp.nDefaultArea >= AT_LAST)
		m_StringProp.nDefaultArea = AT_CN;

	for (int i = 0; i < nCtns; i++)
	{
		char pszDataName[MAX_PATH + 1], pszAreaName[MAX_PATH + 1];
		memset(pszDataName, 0, MAX_PATH + 1);
		memset(pszAreaName, 0, MAX_PATH + 1);

		sprintf_s(pszDataName, MAX_PATH, "data%d", i);
		sprintf_s(pszAreaName, MAX_PATH, "area%d", i);

		char* psz_data = JabberXmlGetAttrValue(pXmlNode, pszDataName);
		char* psz_area = JabberXmlGetAttrValue(pXmlNode, pszAreaName);
		if (psz_data == NULL || psz_area == NULL)
		{
			Clear();
			return false;
		}

		AREA_TYPE nArea = (AREA_TYPE)atoi(psz_area);
		string strData = psz_data;
		m_StringProp.StringMap.insert(pair<AREA_TYPE, string>(nArea, strData));
	}

	ResetDefaultString();
	return true;
}

const char* IPropertyString::GetString()
{
	return (m_StringProp.strDefaultString.c_str());
}

void IPropertyString::SetString(char* pszString)
{
	if (pszString == NULL)
		return;

	STRING_MAP::iterator pStringItem = m_StringProp.StringMap.find(m_StringProp.nDefaultArea);
	if (pStringItem == m_StringProp.StringMap.end())
	{
		string strString = pszString;
		m_StringProp.StringMap.insert(pair<AREA_TYPE, string>(m_StringProp.nDefaultArea, strString));
	}
	else
	{
		string &strString = pStringItem->second;
		strString = pszString;
	}
	m_StringProp.strDefaultString = pszString;
}

void IPropertyString::ResetDefaultString()
{
	STRING_MAP::iterator pStringItem = m_StringProp.StringMap.find(m_StringProp.nDefaultArea);
	if (pStringItem == m_StringProp.StringMap.end())
		return;

	string &strString = pStringItem->second;
	m_StringProp.strDefaultString = strString;
}

// д��xml
bool IPropertyString::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	AddIntAttrToNode(pPropNode, "counts", m_StringProp.StringMap.size());
	AddIntAttrToNode(pPropNode, "defaultarea", m_StringProp.nDefaultArea);

	int nNo = 0;
	for (STRING_MAP::iterator pStringItem = m_StringProp.StringMap.begin(); pStringItem != m_StringProp.StringMap.end(); pStringItem++)
	{
		AREA_TYPE areaType = pStringItem->first;
		string strString = pStringItem->second;
		if (strString.size() <= 0)
			continue;

		char pszDataName[MAX_PATH + 1], pszAreaName[MAX_PATH + 1];
		memset(pszDataName, 0, MAX_PATH + 1);
		memset(pszAreaName, 0, MAX_PATH + 1);
		sprintf_s(pszDataName, MAX_PATH, "data%d", nNo);
		sprintf_s(pszAreaName, MAX_PATH, "area%d", nNo);

		AddIntAttrToNode(pPropNode, pszAreaName, areaType);
		pPropNode->AddAttribute(pszDataName, strString.c_str());
		nNo++;
	}

	return true;
}