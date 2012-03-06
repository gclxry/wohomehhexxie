//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "CUiXmlParser.h"
#include "IFeatureObject.h"
#include "CUiXmlWrite.h"
#include "IPropertyBuilderCtrl.h"

class IPropertyBase;
class IUiFeatureKernel;

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

// string ����
typedef vector<string>									STRING_VEC;

// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY��ObjectId
// һ�ֿؼ������Զ��У��磺Button��CheckBox�ȣ�KEY��ObjectId
// һ�ִ��ڵ����Զ��У�KEY��ObjectId
typedef map<string, IPropertyBase*>						ONE_RESOURCE_PROP_MAP;

// ������������ԵĶ��У�KEY�������������ƣ��磺font
// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
// KEY:ObjectId�����д��ڵĹ�����map
typedef map<string, ONE_RESOURCE_PROP_MAP*>				RESOURCE_PROP_MAP;

class IPropertyBase : public IFeatureObject
{
public:
	IPropertyBase();
	virtual ~IPropertyBase();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	// ������������
	const char* GetRelevancyPropName();
	void SetRelevancyPropName(char *pszPropName);

	// ��������
	IPropertyBase* GetRelevancyProp();
	void SetRelevancyProp(IPropertyBase *pszProp);

	void SetUiKernel(IUiFeatureKernel *pUiKernel);
	IUiFeatureKernel *GetUiKernel();
	
	// ��Builder�н���
	void EnableInBuilder(bool bEnable);
	void SetPropBuilderCtrl(IPropertyBuilderCtrl* pBuilderCtrl);

private:
	IUiFeatureKernel *m_pUiKernel;
	// ������������
	string m_strRelevancyPropName;
	// ��������
	IPropertyBase *m_pRelevancyProp;
	IPropertyBuilderCtrl* m_pBuilderCtrl;
};
