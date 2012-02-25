
#include "StdAfx.h"
#include "MouseStyleList.h"
#include "resource.h"
#include "UiFeatureBuilder.h"
#include "..\..\Inc\UiFeatureDefs.h"

extern CUiFeatureBuilderApp theApp;

CMouseStyleList::CMouseStyleList()
{
	m_pCursorBaseMap = NULL;
	m_pParentCursorProp = NULL;
}

CMouseStyleList::~CMouseStyleList()
{
}

COLORREF CMouseStyleList::OnGetCellBkColor(int nRow, int nColum)
{
	return(nRow % 2) == 0 ? RGB(255, 255, 255) : RGB(255, 255, 255);
}

void CMouseStyleList::OnSelectItem()
{
	if (m_pParentCursorProp == NULL)
		return;

	if (m_nSelectItem < 0)
	{
		// û��ѡ��
		m_pParentCursorProp->SetCursorBaseProp(NULL);
		m_pParentCursorProp->SetRelevancyPropName(NULL);
	}
	else
	{
		IPropertyCursorBase* pCursorBaseProp = (IPropertyCursorBase*)(this->GetItemData(m_nSelectItem));
		m_pParentCursorProp->SetCursorBaseProp(pCursorBaseProp);
		m_pParentCursorProp->SetRelevancyPropName((char*)pCursorBaseProp->GetObjectName());
	}
}

void CMouseStyleList::InitMouseStyleList(IPropertyCursor* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pCursorBaseMap)
{
	m_pParentCursorProp = pParentCursorProp;
	if (pCursorBaseMap == NULL)
		return;

	USES_CONVERSION;
	this->DeleteAllItems();
	m_pCursorBaseMap = pCursorBaseMap;

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("��ʽ"), LVCFMT_LEFT, 35);
	this->InsertColumn(1, _T("����"), LVCFMT_LEFT, 85);
	this->InsertColumn(2, _T("ϵͳ"), LVCFMT_LEFT, 35);
	this->InsertColumn(3, _T("˵��"), LVCFMT_LEFT, 170);

	if (bmp.LoadBitmap(IDB_CURSOR_BITMAP) && m_pCursorBaseMap != NULL)
	{
		BITMAP bmpObj;
		bmp.GetBitmap(&bmpObj);

		UINT nFlags = (ILC_MASK | ((theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4));
		m_CursorImageList.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
		m_CursorImageList.Add(&bmp, RGB(255, 0, 0));

		this->SetImageList(&m_CursorImageList, LVSIL_SMALL);

		int nNo = 0;
		for (ONE_RESOURCE_PROP_MAP::iterator pCursorBaseItem = m_pCursorBaseMap->begin();
			pCursorBaseItem != m_pCursorBaseMap->end(); pCursorBaseItem++)
		{
			IPropertyCursorBase* pCursorBaseProp = dynamic_cast<IPropertyCursorBase*>(pCursorBaseItem->second);
			if (pCursorBaseProp == NULL)
				continue;

			AddCursorInfo(pCursorBaseProp, nNo);
			nNo++;
		}
	}

	if (m_pCursorBaseMap != NULL && m_pParentCursorProp != NULL && m_pParentCursorProp->GetCursorBaseProp() != NULL)
	{
		int nNo = 0;
		for (ONE_RESOURCE_PROP_MAP::iterator pCursorBaseItem = m_pCursorBaseMap->begin();
			pCursorBaseItem != m_pCursorBaseMap->end(); pCursorBaseItem++, nNo++)
		{
			IPropertyCursorBase* pCursorBaseProp = dynamic_cast<IPropertyCursorBase*>(pCursorBaseItem->second);
			if (pCursorBaseProp == NULL)
				continue;

			if (pCursorBaseProp == m_pParentCursorProp->GetCursorBaseProp())
			{
				this->SetItemState(nNo, LVIS_SELECTED, LVIS_SELECTED);
				break;
			}
		}
	}
}

