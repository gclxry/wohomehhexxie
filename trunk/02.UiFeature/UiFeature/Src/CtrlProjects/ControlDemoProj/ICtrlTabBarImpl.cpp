
#include "StdAfx.h"
#include "ICtrlTabBarImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"

ICtrlTabBarImpl::ICtrlTabBarImpl(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_TAB_BAR);

	m_ButtonVec.clear();
	m_pPropTabButtonCtns = NULL;
}

ICtrlTabBarImpl::~ICtrlTabBarImpl(void)
{
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlTabBarImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropTabButtonCtns = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TabButtonCounts", "Tab按钮个数，特别注意：当修改了tab按钮个数的时候，只有重新打开皮肤工程才能生效。修改后请立即重启皮肤工程。");
	if (bIsNewCtrl)
	{
		// 设置默认不接受鼠标信息
		if (m_pPropBase_RcvMouseMsg != NULL)
			m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// 初始化控件
void ICtrlTabBarImpl::OnCreate()
{
}

// 控件初始化完毕
void ICtrlTabBarImpl::OnFinalCreate()
{
}

// 销毁控件
void ICtrlTabBarImpl::OnDestroy()
{
}

// 绘制控件
void ICtrlTabBarImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// 当一个控件包含了其他子控件的时候，系统会发送创建或加载子控件的消息
void ICtrlTabBarImpl::OnCreateSubControl(bool bIsCreate)
{
	if (m_pWindowBase == NULL || m_pPropTabButtonCtns == NULL)
		return;

	m_ButtonVec.clear();
	for (int i = 0; i < m_pPropTabButtonCtns->GetValue(); i++)
	{
		char szName[MAX_PATH];
		memset(szName, 0, MAX_PATH);
		sprintf_s(szName, MAX_PATH, "TabBar_Button_%d", i+1);

		ICtrlButton* pButton = dynamic_cast<ICtrlButton*>(m_pWindowBase->CreateSubControl(dynamic_cast<IControlMessage*>(this), dynamic_cast<IControlBase*>(this), CTRL_NAME_BUTTON, szName, true));
		if (pButton != NULL)
			m_ButtonVec.push_back(pButton);
	}

	OnSize();
}

// 取得指定项的矩形位置，相对于整个窗口
RECT ICtrlTabBarImpl::GetButtonWindowRect(int nBtnNum)
{
	RECT btnRct = {0, 0, 0, 0};
	if (m_pWindowBase == NULL || m_pPropTabButtonCtns == NULL || nBtnNum < 0 || nBtnNum >= (int)m_ButtonVec.size())
		return btnRct;

	ICtrlButton* pButton = m_ButtonVec[nBtnNum];
	if (pButton == NULL)
		return btnRct;

	return pButton->GetWindowRect();
}

// 移动、设置控件位置
void ICtrlTabBarImpl::OnSize()
{
	RECT ClientRct = this->GetWindowRect();
	if (IS_RECT_EMPTY(ClientRct) || (int)m_ButtonVec.size() <= 0)
		return;

	int nW = RECT_WIDTH(ClientRct) / ((int)m_ButtonVec.size());
	int nH = RECT_HEIGHT(ClientRct);

	POINT BeginPt = {ClientRct.left, ClientRct.top};
	for (BUTTON_VEC::iterator pItem = m_ButtonVec.begin(); pItem != m_ButtonVec.end(); pItem++)
	{
		ICtrlButton* pButton = *pItem;
		if (pButton == NULL)
			continue;

		RECT BtnRct;
		SET_RECT_WH(BtnRct, BeginPt.x, BeginPt.y, nW, nH);
		pButton->SetControlLayoutType(CL_L_USER_DEF);
		pButton->SetWindowRect(BtnRct, true);
		BeginPt.x += nW;
	}
}

LRESULT ICtrlTabBarImpl::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL)
		return 0;

	if (nMsgId == CM_BUTTON_UP)
	{
		int nUpBtn = 0, nSetCheckBtn = 0;
		for (BUTTON_VEC::iterator pItem = m_ButtonVec.begin(); pItem != m_ButtonVec.end(); pItem++, nUpBtn++)
		{
			ICtrlButton* pButton = *pItem;
			if (pButton == NULL)
				continue;

			if (pButton->CompareControl(pCtrl))
			{
				pButton->SetCheck(true, false);
				nSetCheckBtn = nUpBtn;
			}
			else
			{
				pButton->SetCheck(false, false);
			}
		}
		this->RedrawControl(true);

		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TABBAR_UP, nSetCheckBtn, NULL);
	}

	return 0;
}

// Builder刷新属性，此函数中只要重新加载控件属性即可
void ICtrlTabBarImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	OnCreateSubControl(true);
}

// 设置当前选中项
void ICtrlTabBarImpl::SetCheck(int nBtnNum)
{
	if (nBtnNum < 0)
		nBtnNum = 0;

	if (nBtnNum >= (int)m_ButtonVec.size())
		nBtnNum = (int)m_ButtonVec.size() - 1;

	int nCheck = 0;
	for (BUTTON_VEC::iterator pItem = m_ButtonVec.begin(); pItem != m_ButtonVec.end(); pItem++, nCheck++)
	{
		ICtrlButton* pButton = *pItem;
		if (pButton == NULL)
			continue;

		pButton->SetCheck((nCheck == nBtnNum), false);
	}
}

// 这个接口会在整个对话框初始化完成的时候调用
// 控件通过派生这个接口，可以在这个接口函数里通过其他控件的名称取得当前对话框里的其他控件。
void ICtrlTabBarImpl::OnWindowFinalCreate()
{
	SetCheck(0);
	this->RedrawControl(true);
}
