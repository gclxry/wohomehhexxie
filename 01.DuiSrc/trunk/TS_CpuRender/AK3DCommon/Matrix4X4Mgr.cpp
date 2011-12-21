#include "stdafx.h"

#include "Matrix4X4Mgr.h"

#include "math.h"

CMatrix4X4Mgr::CMatrix4X4Mgr()
{
	m_uMatrixCount=0;
}

CMatrix4X4Mgr::~CMatrix4X4Mgr()
{
}

void CMatrix4X4Mgr::SetEddyXWithFocus(float *pMatrix,float radian,float x,float y,float z)
{
	float m1[4*4];
	float m2[4*4];

	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m1,-x,-y,-z);
	CMatrix4X4Mgr::GetSingle().SetEddyXMatrix(m2,radian);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
	CMatrix4X4Mgr::GetSingle().Copy(m1,pMatrix);
	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m2,x,y,z);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
}

void CMatrix4X4Mgr::SetEddyYWithFocus(float *pMatrix,float radian,float x,float y,float z)
{
	float m1[4*4];
	float m2[4*4];

	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m1,-x,-y,-z);
	CMatrix4X4Mgr::GetSingle().SetEddyYMatrix(m2,radian);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
	CMatrix4X4Mgr::GetSingle().Copy(m1,pMatrix);
	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m2,x,y,z);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
}

void CMatrix4X4Mgr::SetEddyZWithFocus(float *pMatrix,float radian,float x,float y,float z)
{
	float m1[4*4];
	float m2[4*4];

	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m1,-x,-y,-z);
	CMatrix4X4Mgr::GetSingle().SetEddyZMatrix(m2,radian);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
	CMatrix4X4Mgr::GetSingle().Copy(m1,pMatrix);
	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m2,x,y,z);
	CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m2,m1);
}

void CMatrix4X4Mgr::SetIdentityMatrix(float *pMatrix)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[0]=1;
	pMatrix[5]=1;
	pMatrix[10]=1;
	pMatrix[15]=1;
}

void CMatrix4X4Mgr::SetPerspectiveMatrix(float *pMatrix,float near1,float far1,float left,float right,float top,float bottom)
{
	memset(pMatrix,0,sizeof(float)*4*4);

	/*float a=-((far1+near1)/(far1-near1));
	float b=-(2*far1*near1)/(far1-near1);*/
	float a=far1/(far1-near1);
	float b=near1*far1/(far1-near1);
	pMatrix[0]=2*near1/(right-left);
	pMatrix[5]=2*near1/(top-bottom);
	pMatrix[8]=(left+right)/(left-right);
	pMatrix[9]=(bottom+top)/(bottom-top);
	pMatrix[10]=a;
	pMatrix[11]=1;
	pMatrix[14]=b;
}

void CMatrix4X4Mgr::SetMoveMatrix(float *pMatrix,float dx,float dy,float dz)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[0]=1;
	pMatrix[5]=1;
	pMatrix[10]=1;
	pMatrix[15]=1;
	pMatrix[3]=dx;
	pMatrix[7]=dy;
	pMatrix[11]=dz;
}

void CMatrix4X4Mgr::SetEddyZMatrix(float *pMatrix,float radian)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[10]=1;
	pMatrix[15]=1;
	float c=cos(radian);
	float s=sin(radian);
	pMatrix[0]=c;
	pMatrix[1]=-s;
	pMatrix[4]=s;
	pMatrix[5]=c;
}

void CMatrix4X4Mgr::SetEddyYMatrix(float *pMatrix,float radian)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[5]=1;
	pMatrix[15]=1;
	float c=cos(radian);
	float s=sin(radian);
	pMatrix[0]=c;
	pMatrix[2]=s;
	pMatrix[8]=-s;
	pMatrix[10]=c;
}

