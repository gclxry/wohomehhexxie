#ifndef _AK2DUI_H_
#define _AK2DUI_H_

#include "AKPicDraw.h"

#include "AKList.h"

//UI贴图结构(表示一张贴图)
struct AK_2D_UI_PIC
{
	//贴图ID
	unsigned long uID;

	//位图数据
	unsigned char *pData;

	//宽高
	unsigned long uWidth,uHeight;
};

//UI控件[事件贴图]结构
struct AK_UI_EVENT_UV
{
	//UI事件
	unsigned long uEventID;
	
	//贴图ID
	unsigned long uPicID;

	//UI贴图结构地址
	struct AK_2D_UI_PIC *pUIPic;

	//左上角贴图坐标(u,v)
	long u,v;

	//贴图宽高
	long Width,Height;

	//透明色
	unsigned char r,g,b;
};

//UI控件结构
struct AK_2D_UI
{
	//UI控件ID
	unsigned long uID;

	//父UI控件ID(0表示父控件是屏幕)
	unsigned long uParentID;

	//子控件列表(每个元素保存一个 struct AK_2D_UI * 指针)
	CAKList SonList;

	//是否显示子控件列表
	bool IsDisplaySonList;

	//是否显示本身
	bool IsDisplayMyself;

	//是否显示背景
	bool IsDisplayBack;

	//是否允许被拖动
	bool IsAllowMove;

	//是否接受鼠标接触检查
	bool IsCheckTouch;

	//UI控件左上角坐标(相对于父控件的)
	float x,y;

	//UI控件宽高
	unsigned long uWidth;
	unsigned long uHeight;

	//[事件贴图]列表(每个元素包含一个 struct AK_UI_EVENT_UV * 指针)
	CAKList EventPicList;

	//是否被激活(没激活会变灰)
	bool IsActivation;

	//UI事件
	unsigned long uEventID;

	//UI文本内容
	char *pStr;

	//UI文本内容长度
	unsigned long uStrLength;

	//UI文本字体高度
	int FontHeight;

	//UI文本颜色
	unsigned char r_txt,g_txt,b_txt;

	//文本行间距
	int RowSpace;

	//文本字间距
	int WordSpace;

	//UI颜色
	unsigned char r,g,b;

	//UI透明度(0~255)
	unsigned char uAlpha;

	//扩展属性
	void *pAttrib;
};

//AK2D UI事件结构
struct AK_2DUI_EVENT
{
	//UI的ID(0代表没有接触UI)
	unsigned long uID;

	//事件ID
	unsigned long uEventID;
#define AK_2DUI_EVENT_NONE         0    //无事件
#define AK_2DUI_EVENT_LBTN_DOWN    1    //鼠标左键按下
#define AK_2DUI_EVENT_LBTN_DCLK    2    //鼠标左键双击
#define AK_2DUI_EVENT_LBTN_UP      3    //鼠标左键弹起
#define AK_2DUI_EVENT_RBTN_DOWN    4    //鼠标右键按下
#define AK_2DUI_EVENT_RBTN_DCLK    5    //鼠标右键双击
#define AK_2DUI_EVENT_RBTN_UP      6    //鼠标右键弹起
#define AK_2DUI_EVENT_MOUSE_MOVE   7    //鼠标移动事件
#define AK_2DUI_EVENT_MOUSE_OVER   8    //鼠标进入了某个UI的范围
#define AK_2DUI_EVENT_MOUSE_OUT    9    //鼠标离开了某个UI的范围

	//坐标
	float x,y;
};

//AK2D UI管理类
class CAK2DUI
{
public:

	//删除UI
	void RemoveUI(struct AK_2D_UI *pUI);

	//设置UI焦点(把UI置顶)
	void SetUIFocus(struct AK_2D_UI *pUI);

	//查找UI贴图
	struct AK_2D_UI_PIC * FindUIPic(
		unsigned long uID//UI贴图ID
		);

	//创建UI贴图
	struct AK_2D_UI_PIC * CreateUIPic(
		unsigned long uID,//UI贴图ID
		unsigned long uWidth,//贴图宽
		unsigned long uHeight//贴图高
		);

