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
	// �Ƿ�Ϊ�Ϸ�����
	virtual bool IsRightData() = 0;
	// ��XML�ڵ��ȡ����ֵ�����������Զ���
	virtual bool ReadPropertyFromXmlNode(XmlNode* pXmlNode) = 0;
	// д��xml
	virtual bool AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode) = 0;

	// ����������Ϣ
	virtual void SetFontProp(FONT_PROP *pFontProp) = 0;
	virtual FONT_PROP* GetFontProp() = 0;

	// �Ƿ���ָ����Ч
	virtual bool GetEffectState(FONT_EFFECT FontEffect) = 0;
	virtual void SetEffect(FONT_EFFECT FontEffect, bool bSet) = 0;

	// ��������
	virtual bool DrawFontText(CDrawingBoard &DstDc, char *pszOutText, RECT DstRct) = 0;

	// ����ͼƬ�����ػ��־��������ɺ󣬽����´λ��Ƶ�ʱ�����´���ͼƬ����
	virtual void SetPictureTextRedrawSign() = 0;

	// ����һ��FontBase��¡
	virtual bool Clone(IPropertyFontBase* pFontBase) = 0;

	// ȡ�û������ֵľ��δ�С
	virtual bool GetTextDrawSize(const char* pszDrawText, SIZE &OutSize) = 0;
};
