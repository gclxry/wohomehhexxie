//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ComboBox����
struct COMBOBOX_PROP
{
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
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);

	COMBOBOX_PROP* GetComboBoxData();

private:
	void Clear();

private:
	COMBOBOX_PROP m_ComboBoxPro;
};
