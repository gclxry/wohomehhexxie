//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "CDrawingImage.h"

enum IMAGE_SHOW_TYPE
{
	// 平铺
	IST_PINGPU		= 0,
	// 全拉伸
	IST_ALL_LASHEN,
	// 九宫格拉伸
	IST_JGG_LASHEN
};

// 图片属性
struct IMAGE_BASE_PROP
{
	// 用于识别 strFileName ，如果不是 zipfile，说明是本地完整的路径
	bool bIsZipFile;
	// 在压缩文件中的文件名
	string strFileName;
	IMAGE_SHOW_TYPE ImgShowType;
	RECT RectInImage;
// 九宫格数据
	RECT jggInfo;
};

class IPropertyImageBase : public IPropertyBase
{
	friend class IPropertyImage;
public:
	IPropertyImageBase();
	virtual ~IPropertyImageBase();

	virtual void SetActivePropetry(bool bIsActive);
	virtual bool GetActivePropetry();

	// 是否为合法数据
	virtual bool IsRightData();
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builder使用函数，即：编辑状态下使用函数

//////////////////////////////////////////////////////////////////////////
	// 运行时态使用函数
	void SetImageProp(IMAGE_BASE_PROP* pImgProp);
	IMAGE_BASE_PROP* GetImageProp();

private:
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct);

private:
	IMAGE_BASE_PROP m_ImageProp;
	CDrawingImage m_DrawImg;
	// 被使用的计数器
	int m_nUseCtns;
};
