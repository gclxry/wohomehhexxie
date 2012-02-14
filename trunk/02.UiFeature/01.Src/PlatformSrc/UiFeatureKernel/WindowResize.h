
#pragma once

class IWindowBaseImpl;
class CWindowResize
{
public:
	CWindowResize();
	~CWindowResize();

	static CWindowResize* GetResizeIns();
	VOID InitResizeInfo(IWindowBaseImpl *pDui, UINT uNcHitTest, int nMaxWidth, int nMaxHeight, int nMinWidth, int nMinHeight);
	VOID UnInit();
	BOOL MoveWindowToRect(RECT &MoveRect);
	BOOL IsInResize();
	UINT GetHitType();

private:
	// ��һ�������Ĵ��ڵĴ�С��λ��
	RECT m_OldRect;
	// ����������
	UINT m_uNcHitTest;
	// ������Ĵ���
	IWindowBaseImpl *m_pDuiDlg;
	// �������ֵ����Сֵ
	int m_nMaxWidth;
	int m_nMaxHeight;
	int m_nMinWidth;
	int m_nMinHeight;
};