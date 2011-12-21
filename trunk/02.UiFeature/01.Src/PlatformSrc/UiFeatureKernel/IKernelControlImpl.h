
#pragma once
#include "..\..\Inc\IKernelControl.h"

class IKernelControlImpl : public IKernelControl
{
public:
	IKernelControlImpl(void);
	virtual ~IKernelControlImpl(void);

	static IKernelControl* GetInstance();

};
