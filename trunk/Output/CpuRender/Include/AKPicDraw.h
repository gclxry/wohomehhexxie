//AK位图绘制类

#ifndef _AKPICDRAW_H_
#define _AKPICDRAW_H_

#include "AKList.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

class CAKPicDraw
{

public:

	//填充矩形(可设置透明度)
	void FillRectEX(long x1,long y1,long x2,long y2);

	//填充矩形
	void FillRect(long x1,long y1,long x2,long y2);
	
	//普通文本显示
	void TextOut(long x,long y,char *pStr);

	//普通文本显示(输出区域宽RectWidth接受主动换行及自动换行)
	void TextOut(long x,long y,char *pStr,long RectWidth);

	//设置字体高度(FontHeight的单位是:像素,例如:6\8\12\16\24\32...)
	void SetFontHeight(
		int FontHeight,//字体高度
		int RowSpace=2,//字体行间距
		int WordSpace=2//字体间距
		);

	//显示ASCII字符
	void CharOut(long x,long y,char ch);

	//显示ASCII字符(可设置透明度)
	void CharOutEX(long x,long y,char ch);

	//显示汉字(可设置透明度)
	void ChineseOutEX(long x,long y,char *pChinese);

	//显示汉字
	void ChineseOut(long x,long y,char *pChinese);

	//加载默认点阵字体库文件
	bool LoadDefaultFont(char *pASC16_FilePathName,char *pHZK16_FilePathName);

	//设置透明度
	void SetAlpha(unsigned char uAlpha);
	
	//绘制位图
	void DrawBmp(long x,long y,//绘制到(x,y)
		unsigned char *pData,//位图
		long w,long h//位图宽高
		);

	//绘制位图(可以设置透明度0~255)
	void DrawBmpAlpha(long x,long y,
		unsigned char *pData,long w,long h,
		unsigned char uAlpha);

	//绘制位图(不绘制透明色)
	void DrawBmp(long x,long y,//绘制到(x,y)
		unsigned char *pData,//位图
		long w,long h,//位图宽高
		unsigned long uBackColor//透明色
		);

    //
    void CAKPicDraw::DrawBmpEX(long x,long y,
        unsigned char *pData,long w,long h,unsigned long uBackColor,
		bool IsXReverse=false,//动作是否按X轴反向显示
		bool IsYReverse=false//动作是否按Y轴反向显示
		);

	//
	void DrawBmpEXAlpha(long x,long y,
		unsigned char *pData,long w,long h,unsigned long uBackColor,
		bool IsXReverse=false,//动作是否按X轴反向显示
		bool IsYReverse=false//动作是否按Y轴反向显示
		);

	//获取颜色(内存格式)
	unsigned long GetPixel(long x,long y);

    //获取颜色(COLORREF格式)
    unsigned long GetColorRefPixel(long x,long y);

	//颜色(内存格式)比较:true=相同;false=不同;
	bool ColorCmp(unsigned char *pColor1,unsigned char *pColor2);

	//填充(简便)
	void FillEasy(long x,long y);
	
	//填充
	void Fill(long x,long y,
		unsigned long uBakcColor//填充背景颜色,即(x,y)处原来的颜色
		);

	//设置画笔颜色
	void SetPenColor(unsigned long uColor);

	//设置画笔颜色
	void SetPenColor(unsigned char r,unsigned char g,unsigned char b);

	//绘制直线
	void Line(long x1,long y1,long x2,long y2);

	//绘制直线(线宽可选)
	void Line(long x1,long y1,long x2,long y2,
		int LineWidth//线宽
		);

	//绘制直线(线宽可选,透明度可以用SetAlpha()设置)
	void LineEX(long x1, long y1, long x2, long y2,
		int LineWidth//线宽
		);

	//设置当前点
	void MoveTo(long x,long y);

	//从当前点到(x,y)绘制直线
	void LineTo(long x,long y);

	//从当前点到(x,y)绘制直线(线宽可选)
	void LineTo(long x,long y,int LineWidth);

	//从当前点到(x,y)绘制直线(线宽可选,透明度可以用SetAlpha()设置)
	void LineToEX(long x,long y,int LineWidth);

	//绘制点
	void SetPixel(long x,long y);

	//绘制点(透明度可以用SetAlpha()设置)
	void SetPixelEX(long x, long y);

    //获取(x,y)上下左右方像素颜色的平均值,并返回给pColor
    void GetPixel4Dir(long x,long y,unsigned char *pColor);

    //返回颜色数组pColorList的平均颜色值(颜色数量为uCount)
    unsigned long GetColorListAverage(unsigned long *pColorList,unsigned long uCount);
	
	//选择一幅位图(选择后才可以开始画)
	void SelectPic(unsigned char *pData,long Width,long Height);

	//构造函数
	CAKPicDraw();

	//释构函数
	~CAKPicDraw();

	//对象编号数量
#define AK_PIC_DRAW_MAX_COUNT 10

	//CAKPicDraw对象(uID为对象编号:0~AK_PIC_DRAW_MAX_COUNT)
	static CAKPicDraw *GetInst(unsigned short uID=0)
	{
		static CAKPicDraw AKPicDrawList[AK_PIC_DRAW_MAX_COUNT];

		if(uID < AK_PIC_DRAW_MAX_COUNT)
			return &AKPicDrawList[uID];
		else
			return NULL;
	}
    
public:

    //画笔颜色(内存格式)
	unsigned long m_uPenColorMark;

public:

	//位图地址
	unsigned char *m_pData;

	//位图宽高
	long m_Width,m_Height;

	//透明度
	float m_fAlpha;

	//填充时使用的链表
	CAKList m_PixelList;

	//当前点
	long m_CurX,m_CurY;

	////////////////////////////////////////////////////
	//ASCII点阵字体库
	unsigned char *m_pASC16_Data;

	//汉字点阵字体库
	unsigned char *m_pHZK16_Data;

	//字体高度(单位:像素,例如12\16\24\32...)
	int m_FontHeight;

	//字体行间距
	int m_RowSpace;

	//字体间距
	int m_WordSpace;

	//字符宽
	int m_CharWidth;
	
	//汉字宽
	int m_ChineseWidth;
	////////////////////////////////////////////////////

};

#endif