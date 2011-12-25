
#pragma once
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IUiEngine.h"

class IControlBaseImpl : public IControlBase
{
public:
	IControlBaseImpl(void);
	virtual ~IControlBaseImpl(void);

	// �ػ�ؼ�
	virtual void RedrawControl(bool bDrawImmediately = true);
	// �ػ�ؼ�������ػ涯����ʱ���е���
	virtual void RedrawControlInAnimationTimer();
	// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
	virtual void SetNeedRedraw(bool bNeedRedraw);
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildCtrlsVec();
	// ȡ������
	virtual IPropertyControlInWindow* GetControlBaseProp();

	// ����Ƿ�Hover
	virtual void SetMouseHover(bool bHover);
	virtual bool IsMousehover();

protected:
	// ���ƿؼ�
	virtual void OnPaint();

private:
	// �����ӿؼ��������Ի�
	virtual void SetChildCtrlToRedraw();
	// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CMemoryDC &WndMemDc);

private:
	// �����ؼ����ڴ�DC
	CMemoryDC m_CtrlMemDc;
	// ���ŵĴ���
	IWindowBase* m_pParentWindowBase;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ��ͼ����
	IUiEngine *m_pUiEngine;
	// �ؼ�����
	IPropertyControlInWindow *m_pCtrlProp;
	// ���Hover״̬
	bool m_bMouseHover;
};
