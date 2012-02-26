//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

class IPropertyFont : public IPropertyBase
{
public:
	IPropertyFont();
	virtual ~IPropertyFont();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	const char * GetFontBaseName();

	// ����������Ϣ
	void SetFontBaseProp(IPropertyFontBase *pFontProp);
	IPropertyFontBase* GetFontBaseProp();

	// ��������
	bool DrawText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);

private:
	void SetNeedRedraw();
};
