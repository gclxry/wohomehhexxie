
#pragma once

class IWindowBaseImpl;
class CWindowResize
{
public:
	CWindowResize();
	~CWindowResize();

	VOID InitResizeInfo(IWindowBaseImpl *pWndBase, UINT uNcHitTest, int nMaxWidth, int nMaxHeight, int nMinWidth, int nMinHeight);
	VOID UnInit();
	bool MoveWindowToRect(RECT &MoveRect);
	bool IsInResize();
	UINT GetHitType();

private:
	// ��һ�������Ĵ��ڵĴ�С��λ��
	RECT m_OldRect;
	// ����������
	UINT m_uNcHitTest;
	// ������Ĵ���
	IWindowBaseImpl *m_pWindowBase;
	// �������ֵ����Сֵ
	int m_nMaxWidth;
	int m_nMaxHeight;
	int m_nMinWidth;
	int m_nMinHeight;
};
