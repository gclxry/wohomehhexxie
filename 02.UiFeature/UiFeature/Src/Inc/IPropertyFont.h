//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "IPropertyFontBase.h"

class IPropertyFont : public IPropertyBase
{
public:
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	virtual const char * GetFontBaseName() = 0;

	// ����������Ϣ
	virtual void SetFontBaseProp(IPropertyFontBase *pFontProp) = 0;
	virtual IPropertyFontBase* GetFontBaseProp() = 0;

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct) = 0;

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign() = 0;

	// ȡ�û������ֵľ��δ�С
	virtual bool GetTextDrawSize(const char* pszDrawText, SIZE &OutSize) = 0;
};