void CMatrix4X4Mgr::SetEddyXMatrix(float *pMatrix,float radian)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[0]=1;
	pMatrix[15]=1;
	float c=cos(radian);
	float s=sin(radian);
	pMatrix[5]=c;
	pMatrix[6]=-s;
	pMatrix[9]=s;
	pMatrix[10]=c;
}

void CMatrix4X4Mgr::SetZoomMatrix(float *pMatrix,float sx,float sy,float sz)
{
	memset(pMatrix,0,sizeof(float)*4*4);
	pMatrix[0]=sx;
	pMatrix[5]=sy;
	pMatrix[10]=sz;
	pMatrix[15]=1;
}

void CMatrix4X4Mgr::SetCameraMatrix(float *pMatrix,float x,float y,float z,float zRadian,float yRadian,float xRadian)
{
	float m1[4*4];
	float m2[4*4];
	float m3[4*4];
	float m4[4*4];

	CMatrix4X4Mgr::GetSingle().SetMoveMatrix(m1,-x,-y,-z);
	CMatrix4X4Mgr::GetSingle().SetEddyZMatrix(m2,zRadian);
	CMatrix4X4Mgr::GetSingle().SetEddyYMatrix(m3,yRadian);
	CMatrix4X4Mgr::GetSingle().SetEddyXMatrix(m4,xRadian);
	
	CMatrix4X4Mgr::GetSingle().ClearMatrixList();
	CMatrix4X4Mgr::GetSingle().AddToMatrixList(m1);
	CMatrix4X4Mgr::GetSingle().AddToMatrixList(m2);
	CMatrix4X4Mgr::GetSingle().AddToMatrixList(m3);
	CMatrix4X4Mgr::GetSingle().AddToMatrixList(m4);
	CMatrix4X4Mgr::GetSingle().MulMatrixList(pMatrix);
}

void CMatrix4X4Mgr::Mul(float *m,float *m1,float *m2)
{
	m[0]=m1[0]*m2[0]+m1[1]*m2[4]+m1[2]*m2[8]+m1[3]*m2[12];
	m[1]=m1[0]*m2[1]+m1[1]*m2[5]+m1[2]*m2[9]+m1[3]*m2[13];
	m[2]=m1[0]*m2[2]+m1[1]*m2[6]+m1[2]*m2[10]+m1[3]*m2[14];
	m[3]=m1[0]*m2[3]+m1[1]*m2[7]+m1[2]*m2[11]+m1[3]*m2[15];
	m[4]=m1[4]*m2[0]+m1[5]*m2[4]+m1[6]*m2[8]+m1[7]*m2[12];
	m[5]=m1[4]*m2[1]+m1[5]*m2[5]+m1[6]*m2[9]+m1[7]*m2[13];
	m[6]=m1[4]*m2[2]+m1[5]*m2[6]+m1[6]*m2[10]+m1[7]*m2[14];
	m[7]=m1[4]*m2[3]+m1[5]*m2[7]+m1[6]*m2[11]+m1[7]*m2[15];
	m[8]=m1[8]*m2[0]+m1[9]*m2[4]+m1[10]*m2[8]+m1[11]*m2[12];
	m[9]=m1[8]*m2[1]+m1[9]*m2[5]+m1[10]*m2[9]+m1[11]*m2[13];
	m[10]=m1[8]*m2[2]+m1[9]*m2[6]+m1[10]*m2[10]+m1[11]*m2[14];
	m[11]=m1[8]*m2[3]+m1[9]*m2[7]+m1[10]*m2[11]+m1[11]*m2[15];
	m[12]=m1[12]*m2[0]+m1[13]*m2[4]+m1[14]*m2[8]+m1[15]*m2[12];
	m[13]=m1[12]*m2[1]+m1[13]*m2[5]+m1[14]*m2[9]+m1[15]*m2[13];
	m[14]=m1[12]*m2[2]+m1[13]*m2[6]+m1[14]*m2[10]+m1[15]*m2[14];
	m[15]=m1[12]*m2[3]+m1[13]*m2[7]+m1[14]*m2[11]+m1[15]*m2[15];
}

