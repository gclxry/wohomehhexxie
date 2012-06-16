//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IZipFile.h"
#include "CDrawingImage.h"

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
	char strFileName[MAX_PATH + 1];
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

class IPropertyImageBase : public IPropertyBase
{
public:
	virtual bool GetActivePropetry() = 0;

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú����������༭״̬��ʹ�ú���

//////////////////////////////////////////////////////////////////////////
	// ��������ͼ������ͼ����ⲿҪ�ͷţ����� IPropertySkinManager::DeleteImageBase() ���ɣ�Ҳ�ɲ��ͷţ��ں˻������һ���ͷ�
	virtual IPropertyImageBase* CreateThumbnailImage(SIZE sizeThumbnail) = 0;
	// ����ʱ̬ʹ�ú���
	virtual void SetImageProp(IMAGE_BASE_PROP* pImgProp) = 0;
	virtual IMAGE_BASE_PROP* GetImageProp() = 0;
	virtual ZIP_FILE * GetZipFile() = 0;
	virtual bool SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc) = 0;
	virtual SIZE GetImageSize() = 0;
	// �õ�ͼƬ���ڴ�DC
	virtual CDrawingImage* GetDrawingImage() = 0;
	// ����ͼƬ���ڴ�DC
	virtual CDrawingImage* CreateDrawingImage() = 0;
	// ��ʼ��Image����Image���ص��ڴ棬����Ĭ����û�м���ͼƬ���ݵ�
	virtual void InitImage() = 0;
	// ������������ʱ�����ƶ���
	virtual bool OnDrawAnimation() = 0;
	// ����ʹ�ü���
	virtual void AddUseCounts() = 0;
	// ��������
	virtual void SubtractUseCounts() = 0;
	// ȡ��ʹ�ü���
	virtual int GetUseCounts() = 0;

	// ����ͼƬ�����alpha����255����������alphaֵ������
	virtual bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255) = 0;
	virtual bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255) = 0;
};
