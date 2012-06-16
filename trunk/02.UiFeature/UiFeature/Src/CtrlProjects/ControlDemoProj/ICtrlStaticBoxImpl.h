
#pragma once
#include "..\..\Inc\Control\ICtrlStaticBox.h"

class ICtrlStaticBoxImpl : public ICtrlStaticBox
{
public:
	ICtrlStaticBoxImpl();
	virtual ~ICtrlStaticBoxImpl();

	// ���ÿؼ����ı�
	virtual bool SetText(char* pszText);
	virtual bool SetBackgroundImage(CDrawingImage* pBkImg);

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
	void OnPaint(CDrawingBoard &DrawBoard);

private:
	IPropertyImage* m_pPropImage;
	IPropertyFont* m_pPropFont; 
	IPropertyString* m_pPropText;
};
