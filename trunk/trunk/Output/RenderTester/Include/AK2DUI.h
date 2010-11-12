#ifndef _AK2DUI_H_
#define _AK2DUI_H_

#include "AKPicDraw.h"

#include "AKList.h"

//UI��ͼ�ṹ(��ʾһ����ͼ)
struct AK_2D_UI_PIC
{
	//��ͼID
	unsigned long uID;

	//λͼ����
	unsigned char *pData;

	//���
	unsigned long uWidth,uHeight;
};

//UI�ؼ�[�¼���ͼ]�ṹ
struct AK_UI_EVENT_UV
{
	//UI�¼�
	unsigned long uEventID;
	
	//��ͼID
	unsigned long uPicID;

	//UI��ͼ�ṹ��ַ
	struct AK_2D_UI_PIC *pUIPic;

	//���Ͻ���ͼ����(u,v)
	long u,v;

	//��ͼ���
	long Width,Height;

	//͸��ɫ
	unsigned char r,g,b;
};

//UI�ؼ��ṹ
struct AK_2D_UI
{
	//UI�ؼ�ID
	unsigned long uID;

	//��UI�ؼ�ID(0��ʾ���ؼ�����Ļ)
	unsigned long uParentID;

	//�ӿؼ��б�(ÿ��Ԫ�ر���һ�� struct AK_2D_UI * ָ��)
	CAKList SonList;

	//�Ƿ���ʾ�ӿؼ��б�
	bool IsDisplaySonList;

	//�Ƿ���ʾ����
	bool IsDisplayMyself;

	//�Ƿ���ʾ����
	bool IsDisplayBack;

	//�Ƿ������϶�
	bool IsAllowMove;

	//�Ƿ�������Ӵ����
	bool IsCheckTouch;

	//UI�ؼ����Ͻ�����(����ڸ��ؼ���)
	float x,y;

	//UI�ؼ����
	unsigned long uWidth;
	unsigned long uHeight;

	//[�¼���ͼ]�б�(ÿ��Ԫ�ذ���һ�� struct AK_UI_EVENT_UV * ָ��)
	CAKList EventPicList;

	//�Ƿ񱻼���(û�������)
	bool IsActivation;

	//UI�¼�
	unsigned long uEventID;

	//UI�ı�����
	char *pStr;

	//UI�ı����ݳ���
	unsigned long uStrLength;

	//UI�ı�����߶�
	int FontHeight;

	//UI�ı���ɫ
	unsigned char r_txt,g_txt,b_txt;

	//�ı��м��
	int RowSpace;

	//�ı��ּ��
	int WordSpace;

	//UI��ɫ
	unsigned char r,g,b;

	//UI͸����(0~255)
	unsigned char uAlpha;

	//��չ����
	void *pAttrib;
};

//AK2D UI�¼��ṹ
struct AK_2DUI_EVENT
{
	//UI��ID(0����û�нӴ�UI)
	unsigned long uID;

	//�¼�ID
	unsigned long uEventID;
#define AK_2DUI_EVENT_NONE         0    //���¼�
#define AK_2DUI_EVENT_LBTN_DOWN    1    //����������
#define AK_2DUI_EVENT_LBTN_DCLK    2    //������˫��
#define AK_2DUI_EVENT_LBTN_UP      3    //����������
#define AK_2DUI_EVENT_RBTN_DOWN    4    //����Ҽ�����
#define AK_2DUI_EVENT_RBTN_DCLK    5    //����Ҽ�˫��
#define AK_2DUI_EVENT_RBTN_UP      6    //����Ҽ�����
#define AK_2DUI_EVENT_MOUSE_MOVE   7    //����ƶ��¼�
#define AK_2DUI_EVENT_MOUSE_OVER   8    //��������ĳ��UI�ķ�Χ
#define AK_2DUI_EVENT_MOUSE_OUT    9    //����뿪��ĳ��UI�ķ�Χ

	//����
	float x,y;
};

//AK2D UI������
class CAK2DUI
{
public:

	//ɾ��UI
	void RemoveUI(struct AK_2D_UI *pUI);

	//����UI����(��UI�ö�)
	void SetUIFocus(struct AK_2D_UI *pUI);

	//����UI��ͼ
	struct AK_2D_UI_PIC * FindUIPic(
		unsigned long uID//UI��ͼID
		);

	//����UI��ͼ
	struct AK_2D_UI_PIC * CreateUIPic(
		unsigned long uID,//UI��ͼID
		unsigned long uWidth,//��ͼ��
		unsigned long uHeight//��ͼ��
		);

