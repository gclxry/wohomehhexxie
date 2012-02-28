//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"
#include "IPropertyImageBase.h"

class IPropertyImage : public IPropertyBase
{
public:
	IPropertyImage();
	virtual ~IPropertyImage();

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
	IPropertyImageBase* GetImageBaseProp();
	void SetImageBaseProp(IPropertyImageBase* pNewImgBase);

	const char * GetImageBaseName();

	SIZE GetImageSize();

	// ����ͼƬ�����alpha����255����������alphaֵ������
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);

	bool OnDrawAnimation();

	void SetNeedRedraw();
};
