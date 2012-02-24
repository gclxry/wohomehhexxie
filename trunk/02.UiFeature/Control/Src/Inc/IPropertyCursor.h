//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyCursorBase.h"

class IPropertyCursor : public IPropertyBase
{
public:
	IPropertyCursor();
	virtual ~IPropertyCursor();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	const char * GetCursorBaseName();

	// ���������Ϣ
	void SetCursorBaseProp(IPropertyCursorBase *pCursorProp);
	IPropertyCursorBase* GetCursorBaseProp();

};
