
#pragma once
#include "FetionSFDefs.h"

class CSysUnit
{
public:
	CSysUnit();
	virtual ~CSysUnit();

	// ȡ�õ�ǰexe��Ŀ¼·�������'\'����
	static CString GetAppPath();

	// ���ô��ڵ�͸������
	static void SetWindowToTransparence(HWND hWnd, bool bIsTrans);

private:

};