void CMouseStyleList::AddCursorInfo(IPropertyCursorBase* pCursorBaseProp, int nNo)
{
	USES_CONVERSION;
	if (pCursorBaseProp == NULL || nNo < 0)
		return;

	switch (pCursorBaseProp->GetCursorId())
	{
		// ������� ��׼�ļ�ͷ
	case UF_IDC_ARROW:
		this->InsertItem(nNo, _T(""), 0);
		this->SetItemText(nNo, 3, _T("��׼�ļ�ͷ"));
		break;

		// ˫��ͷָ�򶫱�������
	case UF_IDC_SIZENESW:
		this->InsertItem(nNo, _T(""), 1);
		this->SetItemText(nNo, 3, _T("˫��ͷָ�򶫱�������"));
		break;

		// ���ֹ��
	case UF_IDC_IBEAM:
		this->InsertItem(nNo, _T(""), 2);
		this->SetItemText(nNo, 3, _T("���ֹ��"));
		break;

		// ʮ�ּܹ��
	case UF_IDC_CROSS:
		this->InsertItem(nNo, _T(""), 3);
		this->SetItemText(nNo, 3, _T("ʮ�ּܹ��"));
		break;

		// �����ͷָ�򶫡������ϡ���
	case UF_IDC_SIZEALL:
		this->InsertItem(nNo, _T(""), 4);
		this->SetItemText(nNo, 3, _T("�����ͷָ�򶫡������ϡ���"));
		break;

		// ��ֱ��ͷ
	case UF_IDC_UPARROW:
		this->InsertItem(nNo, _T(""), 5);
		this->SetItemText(nNo, 3, _T("��ֱ��ͷ"));
		break;

		// ˫��ͷָ����
	case UF_IDC_SIZEWE:
		this->InsertItem(nNo, _T(""), 6);
		this->SetItemText(nNo, 3, _T("˫��ͷָ����"));
		break;

		// ˫��ͷָ���ϱ�
	case UF_IDC_SIZENS:
		this->InsertItem(nNo, _T(""), 7);
		this->SetItemText(nNo, 3, _T("˫��ͷָ���ϱ�"));
		break;

		// ˫��ͷָ�������Ͷ���
	case UF_IDC_SIZENWSE:
		this->InsertItem(nNo, _T(""), 8);
		this->SetItemText(nNo, 3, _T("˫��ͷָ�������Ͷ���"));
		break;

		// ����
	case UF_IDC_HAND:
		this->InsertItem(nNo, _T(""), 9);
		this->SetItemText(nNo, 3, _T("����"));
		break;

		// ��׼�ļ�ͷ��Сɳ©
	case UF_IDC_APPSTARTING:
		this->InsertItem(nNo, _T(""), 10);
		this->SetItemText(nNo, 3, _T("��׼�ļ�ͷ��Сɳ©"));
		break;

		// ɳ©
	case UF_IDC_WAIT:
		this->InsertItem(nNo, _T(""), 11);
		this->SetItemText(nNo, 3, _T("ɳ©"));
		break;

		// ��׼�ļ�ͷ���ʺ�
	case UF_IDC_HELP:
		this->InsertItem(nNo, _T(""), 12);
		this->SetItemText(nNo, 3, _T("��׼�ļ�ͷ���ʺ�"));
		break;

		// ��ֹȦ
	case UF_IDC_NO:
		this->InsertItem(nNo, _T(""), 13);
		this->SetItemText(nNo, 3, _T("��ֹȦ"));
		break;

	default:
		break;
	}

	this->SetItemText(nNo, 1, A2W(pCursorBaseProp->GetObjectName()));

	if (pCursorBaseProp->IsSystemCursor())
		this->SetItemText(nNo, 2, _T("��"));
	this->SetItemData(nNo, (DWORD_PTR)pCursorBaseProp);
}
