
#pragma once
#include "FetionSF.h"

// ���������εĴ�С
#define DROP_SJ_H								(4)
#define DROP_SJ_W								(7)

#define MSG_TITLE								_T("��ÿƼ�")

// ��������
enum WND_TYPE
{
	// Bar�����������Ӵ���
	DWT_BAR_NORMAL	= 0x00000100,
	// Tool bar
	DWT_BAR_TOOL_BAR,
	// ������
	DWT_BAR_CAPTION,
	// ComboBox��ѡ��ť
	DWT_BAR_COMBO_SELECT_BUTTON,
	// ��ť
	DWT_BUTTON		= 0x00000200,
	// ������ť
	DWT_COMBO_BOX_DROPDOWN_BUTTON,
	// ���䰴ť
	DWT_GRADIENT_BUTTON,
	// ����������ť
	DWT_DROPDOWN_GRADIENT_BUTTON,
	// ��̬�ı���
	DWT_STATIC		= 0x00000400,
	// GIF��ʾ����
	DWT_GIF_STATIC,
	// �����Ӱ�ť
	DWT_LINK_STATIC,
	// ��껬����ť
	DWT_MOUSEMOVE_STATIC,
	// �༭��
	DWT_EDIT		= 0x00000800,
	// ���ı���
	DWT_RICH_EDIT,
	// CheckBox
	DWT_CHECK_BOX	= 0x00001000,
	// ComboBox
	DWT_COMBO_BOX	= 0x00002000,
	// Flash
	DWT_FLASH		= 0x00004000,
};

/// ���������б� ///////////////////////////////////////////////////////////////////////
// �Ƿ�ɼ�
const DWORD DWP_VISABLE							= 0x00000001;
// �Ƿ����
const DWORD DWP_ENABLE							= 0x00000002;
// �Ƿ�ΪĬ�ϴ���
const DWORD DWP_DEFAULTWND						= 0x00000004;
// �Ƿ�ȡ�ý���
const DWORD DWP_FOCUS							= 0x00000008;
// �����Ƿ�����
const DWORD DWP_DESTROY							= 0x00000010;
// �����Ƿ�����˴��������ƶ���Ϣѭ��
const DWORD DWP_ENTERSIZEMOVE					= 0x00000020;
// ����Ƿ���봰��
const DWORD DWP_MOUSEHOVER						= 0x00000040;
// ����Ƿ���
const DWORD DWP_MOUSEDOWN						= 0x00000080;
// �Ƿ�����갴����Ϣ
const DWORD DWP_MSG_MOUSEDOWN					= 0x00000100;
// �Ƿ������˫����Ϣ
const DWORD DWP_MSG_MOUSEDCLICK					= 0x00000200;
// �Ƿ�������ƶ���Ϣ
const DWORD DWP_MSG_MOUSEMOUSE					= 0x00000400;
// �Ƿ��ͻ�ͼ��Ϣ
const DWORD DWP_MSG_PAINT						= 0x00000800;
// HOT ���ڣ���Ҫ���ڰ�ť����toolbar�İ�ť�����º��״̬
const DWORD DWP_HOT_WND							= 0x00001000;


//////////////////////////////////////////////////////////////////////////

class WND_TEXT 
{
public:
	WND_TEXT() :
	OutFormat(StringFormat::GenericTypographic())
	{
		strFontName = _T(""); 
		nFontHeight = 0;
		FStyle = FontStyleRegular;
		TextColor = Color(0, 0, 0);
		TextRectF.X = 0.0;
		TextRectF.Y = 0.0;
		TextRectF.Width = 0.0;
		TextRectF.Height = 0.0;
		strText = _T("");

		OutFormat.SetLineAlignment(StringAlignmentCenter);
	};
	bool IsEmpty() { return strFontName.IsEmpty(); };

	// ������
	CString strFontName;
	// �����
	int nFontHeight;
	// ������ʽ
	FontStyle FStyle;
	// ������ɫ
	Color TextColor;
	// �����ʽ
	StringFormat OutFormat;
	// ���ڵ�����
	CString strText;
	// �������������λ��
	RectF TextRectF;
};
