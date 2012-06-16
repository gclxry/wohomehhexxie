
#include "StdAfx.h"
#include "ICtrlTabBarImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"

ICtrlTabBarImpl::ICtrlTabBarImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_TAB_BAR);

	m_ButtonVec.clear();
	m_pPropTabButtonCtns = NULL;
}

ICtrlTabBarImpl::~ICtrlTabBarImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlTabBarImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropTabButtonCtns = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "TabButtonCounts", "Tab��ť�������ر�ע�⣺���޸���tab��ť������ʱ��ֻ�����´�Ƥ�����̲�����Ч���޸ĺ�����������Ƥ�����̡�");
	if (bIsNewCtrl)
	{
		// ����Ĭ�ϲ����������Ϣ
		if (m_pPropBase_RcvMouseMsg != NULL)
			m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// ��ʼ���ؼ�
void ICtrlTabBarImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlTabBarImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlTabBarImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlTabBarImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
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

// ȡ��ָ����ľ���λ�ã��������������
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

// �ƶ������ÿؼ�λ��
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

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlTabBarImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	OnCreateSubControl(true);
}

// ���õ�ǰѡ����
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

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlTabBarImpl::OnWindowFinalCreate()
{
	SetCheck(0);
	this->RedrawControl(true);
}
