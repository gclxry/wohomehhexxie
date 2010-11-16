
#pragma once
#include "FetionSFDefs.h"

class CSysUnit
{
public:
	CSysUnit();
	virtual ~CSysUnit();

	// 取得当前exe的目录路径，最后'\'结束
	static CString GetAppPath();

private:

};

