//////////////////////////////////////////////////////////////////////////
// 属性

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "CDrawingImage.h"
#include "IZipFile.h"

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
	string strFileName;
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

class CGifImage;
class IPropertyImageBase : public IPropertyBase
{
public:
	IPropertyImageBase();
	virtual ~IPropertyImageBase();

	static void InitPropImageBase(IMAGE_BASE_PROP *pImgBaseProp);

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

	ZIP_FILE * GetZipFile();
	void SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc);

	// 绘制图片，如果alpha不是255，则根据这个alpha值来绘制
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);

	bool OnDrawAnimation();

	SIZE GetImageSize();

	// 得到图片的内存DC
	CDrawingImage* GetDrawingImage();
private:
	bool DrawImage_AllLaShen(CDrawingBoard &DstDc, RECT DstRct);
	bool DrawImage_PingPu(CDrawingBoard &DstDc, RECT DstRct);
	bool DrawImage_JggLaShen(CDrawingBoard &DstDc, RECT DstRct);
	bool SetXuLieDrawInTimer();
	bool InitDrawXuLieRect();

	bool SetGifDrawInTimer();
	void InitGifImage();

private:
	IMAGE_BASE_PROP m_ImageProp;
	CDrawingImage m_DrawImg;
	// 被使用的计数器
	int m_nUseCtns;
	// 写入zip文件的信息
	ZIP_FILE *m_pZipFile;

//////////////////////////////////////////////////////////////////////////
	// 序列使用参数
	RECT m_rctXuLieDraw;

//////////////////////////////////////////////////////////////////////////
	CGifImage *m_pGifImg;
	int m_nGifCurFrameTime;
	int m_nGifTimeCtns;

	bool m_bIsTimerDrawEnd;
};
