
#pragma once

#include "BaseCtrlDefs.h"

class CBfRichEdit : public CDirectUiWindow
{
public:
	CBfRichEdit(void);
	virtual ~CBfRichEdit(void);

protected:
	virtual void OnPaint();
};
