//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"
#include "CDrawingBoard.h"

// ������ʾ��ʽ
enum FONT_SHOW_MODE
{
	// ������ʾ��������ʾ��Χĩβ����ʾ...
	FSM_ONE_ROW_NO_POINT	= 0,
	// ������ʾ��������ʾ��Χ��ʾ...
	FSM_ONE_ROW_POINT		= 1,
	// ������ʾ
	FSM_MULTI_ROW			= 2
};

// ����ģʽ
enum FONT_ALIGNING
{
	// ˮƽ����/��ֱ����
	FAL_LEFT_TOP		= 0,
	// ˮƽ����/��ֱ����
	FAL_MIDDLE			= 1,
	// ˮƽ����/��ֱ����
	FAL_RIGHT_BOTTOM	= 2
};

// ������Ч
enum FONT_EFFECT
{
	FE_NONE			= 0x00000000,
	// ��Ӱ����
	FE_SHADOW		= 0x00000001,
	// ģ������
	FE_OBSCURE		= 0x00000002
};

// ��������
struct FONT_PROP
{
	// �Ƿ�ΪͼƬ����
	bool bIsPicText;
	// �Ƿ�Ϊֱ������
	bool bIsZhiLiText;
	// ������Ϣ
	LOGFONTA Font;
	// ������ɫ
	COLORREF FontColor;
	// ��ֱͣ����Ϣ
	FONT_ALIGNING VAligning;
	// ˮƽͣ����Ϣ
	FONT_ALIGNING HAligning;
	// ��ʾ��ʽ
	FONT_SHOW_MODE ShowMode;
	// ������Ч
	UINT FontEffect;
};

class IPropertyFontBase : public IPropertyBase
{
public:
	IPropertyFontBase();
	virtual ~IPropertyFontBase();

	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData();
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode);
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode);

	// ����������Ϣ
	void SetFontProp(FONT_PROP *pFontProp);
	FONT_PROP* GetFontProp();

	// �Ƿ���ָ����Ч
	bool GetEffectState(FONT_EFFECT FontEffect);
	void SetEffect(FONT_EFFECT FontEffect, bool bSet);

	// ��������
	bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	void SetPictureTextRedrawSign();

private:
	// ���Ƶ�ָ���ڴ�DC��
	bool DrawToBoard(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);
	// ������Ӱ���ֵ�ָ���ڴ�DC��
	bool DrawShadowText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);
	// ����ͼƬ����
	bool DrawPictureText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct);

private:
	bool m_bRecreatePicText;
	FONT_PROP m_FontProp;
	// ͼƬ�����ڴ�DC
	CDrawingBoard m_PicTextBorad;
};
