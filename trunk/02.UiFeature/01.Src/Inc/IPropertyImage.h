//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CMemoryDC.h"
#include "IPropertyImageBase.h"

class IPropertyImage : public IPropertyBase
{
public:
	IPropertyImage();
	virtual ~IPropertyImage();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadResourceXmlProperty(XmlNode* pXmlNode);

//////////////////////////////////////////////////////////////////////////
	// Builderʹ�ú����������༭״̬��ʹ�ú���

//////////////////////////////////////////////////////////////////////////
	// ����ʱ̬ʹ�ú���
	IPropertyImageBase* GetImageBaseProp();
	const char * GetImageBaseName();
	bool DrawImage(CMemoryDC &DstDc, RECT DstRct);

private:
	string m_strImageBaseName;
	IPropertyImageBase *m_pImageBaseProp;
};
