//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"

// ComboBox属性
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

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);

	COMBOBOX_PROP* GetComboBoxData();

private:
	void Clear();

private:
	COMBOBOX_PROP m_ComboBoxPro;
};
