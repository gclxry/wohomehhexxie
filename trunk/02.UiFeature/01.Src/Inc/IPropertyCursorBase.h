//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class IPropertyCursorBase : public IPropertyBase
{
public:
	IPropertyCursorBase();
	virtual ~IPropertyCursorBase();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	// �Ƿ�Ϊϵͳ���
	bool IsSystemCursor();
	// ����ϵͳ���
	void SetSystemCursor(bool bIsSysCursor);
	// ���ù��ID
	void SetCursorId(int nId);

private:
	// �Ƿ���ϵͳĬ�Ϲ��
	bool m_bIsSysCursor;
	// ���ID
	int m_nCursorId;
};
