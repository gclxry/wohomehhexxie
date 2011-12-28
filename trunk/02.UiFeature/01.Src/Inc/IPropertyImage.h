//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "CMemoryDC.h"
#include "IPropertyImageBase.h"

class IPropertyImage : public IPropertyBase
{
public:
	IPropertyImage();
	virtual ~IPropertyImage();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builder使用函数，即：编辑状态下使用函数

//////////////////////////////////////////////////////////////////////////
	// 运行时态使用函数
	IPropertyImageBase* GetImageBaseProp();
	const char * GetImageBaseName();
	bool DrawImage(CMemoryDC &DstDc, RECT DstRct);

private:
	string m_strImageBaseName;
	IPropertyImageBase *m_pImageBaseProp;
};
