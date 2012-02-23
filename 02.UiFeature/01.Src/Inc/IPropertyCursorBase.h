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

	// ����ϵͳ���
	void SetSystemCursor(bool bIsSysCursor);
	// �Ƿ�Ϊϵͳ���
	bool IsSystemCursor();

	// ���ù��ID
	void SetCursorId(int nId);
	// �õ����id
	int GetCursorId();

private:
	// �Ƿ���ϵͳĬ�Ϲ��
	bool m_bIsSysCursor;
	// ���ID
	int m_nCursorId;
};
