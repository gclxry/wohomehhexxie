//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

// ��������
enum AREA_TYPE
{
	AT_NONE	= 0,
	// ���ļ���
	AT_CN		= 1,
	// ���ķ���
	AT_CN_TW	= 2,
	// Ӣ��
	AT_EN		= 3,
	// ����
	AT_JP		= 4,
	// ����
	AT_GE		= 5,
	AT_LAST		= 6
};

class IPropertyString : public IPropertyBase
{
public:
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	// Ĭ����ʾ����
	virtual const char* GetString() = 0;
	virtual void SetString(char* pszString) = 0;
	virtual int GetLength() = 0;

	virtual void SetArea(AREA_TYPE areaType) = 0;
};
