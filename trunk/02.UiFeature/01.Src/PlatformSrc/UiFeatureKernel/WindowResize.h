
#pragma once
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"

class IWindowBaseImpl;
class CWindowResize
{
public:
	CWindowResize();
	~CWindowResize();

	void InitResizeInfo(IWindowBaseImpl *pWndBase, IPropertyBool *pPropBase_Layered,
		IPropertyBool *pPropSize_Enable,
		IPropertyInt *pPropSize_MaxWidth, IPropertyInt *pPropSize_MaxHeight,
		IPropertyInt *pPropSize_MinWidth, IPropertyInt *pPropSize_MinHeight,
		IPropertyBool *pPropStretching_Enable,
		IPropertyInt *pPropStretching_LeftSpace, IPropertyInt *pPropStretching_RightSpace,
		IPropertyInt *pPropStretching_TopSpace, IPropertyInt *pPropStretching_BottomSpace);

	// ����Ƿ��ƶ����˴��ڿ��Խ�����������ı�Ե
	int MouseMoveInWindowFrame(POINT pt);

	bool IsInResize();

	// �ֲ㴰��ģʽ�£����촰�ڲ���
	bool BeginResizeInLayeredWindow();
	bool ResizeInLayeredWindow(RECT &OutOldRect, RECT &OutNewRect);
	void EndResizeInLayeredWindow();

private:
	// ��һ�������Ĵ��ڵĴ�С��λ��
	RECT m_OldRect;
	// ����������
	int m_nNcHitTest;
	// ������Ĵ���
	IWindowBaseImpl *m_pWindowBase;
	// �Ƿ�֧�ֲַ㴰��
	bool m_bSupLayered;

	// stretching-enable
	bool m_bStretching;
	// stretching-leftspace
	int m_nLeftSpace;
	// stretching-rightspace
	int m_nRightSpace;
	// stretching-topspace
	int m_nTopSpace;
	// stretching-bottomspace
	int m_nBottomSpace;

	bool m_bUseSize;
	int m_nMaxWidth;
	int m_nMaxHeight;
	int m_nMinWidth;
	int m_nMinHeight;
};
