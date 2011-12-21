//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ComboBox����
struct COMBOBOX_PROP
{
	// ��������
	string strName;
	int nSelect;
	STRING_VEC DataVec;
};

class IPropertyComboBox : public IPropertyBase
{
public:
	IPropertyComboBox();
	~IPropertyComboBox();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ȡ����������
	virtual PROP_TYPE GetPropType();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

private:
	void Clear();

private:
	COMBOBOX_PROP m_ComboBoxPro;
};
