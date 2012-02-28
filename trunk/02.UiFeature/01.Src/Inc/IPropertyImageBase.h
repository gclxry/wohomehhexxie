//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "CDrawingImage.h"
#include "IZipFile.h"

enum IMAGE_SHOW_TYPE
{
	// ƽ��
	IST_PINGPU		= 0,
	// ȫ����
	IST_ALL_LASHEN,
	// �Ź�������
	IST_JGG_LASHEN
};

enum IMAGE_PLAY_TYPE
{
	// ��̬
	IPT_STATIC_IMG		= 0,
	// GIF
	IPT_GIF,
	// ͼƬ����
	IPT_IMAGE_XULIE
};

enum IMAGE_LOOP_TYPE
{
	// ѭ��һ��
	ILT_LOOP_1		= 0,
	// ����ѭ��
	ILT_LOOP
};

enum IMAGE_BOFANG_TYPE
{
	// ���򲥷�
	IBFT_ZHENGXIANG		= 0,
	// ���򲥷�
	IBFT_FANXIANG
};

// ͼƬ����
struct IMAGE_BASE_PROP
{
	// ����ʶ�� strFileName ��������� zipfile��˵���Ǳ���������·��
	bool bIsZipFile;
	// ��ѹ���ļ��е��ļ���
	string strFileName;
	// �Ź��������
	IMAGE_SHOW_TYPE ImgShowType;
	// ͼƬ����
	IMAGE_PLAY_TYPE ImgPlayType;
	// ѭ������
	IMAGE_LOOP_TYPE ImgLoopType;
	// ����/���򲥷�
	IMAGE_BOFANG_TYPE ImgBoFangType;
	RECT RectInImage;
	// �Ź�������
	RECT jggInfo;
	// �Ƿ���ƾŹ����м�����
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

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú����������༭״̬��ʹ�ú���

//////////////////////////////////////////////////////////////////////////
	// ����ʱ̬ʹ�ú���
	void SetImageProp(IMAGE_BASE_PROP* pImgProp);
	IMAGE_BASE_PROP* GetImageProp();

	ZIP_FILE * GetZipFile();
	void SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc);

	// ����ͼƬ�����alpha����255����������alphaֵ������
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);

	bool OnDrawAnimation();

	SIZE GetImageSize();

	// �õ�ͼƬ���ڴ�DC
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
	// ��ʹ�õļ�����
	int m_nUseCtns;
	// д��zip�ļ�����Ϣ
	ZIP_FILE *m_pZipFile;

//////////////////////////////////////////////////////////////////////////
	// ����ʹ�ò���
	RECT m_rctXuLieDraw;

//////////////////////////////////////////////////////////////////////////
	CGifImage *m_pGifImg;
	int m_nGifCurFrameTime;
	int m_nGifTimeCtns;

	bool m_bIsTimerDrawEnd;
};
