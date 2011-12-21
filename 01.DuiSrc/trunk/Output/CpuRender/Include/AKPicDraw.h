//AKλͼ������

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

	//������(������͸����)
	void FillRectEX(long x1,long y1,long x2,long y2);

	//������
	void FillRect(long x1,long y1,long x2,long y2);
	
	//��ͨ�ı���ʾ
	void TextOut(long x,long y,char *pStr);

	//��ͨ�ı���ʾ(��������RectWidth�����������м��Զ�����)
	void TextOut(long x,long y,char *pStr,long RectWidth);

	//��������߶�(FontHeight�ĵ�λ��:����,����:6\8\12\16\24\32...)
	void SetFontHeight(
		int FontHeight,//����߶�
		int RowSpace=2,//�����м��
		int WordSpace=2//������
		);

	//��ʾASCII�ַ�
	void CharOut(long x,long y,char ch);

	//��ʾASCII�ַ�(������͸����)
	void CharOutEX(long x,long y,char ch);

	//��ʾ����(������͸����)
	void ChineseOutEX(long x,long y,char *pChinese);

	//��ʾ����
	void ChineseOut(long x,long y,char *pChinese);

	//����Ĭ�ϵ���������ļ�
	bool LoadDefaultFont(char *pASC16_FilePathName,char *pHZK16_FilePathName);

	//����͸����
	void SetAlpha(unsigned char uAlpha);
	
	//����λͼ
	void DrawBmp(long x,long y,//���Ƶ�(x,y)
		unsigned char *pData,//λͼ
		long w,long h//λͼ���
		);

	//����λͼ(��������͸����0~255)
	void DrawBmpAlpha(long x,long y,
		unsigned char *pData,long w,long h,
		unsigned char uAlpha);

	//����λͼ(������͸��ɫ)
	void DrawBmp(long x,long y,//���Ƶ�(x,y)
		unsigned char *pData,//λͼ
		long w,long h,//λͼ���
		unsigned long uBackColor//͸��ɫ
		);

    //
    void CAKPicDraw::DrawBmpEX(long x,long y,
        unsigned char *pData,long w,long h,unsigned long uBackColor,
		bool IsXReverse=false,//�����Ƿ�X�ᷴ����ʾ
		bool IsYReverse=false//�����Ƿ�Y�ᷴ����ʾ
		);

	//
	void DrawBmpEXAlpha(long x,long y,
		unsigned char *pData,long w,long h,unsigned long uBackColor,
		bool IsXReverse=false,//�����Ƿ�X�ᷴ����ʾ
		bool IsYReverse=false//�����Ƿ�Y�ᷴ����ʾ
		);

	//��ȡ��ɫ(�ڴ��ʽ)
	unsigned long GetPixel(long x,long y);

    //��ȡ��ɫ(COLORREF��ʽ)
    unsigned long GetColorRefPixel(long x,long y);

	//��ɫ(�ڴ��ʽ)�Ƚ�:true=��ͬ;false=��ͬ;
	bool ColorCmp(unsigned char *pColor1,unsigned char *pColor2);

	//���(���)
	void FillEasy(long x,long y);
	
	//���
	void Fill(long x,long y,
		unsigned long uBakcColor//��䱳����ɫ,��(x,y)��ԭ������ɫ
		);

	//���û�����ɫ
	void SetPenColor(unsigned long uColor);

	//���û�����ɫ
	void SetPenColor(unsigned char r,unsigned char g,unsigned char b);

	//����ֱ��
	void Line(long x1,long y1,long x2,long y2);

	//����ֱ��(�߿��ѡ)
	void Line(long x1,long y1,long x2,long y2,
		int LineWidth//�߿�
		);

	//����ֱ��(�߿��ѡ,͸���ȿ�����SetAlpha()����)
	void LineEX(long x1, long y1, long x2, long y2,
		int LineWidth//�߿�
		);

	//���õ�ǰ��
	void MoveTo(long x,long y);

	//�ӵ�ǰ�㵽(x,y)����ֱ��
	void LineTo(long x,long y);

	//�ӵ�ǰ�㵽(x,y)����ֱ��(�߿��ѡ)
	void LineTo(long x,long y,int LineWidth);

	//�ӵ�ǰ�㵽(x,y)����ֱ��(�߿��ѡ,͸���ȿ�����SetAlpha()����)
	void LineToEX(long x,long y,int LineWidth);

	//���Ƶ�
	void SetPixel(long x,long y);

	//���Ƶ�(͸���ȿ�����SetAlpha()����)
	void SetPixelEX(long x, long y);

    //��ȡ(x,y)�������ҷ�������ɫ��ƽ��ֵ,�����ظ�pColor
    void GetPixel4Dir(long x,long y,unsigned char *pColor);

    //������ɫ����pColorList��ƽ����ɫֵ(��ɫ����ΪuCount)
    unsigned long GetColorListAverage(unsigned long *pColorList,unsigned long uCount);
	
	//ѡ��һ��λͼ(ѡ���ſ��Կ�ʼ��)
	void SelectPic(unsigned char *pData,long Width,long Height);

	//���캯��
	CAKPicDraw();

	//�͹�����
	~CAKPicDraw();

	//����������
#define AK_PIC_DRAW_MAX_COUNT 10

	//CAKPicDraw����(uIDΪ������:0~AK_PIC_DRAW_MAX_COUNT)
	static CAKPicDraw *GetInst(unsigned short uID=0)
	{
		static CAKPicDraw AKPicDrawList[AK_PIC_DRAW_MAX_COUNT];

		if(uID < AK_PIC_DRAW_MAX_COUNT)
			return &AKPicDrawList[uID];
		else
			return NULL;
	}
    
public:

    //������ɫ(�ڴ��ʽ)
	unsigned long m_uPenColorMark;

public:

	//λͼ��ַ
	unsigned char *m_pData;

	//λͼ���
	long m_Width,m_Height;

	//͸����
	float m_fAlpha;

	//���ʱʹ�õ�����
	CAKList m_PixelList;

	//��ǰ��
	long m_CurX,m_CurY;

	////////////////////////////////////////////////////
	//ASCII���������
	unsigned char *m_pASC16_Data;

	//���ֵ��������
	unsigned char *m_pHZK16_Data;

	//����߶�(��λ:����,����12\16\24\32...)
	int m_FontHeight;

	//�����м��
	int m_RowSpace;

	//������
	int m_WordSpace;

	//�ַ���
	int m_CharWidth;
	
	//���ֿ�
	int m_ChineseWidth;
	////////////////////////////////////////////////////

};

#endif