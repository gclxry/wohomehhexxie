//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "CMemoryDC.h"

// 九宫格数据
struct JGG_INFO
{
	// 九宫格边线距离
	int nLeftSpace;
	int nRightSpace;
	int nTopSpace;
	int nBottomSpace;
	// 九宫格是否拉伸，不拉伸则平铺
	bool bLeftStretch;
	bool bRightStretch;
	bool bTopStretch;
	bool bBottomStretch;
	bool bMiddleStretch;
};

// 图片属性
struct IMAGE_PROP
{
	int nPropId;
	string strName;
	string strPropInfo;
	// 在压缩文件中的文件名
	string strZipFile;
	RECT RectInImage;
	JGG_INFO jggInfo;
};

class IPropertyImage : public IPropertyBase
{
public:
	IPropertyImage();
	~IPropertyImage();

	// 是否为合法数据
	virtual bool IsRightData();
	// 取得属性类型
	virtual PROP_TYPE GetPropType();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builder使用函数，即：编辑状态下使用函数

//////////////////////////////////////////////////////////////////////////
	// 运行时态使用函数
	void SetImageProp(IMAGE_PROP* pImgProp);
	IMAGE_PROP* GetImageProp();

	bool DrawImage(CMemoryDC &DstDc, RECT DstRct);

private:
	IMAGE_PROP m_ImageProp;
};
