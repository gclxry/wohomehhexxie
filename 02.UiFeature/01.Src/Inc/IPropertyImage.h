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
	IPropertyImageBase* GetImageBaseProp();
	void SetImageBaseProp(IPropertyImageBase* pNewImgBase);
	const char * GetImageBaseName();
	SIZE GetImageSize();
	void SetNeedRedraw();
	// ��ʼ��Image����Image���ص��ڴ棬����Ĭ����û�м���ͼƬ���ݵ�
	void InitImage();
	// ������������ʱ�����ƶ���
	bool OnDrawAnimation();

	// ����ͼƬ�����alpha����255����������alphaֵ������
	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha = 255);
	bool DrawImage(HDC hDc, RECT DstRct, int nAlpha = 255);
};
