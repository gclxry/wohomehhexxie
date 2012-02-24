//////////////////////////////////////////////////////////////////////////
// ����

#pragma once
#include "IPropertyBase.h"

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
	FAL_RIGHT_BOTTOM	= 1,
	// ˮƽ����/��ֱ����
	FAL_MIDDLE		= 2
};

// ��������
struct FONT_PROP
{
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

	// ����������Ϣ
	void SetFontProp(FONT_PROP *pFontProp);
	FONT_PROP* GetFontProp();

private:
	FONT_PROP m_FontProp;
};