	//����UI�¼���ͼUV��Ϣ
	struct AK_UI_EVENT_UV * FindUIEventUV(
	struct AK_2D_UI *pUI,//UI��ַ
		unsigned long uEventID//UI�¼�
		);

	//����UI�¼���ͼUV��Ϣ
	struct AK_UI_EVENT_UV * SetUIEventUV(
	struct AK_2D_UI *pUI,//UI��ַ
		unsigned long uEventID,//UI�¼�
		unsigned long uPicID,//��ͼID
		long u,long v,//���Ͻ���ͼ����
		long Width,long Height,//��ͼ���
		unsigned char r=0,unsigned char g=0,unsigned char b=0//͸��ɫ
		);

	//ɾ����ͼ�б�
	void FreePicList();

	//ɾ������UI�б�
	void FreeUIList(CAKList *pList=NULL);

	//pSonUI����pParentUIΪ��UI(pParentUI==NULLʱ,pSonUI���Ϊ��UI)
	bool Join(struct AK_2D_UI *pParentUI,struct AK_2D_UI *pSonUI);

	//��ʾ��ȾUI
	void DisplayUI(unsigned short uPicDrawID=0,CAKList *pUIList=NULL,struct AK_2D_UI *pParentUI=NULL,float x=0,float y=0);

	//����UI��ɫ
	void SetUIColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b);

	//����UI�ı���ɫ
	void SetTextColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b);

	//����UI�ı�����
	bool SetUITextLength(struct AK_2D_UI *pUI,unsigned long uLength);

	//����UI�ı�
	bool SetUIText(struct AK_2D_UI *pUI,char *pStr);

	//��ȡUI
	struct AK_2D_UI * CAK2DUI::GetUI(unsigned long uID,CAKList *pList=NULL);

	//����UI
	struct AK_2D_UI * CreateUI(
		unsigned long uID,//UI ID
		float x,float y,//UI���Ͻ�����
		unsigned long uWidth,unsigned long uHeight,//UI���
		unsigned long uStatus=0//UI״̬
		);

	CAK2DUI();

	~CAK2DUI();
	
	static CAK2DUI &GetSingle()
	{
		static CAK2DUI single;
		return single;
	}

public:

	////////////////////////////////////////////////////////////////

	//�û���ȡ������Ϣ
	bool GetEvent(struct AK_2DUI_EVENT &event);

	//��ȡһ��������Ϣ����Ԫ��
	struct AK_2DUI_EVENT * GerFreeEvent();

	//������(x,y)�ϱ��Ӵ��������UI;û�з���NULL
	struct AK_2D_UI * TouchNearUI(float x,float y,CAKList *pList=NULL,float xx=0,float yy=0);

	//�������������Ϣ
	void SendLBtnDown(float x,float y);

	//�������˫����Ϣ
	void SendLBtnDClk(float x,float y);

	//�������������Ϣ
	void SendLBtnUp(float x,float y);

	//�����Ҽ�������Ϣ
	void SendRBtnDown(float x,float y);

	//�����Ҽ�˫����Ϣ
	void SendRBtnDClk(float x,float y);

	//�����Ҽ�������Ϣ
	void SendRBtnUp(float x,float y);

	//��������ƶ���Ϣ
	void SendMouseMove(float x,float y);
	
	////////////////////////////////////////////////////////////////

protected:

	//UI��ͼ�б�(ÿ��Ԫ�ر���һ�� struct AK_2D_UI_PIC * ָ��)
	CAKList m_PicList;

	//UI�ؼ��б�(ÿ��Ԫ�ر���һ�� struct AK_2D_UI * ָ��)
	CAKList m_UIList;

	//��ǰ���������UI
	struct AK_2D_UI *m_pOnMouseOverUI;

	//��ǰ��������µ�UI
	struct AK_2D_UI *m_pOnLBtnDownUI;

	//��ǰ��ȡ�����UI
	struct AK_2D_UI *m_pOnFocusUI;

	//��һ������ƶ�ʱ������
	float m_OldX,m_OldY;

#define AK_2DUI_EVENT_MAX_COUNT 1024
	//UI��Ϣ����
	struct AK_2DUI_EVENT m_EventList[AK_2DUI_EVENT_MAX_COUNT];

	//UI��Ϣ����ͷָ��(ָ���б��е�һ����Ϣ)
	unsigned long m_uEventListPointer;

	//UI��Ϣ����
	unsigned long m_uEventCount;

public:
	
	//��Ⱦ��Ļ��������Ͻ�����
	float m_ScrX;
	float m_ScrY;

};

#endif
