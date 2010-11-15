
#include "GifImage.h"

CGifImage::CGifImage(void)
{
	m_pImg = NULL;
	m_nFrameCount = 0;
	m_pPropertyItem = NULL;
}

CGifImage::~CGifImage(void)
{
	Release();
}

void CGifImage::Init()
{
	if (m_pImg != NULL)
	{
		UINT nCount = m_pImg->GetFrameDimensionsCount();
		GUID* pDimensionIDs = new GUID[nCount];

		// �õ���֡�Ķ����б�
		m_pImg->GetFrameDimensionsList(pDimensionIDs, nCount);

		//��ȡ��֡��
		m_nFrameCount = m_pImg->GetFrameCount(&pDimensionIDs[0]);

		// ����ͼ�����������Ŀ PropertyItemEquipMake.
		// ��ȡ����Ŀ�Ĵ�С.
		int nSize = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
		if (nSize > 0)
		{
			// Ϊ������Ŀ����ռ�.
			m_pPropertyItem = (PropertyItem*)malloc(nSize);
			m_pImg->GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);
		}
		delete pDimensionIDs;
	}
}

void CGifImage::Release()
{
	if (m_pPropertyItem != NULL)
	{
		free(m_pPropertyItem);
	}

	m_pImg = NULL;
	m_nFrameCount = 0;
	m_pPropertyItem = NULL;
}
