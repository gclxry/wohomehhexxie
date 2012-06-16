//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "CUiXmlParser.h"
#include "IFeatureObject.h"
#include "CUiXmlWrite.h"
#include "IPropertyBuilderCtrl.h"
#include "CTList.h"

class IPropertyBase;
class IUiFeatureKernel;


// һ�����ԵĶ��У��磺font��string��image�ȣ�KEY��ObjectId
// һ�ֿؼ������Զ��У��磺Button��CheckBox�ȣ�KEY��ObjectId
// һ�ִ��ڵ����Զ��У�KEY��ObjectId
typedef map<string, IPropertyBase*>						ONE_RESOURCE_PROP_MAP;

// ������������ԵĶ��У�KEY�������������ƣ��磺font
// ���пؼ���������ԵĶ��У�KEY���ؼ��������ƣ��磺Button
// KEY:ObjectId�����д��ڵĹ�����map
typedef map<string, ONE_RESOURCE_PROP_MAP*>				RESOURCE_PROP_MAP;

class IPropertyBase : public IFeatureObject, public ListObj
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
	virtual const char* GetRelevancyPropName();
	virtual void SetRelevancyPropName(char *pszPropName);

	// ��������
	virtual IPropertyBase* GetRelevancyProp();
	virtual void SetRelevancyProp(IPropertyBase *pszProp);

	virtual void SetUiKernel(IUiFeatureKernel *pUiKernel);
	virtual IUiFeatureKernel *GetUiKernel();
	
	// ��Builder�н���
	virtual void EnableInBuilder(bool bEnable);
	virtual bool IsEnableInBuilder();
	virtual void SetPropBuilderCtrl(IPropertyBuilderCtrl* pBuilderCtrl);

protected:
	IUiFeatureKernel *m_pUiKernel;

private:
	// ������������
	char m_strRelevancyPropName[MAX_PATH + 1];
	// ��������
	IPropertyBase *m_pRelevancyProp;
	IPropertyBuilderCtrl* m_pBuilderCtrl;
	bool m_bIsEnableInBuilder;
};
