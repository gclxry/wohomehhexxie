#pragma once
#include "Windows.h"

class CGifImage
{
public:
	CGifImage();
	virtual ~CGifImage();

	// ��һ���ڴ��д���
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
	// ֡��
	int m_nFrameCount;
	// ����
	PropertyItem *m_pPropertyItem;
	int m_nCurFrame;
};
