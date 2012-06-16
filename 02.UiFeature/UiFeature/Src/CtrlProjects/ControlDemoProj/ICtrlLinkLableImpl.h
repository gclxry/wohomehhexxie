
#pragma once
#include "..\..\Inc\Control\ICtrlLinkLable.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyFontBase.h"

class ICtrlLinkLableImpl : public ICtrlLinkLable
{
public:
	ICtrlLinkLableImpl();
	virtual ~ICtrlLinkLableImpl();

	// ����Link����
	virtual void SetLinkText(char *pText, bool bRedraw);
	// ����Link���ӵ�ַURL
	virtual void SetLinkUrl(char *pUrl);
	// ȡ��Link���ӵ�ַURL
	virtual const char * GetLinkUrl();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt);

private:
	bool m_bIsLButtonDown;

	IPropertyString* m_pPropLinkText;
	IPropertyString* m_pPropLinkUrl;
	IPropertyCursor* m_pPropCursor;
	IPropertyGroup* m_PropFontGroup;
	IPropertyFont* m_pPropFontNormal;
	IPropertyFont* m_pPropFontHover;
	IPropertyFont* m_pPropFontDown;
};
