//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ComboBox����
struct COMBOBOX_PROP
{
	// ��������
	string strName;
	string strPropInfo;
	int nSelect;
	STRING_VEC DataVec;
};

class IPropertyComboBox : public IPropertyBase
{
public:
	IPropertyComboBox();
	virtual ~IPropertyComboBox();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	void Clear();

private:
	COMBOBOX_PROP m_ComboBoxPro;
};