void CMatrix4X4Mgr::VertexTransform(float *pMatrix,float x,float y,float z,float *pX,float *pY,float *pZ)
{
	*pX=pMatrix[0]*x+pMatrix[1]*y+pMatrix[2]*z+pMatrix[3];
	*pY=pMatrix[4]*x+pMatrix[5]*y+pMatrix[6]*z+pMatrix[7];
	*pZ=pMatrix[8]*x+pMatrix[9]*y+pMatrix[10]*z+pMatrix[11];

	//计算齐次坐标第4项参数
	float para=pMatrix[12]*x+pMatrix[13]*y+pMatrix[14]*z+pMatrix[15];

	//如果参数不为1则需要对坐标进行规格化
	if(para!=1&&para!=0)
	{
		*pX/=para;
		*pY/=para;
		*pZ/=para;
	}
}

void CMatrix4X4Mgr::Copy(float *pDestMatrix,float *pSrcMatrix)
{
	memcpy(pDestMatrix,pSrcMatrix,sizeof(float)*4*4);
}

float CMatrix4X4Mgr::Angle2Radian(float Angle)
{
	return(3.1415f/180*Angle);
}

void CMatrix4X4Mgr::InsertValue(float *m,float *m1,float *m2,float percent)
{
	if(percent==0)Copy(m,m1);
	else
	{
		if(percent==1)Copy(m,m2);
		else
		{
			m[0]=m1[0]+(m2[0]-m1[0])*percent;
			m[1]=m1[1]+(m2[1]-m1[1])*percent;
			m[2]=m1[2]+(m2[2]-m1[2])*percent;
			m[3]=m1[3]+(m2[3]-m1[3])*percent;
			m[4]=m1[4]+(m2[4]-m1[4])*percent;
			m[5]=m1[5]+(m2[5]-m1[5])*percent;
			m[6]=m1[6]+(m2[6]-m1[6])*percent;
			m[7]=m1[7]+(m2[7]-m1[7])*percent;
			m[8]=m1[8]+(m2[8]-m1[8])*percent;
			m[9]=m1[9]+(m2[9]-m1[9])*percent;
			m[10]=m1[10]+(m2[10]-m1[10])*percent;
			m[11]=m1[11]+(m2[11]-m1[11])*percent;
			m[12]=m1[12]+(m2[12]-m1[12])*percent;
			m[13]=m1[13]+(m2[13]-m1[13])*percent;
			m[14]=m1[14]+(m2[14]-m1[14])*percent;
			m[15]=m1[15]+(m2[15]-m1[15])*percent;
		}
	}
}

void CMatrix4X4Mgr::ClearMatrixList()
{
	m_uMatrixCount=0;
}

bool CMatrix4X4Mgr::AddToMatrixList(float *pMatrix)
{
	if(m_uMatrixCount>=MATRIX_LIST_MAX_COUNT)return false;
	m_pMatrixList[m_uMatrixCount]=pMatrix;
	++m_uMatrixCount;
	return true;
}

bool CMatrix4X4Mgr::MulMatrixList(float *pMatrix)
{
	//矩阵列表空
	if(m_uMatrixCount<=0)return false;

	//矩阵列表中只有一个矩阵
	if(m_uMatrixCount==1)
	{
		CMatrix4X4Mgr::GetSingle().Copy(pMatrix,m_pMatrixList[0]);
		return true;
	}

	float m[4*4];

	CMatrix4X4Mgr::GetSingle().Copy(m,m_pMatrixList[0]);

	//矩阵合成(连续相乘)
	unsigned long i;
	for(i=1;i<m_uMatrixCount;++i)
	{
		CMatrix4X4Mgr::GetSingle().Mul(pMatrix,m_pMatrixList[i],m);
		CMatrix4X4Mgr::GetSingle().Copy(m,pMatrix);
	}

	return true;
}