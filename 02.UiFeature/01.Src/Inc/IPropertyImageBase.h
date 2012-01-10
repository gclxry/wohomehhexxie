//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "CDrawingImage.h"

// �Ź�������
struct JGG_INFO
{
	// �Ź�����߾���
	int nLeftSpace;
	int nRightSpace;
	int nTopSpace;
	int nBottomSpace;
	// �Ź����Ƿ����죬��������ƽ��
	bool bLeftStretch;
	bool bRightStretch;
	bool bTopStretch;
	bool bBottomStretch;
	bool bMiddleStretch;
};

// ͼƬ����
struct IMAGE_BASE_PROP
{
	// ��ѹ���ļ��е��ļ���
	bool bIsZipFile;
	string strFileName;
	RECT RectInImage;
	JGG_INFO jggInfo;
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