	//查找UI事件贴图UV信息
	struct AK_UI_EVENT_UV * FindUIEventUV(
	struct AK_2D_UI *pUI,//UI地址
		unsigned long uEventID//UI事件
		);

	//设置UI事件贴图UV信息
	struct AK_UI_EVENT_UV * SetUIEventUV(
	struct AK_2D_UI *pUI,//UI地址
		unsigned long uEventID,//UI事件
		unsigned long uPicID,//贴图ID
		long u,long v,//左上角贴图坐标
		long Width,long Height,//贴图宽高
		unsigned char r=0,unsigned char g=0,unsigned char b=0//透明色
		);

	//删除贴图列表
	void FreePicList();

	//删除整个UI列表
	void FreeUIList(CAKList *pList=NULL);

	//pSonUI捆绑pParentUI为父UI(pParentUI==NULL时,pSonUI变更为根UI)
	bool Join(struct AK_2D_UI *pParentUI,struct AK_2D_UI *pSonUI);

	//显示渲染UI
	void DisplayUI(unsigned short uPicDrawID=0,CAKList *pUIList=NULL,struct AK_2D_UI *pParentUI=NULL,float x=0,float y=0);

	//设置UI颜色
	void SetUIColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b);

	//设置UI文本颜色
	void SetTextColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b);

	//设置UI文本长度
	bool SetUITextLength(struct AK_2D_UI *pUI,unsigned long uLength);

	//设置UI文本
	bool SetUIText(struct AK_2D_UI *pUI,char *pStr);

	//获取UI
	struct AK_2D_UI * CAK2DUI::GetUI(unsigned long uID,CAKList *pList=NULL);

	//创建UI
	struct AK_2D_UI * CreateUI(
		unsigned long uID,//UI ID
		float x,float y,//UI左上角坐标
		unsigned long uWidth,unsigned long uHeight,//UI宽高
		unsigned long uStatus=0//UI状态
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

	//用户获取队列消息
	bool GetEvent(struct AK_2DUI_EVENT &event);

	//获取一个空闲消息队列元素
	struct AK_2DUI_EVENT * GerFreeEvent();

	//返回在(x,y)上被接触且最近的UI;没有返回NULL
	struct AK_2D_UI * TouchNearUI(float x,float y,CAKList *pList=NULL,float xx=0,float yy=0);

	//产生左键按下消息
	void SendLBtnDown(float x,float y);

	//产生左键双击消息
	void SendLBtnDClk(float x,float y);

	//产生左键弹起消息
	void SendLBtnUp(float x,float y);

	//产生右键按下消息
	void SendRBtnDown(float x,float y);

	//产生右键双击消息
	void SendRBtnDClk(float x,float y);

	//产生右键弹起消息
	void SendRBtnUp(float x,float y);

	//产生鼠标移动消息
	void SendMouseMove(float x,float y);
	
	////////////////////////////////////////////////////////////////

protected:

	//UI贴图列表(每个元素保存一个 struct AK_2D_UI_PIC * 指针)
	CAKList m_PicList;

	//UI控件列表(每个元素保存一个 struct AK_2D_UI * 指针)
	CAKList m_UIList;

	//当前被鼠标进入的UI
	struct AK_2D_UI *m_pOnMouseOverUI;

	//当前被左键按下的UI
	struct AK_2D_UI *m_pOnLBtnDownUI;

	//当前获取焦点的UI
	struct AK_2D_UI *m_pOnFocusUI;

	//上一次鼠标移动时的坐标
	float m_OldX,m_OldY;

#define AK_2DUI_EVENT_MAX_COUNT 1024
	//UI消息队列
	struct AK_2DUI_EVENT m_EventList[AK_2DUI_EVENT_MAX_COUNT];

	//UI消息队列头指针(指向列表中第一条消息)
	unsigned long m_uEventListPointer;

	//UI消息数量
	unsigned long m_uEventCount;

public:
	
	//渲染屏幕缓冲的左上角坐标
	float m_ScrX;
	float m_ScrY;

};

#endif
