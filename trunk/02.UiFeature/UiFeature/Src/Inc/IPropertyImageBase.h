//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "IZipFile.h"
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

enum IMAGE_PLAY_TYPE
{
	// 静态
	IPT_STATIC_IMG		= 0,
	// GIF
	IPT_GIF,
	// 图片序列
	IPT_IMAGE_XULIE
};

enum IMAGE_LOOP_TYPE
{
	// 循环一次
	ILT_LOOP_1		= 0,
	// 无限循环
	ILT_LOOP
};

enum IMAGE_BOFANG_TYPE
{
	// 正向播放
	IBFT_ZHENGXIANG		= 0,
	// 反向播放
	IBFT_FANXIANG
};

// 图片属性
struct IMAGE_BASE_PROP
{
	// 用于识别 strFileName ，如果不是 zipfile，说明是本地完整的路径
	bool bIsZipFile;
	// 在压缩文件中的文件名
	char strFileName[MAX_PATH + 1];
	// 九宫格拉伸等
	IMAGE_SHOW_TYPE ImgShowType;
	// 图片序列
	IMAGE_PLAY_TYPE ImgPlayType;
	// 循环次数
	IMAGE_LOOP_TYPE ImgLoopType;
	// 正向/反向播放
	IMAGE_BOFANG_TYPE ImgBoFangType;
	RECT RectInImage;
	// 九宫格数据
	RECT jggInfo;
	// 是否绘制九宫格中间区域
	bool bIsDrawJggMid;
};

class IPropertyImageBase : public IPropertyBase
{
public:
	virtual bool GetActivePropetry() = 0;

	// 是否为合法数据
	virtual bool IsRightData() = 0;
	// 从XML节点读取属性值，并放入属性队列
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// 写入xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

//////////////////////////////////////////////////////////////////////////
	// Builder使用函数，即：编辑状态下使用函数

//////////////////////////////////////////////////////////////////////////
	// 生成缩略图，缩略图如果外部要释放，调用 IPropertySkinManager::DeleteImageBase() 即可，也可不释放，内核会在最后一起释放
	virtual IPropertyImageBase* CreateThumbnailImage(SIZE sizeThumbnail) = 0;
	// 运行时态使用函数
	virtual void SetImageProp(IMAGE_BASE_PROP* pImgProp) = 0;
	virtual IMAGE_BASE_PROP* GetImageProp() = 0;
	virtual ZIP_FILE * GetZipFile() = 0;
	virtual bool SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc) = 0;
	virtual SIZE GetImageSize() = 0;
	// 得到图片的内存DC
	virtual CDrawingImage* GetDrawingImage() = 0;
	// 创建图片的内存DC
	virtual CDrawingImage* CreateDrawingImage() = 0;
	// 初始化Image，将Image加载到内存，程序默认是没有加载图片数据的
	virtual void InitImage() = 0;
	// 轻量级动画定时器绘制动画
	virtual bool OnDrawAnimation() = 0;
	// 设置使用计数
	virtual void AddUseCounts() = 0;
	// 减掉技术
	virtual void SubtractUseCounts() = 0;
	// 取得使用技术
	virtual int GetUseCounts() = 0;

	// 绘制图片，如果alpha不是255，则根据这个alpha值来绘制
	virtual bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255) = 0;
	virtual bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255) = 0;
};
