//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "IPropertyImageBase.h"

class IPropertyImage : public IPropertyBase
{
public:
	IPropertyImage();
	virtual ~IPropertyImage();

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
	IPropertyImageBase* GetImageBaseProp();
	void SetImageBaseProp(IPropertyImageBase* pNewImgBase);

	const char * GetImageBaseName();

	SIZE GetImageSize();

	// 绘制图片，如果alpha不是255，则根据这个alpha值来绘制
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);

	bool OnDrawAnimation();

	void SetNeedRedraw();
};
