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
	bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	void SetPictureTextRedrawSign();

private:
	void SetNeedRedraw();
};
