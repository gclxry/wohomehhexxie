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

	bool DrawImage(CDrawingBoard &DstDc, RECT DstRct);
};
