//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyImageBase.h"
#include "CDrawingBoard.h"


class IPropertyImage : public IPropertyBase
{
public:
	virtual void SetActivePropetry(bool bIsActive) = 0;
	virtual bool GetActivePropetry() = 0;

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

//////////////////////////////////////////////////////////////////////////
	// ��������ͼ������ͼ����ⲿҪ�ͷţ����� IPropertySkinManager::DeleteImageBase() ���ɣ�Ҳ�ɲ��ͷţ��ں˻������һ���ͷ�
	virtual IPropertyImageBase* CreateThumbnailImage(SIZE sizeThumbnail) = 0;
	virtual IPropertyImageBase* GetImageBaseProp() = 0;
	virtual void SetImageBaseProp(IPropertyImageBase* pNewImgBase) = 0;
	virtual const char * GetImageBaseName() = 0;
	virtual SIZE GetImageSize() = 0;
	virtual void SetImageProp(IMAGE_BASE_PROP* pImgProp) = 0;
	virtual IMAGE_BASE_PROP* GetImageProp() = 0;
	// �õ�ͼƬ���ڴ�DC
	virtual CDrawingImage* GetDrawingImage() = 0;
	// ����ͼƬ���ڴ�DC
	virtual CDrawingImage* CreateDrawingImage() = 0;
	virtual void SetNeedRedraw() = 0;
	// ��ʼ��Image����Image���ص��ڴ棬����Ĭ����û�м���ͼƬ���ݵ�
	virtual void InitImage() = 0;
	// ������������ʱ�����ƶ���
	virtual bool OnDrawAnimation() = 0;

	// ����ͼƬ�����alpha����255����������alphaֵ������
	virtual bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255) = 0;
	virtual bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255) = 0;
};
