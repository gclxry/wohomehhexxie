
#include "StdAfx.h"
#include "WindowSubclass.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "IKernelWindowImpl.h"

LRESULT CALLBACK WindowSubProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	SUB_CLASS_WINDOW_MAP* pSubMap = CWindowSubclass::GetInstance()->GetSubclassWindowMap();
	if (pSubMap != NULL)
	{
		SUB_CLASS_WINDOW_MAP::iterator pSubItem = pSubMap->find(hWnd);
		if (pSubItem != pSubMap->end())
		{
			SUBCLASS_FUNCTION SubFun = pSubItem->second;
			if (nMsgId == WM_NCDESTROY)
			{
				// ��ע�������ɾ��
				pSubMap->erase(pSubItem);
				if (SubFun.pOldWndProc != NULL)
					::SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)SubFun.pOldWndProc);

				// �ͷŵ�ǰƤ����Դ�����໯��Դ
				IKernelWindowImpl::GetInstance()->ReleaseFeatureSkin(hWnd);

				// ��Ϣ��Ҫ�������´���
				if (SubFun.pOldWndProc != NULL)
					return ::CallWindowProc(SubFun.pOldWndProc, hWnd, nMsgId, wParam, lParam);
			}
			else
			{
				if (SubFun.pWndBase != NULL)
				{
					bool bPassOn = true;
					LRESULT lpRst = SubFun.pWndBase->WindowProc(nMsgId, wParam, lParam, bPassOn);
					if (bPassOn)
					{
						// ��Ϣ��Ҫ�������´���
						if (SubFun.pOldWndProc != NULL)
							return ::CallWindowProc(SubFun.pOldWndProc, hWnd, nMsgId, wParam, lParam);
					}
					else
					{
						// ��Ϣ���������´��ˣ�ֱ�ӷ���
						return lpRst;
					}
				}
			}
		}
	}

	return ::DefWindowProc(hWnd, nMsgId, wParam, lParam);
}

CWindowSubclass::CWindowSubclass()
{
	m_SubClsWndMap.clear();
}

CWindowSubclass::~CWindowSubclass()
{
}

CWindowSubclass* CWindowSubclass::GetInstance()
{
	static CWindowSubclass _SubclassInstance;
	return &_SubclassInstance;
}

bool CWindowSubclass::SubWindow(HWND hWnd, IWindowBase* pWndBase)
{
	if (!::IsWindow(hWnd) || pWndBase == NULL)
		return false;

	SUB_CLASS_WINDOW_MAP::iterator pSubItem = m_SubClsWndMap.find(hWnd);
	if (pSubItem != m_SubClsWndMap.end())
		return false;

	SUBCLASS_FUNCTION SubFu;
	SubFu.pWndBase = pWndBase;
	SubFu.pOldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)WindowSubProc);
	if (SubFu.pOldWndProc == NULL)
		return false;

	m_SubClsWndMap.insert(pair<HWND, SUBCLASS_FUNCTION>(hWnd, SubFu));
	return true;
}

IWindowBase* CWindowSubclass::FindSubWindow(HWND hWnd)
{
	SUB_CLASS_WINDOW_MAP::iterator pSubItem = m_SubClsWndMap.find(hWnd);
	if (pSubItem == m_SubClsWndMap.end())
		return NULL;

	SUBCLASS_FUNCTION &SubFun = pSubItem->second;
	return SubFun.pWndBase;
}

SUB_CLASS_WINDOW_MAP* CWindowSubclass::GetSubclassWindowMap()
{
	return &m_SubClsWndMap;
}
