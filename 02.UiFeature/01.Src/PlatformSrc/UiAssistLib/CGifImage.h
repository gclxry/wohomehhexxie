#pragma once
#include "Windows.h"

class CGifImage
{
public:
	CGifImage();
	virtual ~CGifImage();

	// 从一段内存中创建
	bool CreateByMem(BYTE *pImgFileMem, int nLen);
	bool CreateByFile(const char *pszFilePath);

	bool IsAnimatedGIF();
	int GetFrameCounts();
	PropertyItem* GetFrameParam();
	Bitmap* GetImage();
	SIZE GetImageSize();

	int GetCurrentPlayFrame();
	int SetCurrentPlayFrame(int nFrame);

	void Init();
	void Release();

private:
	Bitmap *m_pImg;
	// 帧数
	int m_nFrameCount;
	// 属性
	PropertyItem *m_pPropertyItem;
	int m_nCurFrame;
};
