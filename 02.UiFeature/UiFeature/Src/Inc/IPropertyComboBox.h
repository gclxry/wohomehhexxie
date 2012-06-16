//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

class CPropertyViewCtrl;

// string ����
typedef vector<string>									STRING_VEC;
// ComboBox����
struct COMBOBOX_PROP
{
	int nSelect;
	STRING_VEC DataVec;
};

class IPropertyComboBox : public IPropertyBase
{
	friend class CPropertyViewCtrl;

public:
	virtual void Clear() = 0;
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	// ����ѡ����
	virtual void SetSelectString(char *pszSelString) = 0;
	virtual void SetSelect(int nSel) = 0;
	virtual int GetSelect() = 0;
	virtual int GetDataCounts() = 0;
	// ���б������һ������
	virtual bool AppendString(char *pszString) = 0;

protected:
	virtual COMBOBOX_PROP* GetComboBoxData() = 0;
};
