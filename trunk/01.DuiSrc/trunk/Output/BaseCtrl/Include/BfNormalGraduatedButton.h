//////////////////////////////////////////////////////////////////////////
// 

#pragma once
#include "BfGraduatedButton.h"

class CBfNormalGraduatedButton : public CBfGraduatedButton
{
public:
	CBfNormalGraduatedButton(void);
	virtual ~CBfNormalGraduatedButton(void);

protected:
	virtual void DrawGraduatedButton(int nDrawSta);
	virtual void NormalDraw() {};
};
