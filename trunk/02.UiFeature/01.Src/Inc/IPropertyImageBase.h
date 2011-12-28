//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CMemoryDC.h"

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
	string strZipFile;
	RECT RectInImage;
	JGG_INFO jggInfo;
};

class IPropertyImageBase : public IPropertyBase
{
public:
	IPropertyImageBase();
	virtual ~IPropertyImageBase();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú����������༭״̬��ʹ�ú���

//////////////////////////////////////////////////////////////////////////
	// ����ʱ̬ʹ�ú���
	void SetImageProp(IMAGE_BASE_PROP* pImgProp);
	IMAGE_BASE_PROP* GetImageProp();

	bool DrawImage(CMemoryDC &DstDc, RECT DstRct);

private:
	IMAGE_BASE_PROP m_ImageProp;
};
