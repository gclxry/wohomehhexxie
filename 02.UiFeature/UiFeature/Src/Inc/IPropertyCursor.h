//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyCursorBase.h"

class IWindowBase;
class IPropertyCursor : public IPropertyBase
{
public:
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual const char * GetCursorBaseName() = 0;

	// ���������Ϣ
	virtual void SetCursorBaseProp(IPropertyCursorBase *pCursorProp) = 0;
	virtual IPropertyCursorBase* GetCursorBaseProp() = 0;
};
