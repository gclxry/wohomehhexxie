//4X4矩阵类
#ifndef _MATRIX4X4MGR_H_
#define _MATRIX4X4MGR_H_

class CMatrix4X4Mgr
{
public:

	//清除矩阵列表
	void ClearMatrixList();

	//添加到矩阵列表(用于矩阵复合,先添加的矩阵会首先作用)
	bool AddToMatrixList(float *pMatrix);

	//将矩阵列表中的矩阵按照顺序合成(连续相乘)并将结果保存到pMatrix
	bool MulMatrixList(float *pMatrix);

	//矩阵插值:m为m1和m2按百分比percent(0~1))计算出来的过渡矩阵
	void CMatrix4X4Mgr::InsertValue(float *m,float *m1,float *m2,float percent);

	//角度转弧度
	float Angle2Radian(float Angle);

	//矩阵pSrcMatrix复制到矩阵pDestMatrix
	void Copy(float *pDestMatrix,float *pSrcMatrix);

	//顶点变换(x,y,z)通过矩阵pMatrix变换为(pX,pY,pZ)
	void VertexTransform(float *pMatrix,float x,float y,float z,float *pX,float *pY,float *pZ);

	//设置摄像机矩阵
	void SetCameraMatrix(float *pMatrix,
		float x,float y,float z,//摄像机位置
		float zRadian,float yRadian,float xRadian//欧拉角
		);

	//设置以(x,y,z)为中心绕X轴旋转矩阵
	void SetEddyXWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//设置以(x,y,z)为中心绕Y轴旋转矩阵
	void SetEddyYWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//设置以(x,y,z)为中心绕Z轴旋转矩阵
	void SetEddyZWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//设置缩放矩阵
	void SetZoomMatrix(float *pMatrix,float sx,float sy,float sz);

	//设置绕X轴旋转矩阵
	void SetEddyXMatrix(float *pMatrix,float radian);

	//设置绕Y轴旋转矩阵
	void SetEddyYMatrix(float *pMatrix,float radian);

	//设置绕Z轴旋转矩阵
	void SetEddyZMatrix(float *pMatrix,float radian);

	//设置平移矩阵
	void SetMoveMatrix(float *pMatrix,float dx,float dy,float dz);

	//设置单位矩阵(主对角线上全1)
	void SetIdentityMatrix(float *pMatrix);

	//设置透视投影矩阵(原点为视点,near1为近截面到原点的距离,far1为远截面到原点的距离)
	void SetPerspectiveMatrix(
		float *pMatrix,
		float near1,
		float far1,
		float left,//投影面左边界
		float right,//投影面右边界
		float top,//投影面上边界
		float bottom//投影面下边界
		);

	//4X4矩阵乘法m=m1*m2;
	void Mul(float *m,float *m1,float *m2);

	CMatrix4X4Mgr();

	~CMatrix4X4Mgr();

	static CMatrix4X4Mgr & GetSingle()
	{
		static CMatrix4X4Mgr Single;
		return Single;
	}

protected:

	//矩阵列表(用于4X4矩阵序列的复合变换)
#define MATRIX_LIST_MAX_COUNT 1024
	float *m_pMatrixList[MATRIX_LIST_MAX_COUNT];

	//矩阵数量
	unsigned long m_uMatrixCount;
};

#endif