
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

		// 得到子帧的对象列表
		m_pImg->GetFrameDimensionsList(pDimensionIDs, nCount);

		//获取总帧数
		m_nFrameCount = m_pImg->GetFrameCount(&pDimensionIDs[0]);

		// 假设图像具有属性条目 PropertyItemEquipMake.
		// 获取此条目的大小.
		int nSize = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
		if (nSize > 0)
		{
			// 为属性条目分配空间.
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
