#pragma once
#include "BaseDlgDefs.h"

class CResImage;

class CGifImage
{
	friend class CResImage;
public:
	CGifImage();
	virtual ~CGifImage();

	bool IsAnimatedGIF() { return (m_pPropertyItem != NULL && m_nFrameCount > 1); };
	int GetFrameCounts() { return m_nFrameCount; };
	PropertyItem *GetFrameParam() { return m_pPropertyItem; };
	Image *GetImage() { return m_pImg; };

private:
	void Init();
	void Release();

private:
	Image *m_pImg;

	// Ö¡Êý
	int m_nFrameCount;
	// ÊôÐÔ
	PropertyItem *m_pPropertyItem;
};
