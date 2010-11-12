
#pragma once


#define DEF_VERTEX(varName,x,y,z)\
	AK3D_VERTEX varName;\
	varName.xDest=x;\
	varName.yDest=y;\
	varName.zDest=z;

#define DEF_UV(varName,u,v)\
	float varName[2];\
	varName[0]=u;\
	varName[1]=v;
