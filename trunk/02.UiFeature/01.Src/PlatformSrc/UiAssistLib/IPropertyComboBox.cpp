
#include "stdafx.h"
#include "..\..\Inc\IPropertyComboBox.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyComboBox::IPropertyComboBox()
{
	SetObjectType(PROP_TYPE_COMBOBOX_NAME);
	Clear();
}

IPropertyComboBox::~IPropertyComboBox()
{
	Clear();
}

void IPropertyComboBox::Clear()
{
	m_ComboBoxPro.nSelect = -1;
	m_ComboBoxPro.DataVec.clear();
}

bool IPropertyComboBox::IsRightData()
{
	return (m_ComboBoxPro.DataVec.size() > 0 && m_ComboBoxPro.nSelect >= 0 && m_ComboBoxPro.nSelect < (int)m_ComboBoxPro.DataVec.size());
}

COMBOBOX_PROP* IPropertyComboBox::GetComboBoxData()
{
	return &m_ComboBoxPro;
}

bool IPropertyComboBox::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_counts = JabberXmlGetAttrValue(pXmlNode, "counts");
	char* psz_select = JabberXmlGetAttrValue(pXmlNode, "select");
	if (psz_id == NULL || psz_name == NULL || psz_counts == NULL || psz_select == NULL)
		return false;

	int nCtns = atoi(psz_counts);

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	m_ComboBoxPro.nSelect = atoi(psz_select);
	if (m_ComboBoxPro.nSelect < 0 || m_ComboBoxPro.nSelect >= nCtns)
		m_ComboBoxPro.nSelect = 0;

	for (int i = 0; i < nCtns; i++)
	{
		char pszDataName[MAX_PATH + 1];
		memset(pszDataName, 0, MAX_PATH + 1);
		sprintf_s(pszDataName, MAX_PATH, "data%d", i);

		char* psz_data = JabberXmlGetAttrValue(pXmlNode, pszDataName);
		if (psz_data == NULL)
		{
			Clear();
			return false;
		}

		string strData = psz_data;
		m_ComboBoxPro.DataVec.push_back(strData);
	}

	return true;
}

// 写入xml
bool IPropertyComboBox::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
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
	AddIntAttrToNode(pPropNode, "counts", m_ComboBoxPro.DataVec.size());
	AddIntAttrToNode(pPropNode, "select", m_ComboBoxPro.nSelect);

	int nNo = 0;
	for (STRING_VEC::iterator pStringItem = m_ComboBoxPro.DataVec.begin(); pStringItem != m_ComboBoxPro.DataVec.end(); pStringItem++)
	{
		string strString = *pStringItem;
		if (strString.size() <= 0)
			continue;

		char pszDataName[MAX_PATH + 1];
		memset(pszDataName, 0, MAX_PATH + 1);
		sprintf_s(pszDataName, MAX_PATH, "data%d", nNo);

		pPropNode->AddAttribute(pszDataName, strString.c_str());
		nNo++;
	}

	return true;
}

// 设置选中项
void IPropertyComboBox::SetSelect(int nSel)
{
	if (nSel < 0 || nSel >= (int)m_ComboBoxPro.DataVec.size() || m_ComboBoxPro.nSelect == nSel)
		return;

	m_ComboBoxPro.nSelect = nSel;
}

int IPropertyComboBox::GetSelect()
{
	return m_ComboBoxPro.nSelect;
}

void IPropertyComboBox::SetSelectString(char *pszSelString)
{
	if (pszSelString == NULL || strlen(pszSelString) <= 0)
		return;

	int nNo = 0;
	for (STRING_VEC::iterator pStringItem = m_ComboBoxPro.DataVec.begin(); pStringItem != m_ComboBoxPro.DataVec.end(); pStringItem++, nNo++)
	{
		string strString = *pStringItem;
		if (strString.size() <= 0)
			continue;

		if (lstrcmpiA(pszSelString, strString.c_str()) == 0)
		{
			m_ComboBoxPro.nSelect = nNo;
			return;
		}
	}
}
