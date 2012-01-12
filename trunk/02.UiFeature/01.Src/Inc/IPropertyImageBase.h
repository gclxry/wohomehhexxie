//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
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

// ͼƬ����
struct IMAGE_BASE_PROP
{
	// ����ʶ�� strFileName ��������� zipfile��˵���Ǳ���������·��
	bool bIsZipFile;
	// ��ѹ���ļ��е��ļ���
	string strFileName;
	IMAGE_SHOW_TYPE ImgShowType;
	RECT RectInImage;
// �Ź�������
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

private:
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct);

private:
	IMAGE_BASE_PROP m_ImageProp;
	CDrawingImage m_DrawImg;
	// ��ʹ�õļ�����
	int m_nUseCtns;
};
