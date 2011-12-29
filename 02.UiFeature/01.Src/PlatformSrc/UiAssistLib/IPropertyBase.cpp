
#include "stdafx.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBase::IPropertyBase()
{
	SetObjectType("PropertyBase");
}

IPropertyBase::~IPropertyBase()
{

}

bool IPropertyBase::IsRightData()
{
	return (strlen(this->GetObjectName()) > 0);
}

// 从XML节点读取属性值，并放入属性队列
bool IPropertyBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	return false;
}
