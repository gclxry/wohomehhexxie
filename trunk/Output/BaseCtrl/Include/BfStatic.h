//////////////////////////////////////////////////////////////////////////
// ����MFC CStatic����̬�ı�����

#pragma once
#include "DirectUiWnd.h"

class CBfStatic : public CDirectUiWnd
{
public:
	CBfStatic(void);
	virtual ~CBfStatic(void);

	virtual void OnPaint();

	// �Ƿ���Ʊ���ɫ��Ĭ�ϲ�����
	void SetDrawBkgndColor(bool bIsDraw) { m_bIsDrawBkgndColor = bIsDraw; };
	// ����ͼƬΪԲ�ǵĲ���
	void SetDrawImageWane(int nWaneEllipse = 10)  { m_nWaneEllipse = nWaneEllipse; };
	// ����ȫ������ͼƬ
	void SetFullDrawImage(bool bIsFull) { m_bIsFullDraw = bIsFull; };

protected:
	bool m_bIsDrawBkgndColor;
	bool m_bIsFullDraw;
	int m_nWaneEllipse;
};
