//4X4������
#ifndef _MATRIX4X4MGR_H_
#define _MATRIX4X4MGR_H_

class CMatrix4X4Mgr
{
public:

	//��������б�
	void ClearMatrixList();

	//��ӵ������б�(���ھ��󸴺�,����ӵľ������������)
	bool AddToMatrixList(float *pMatrix);

	//�������б��еľ�����˳��ϳ�(�������)����������浽pMatrix
	bool MulMatrixList(float *pMatrix);

	//�����ֵ:mΪm1��m2���ٷֱ�percent(0~1))��������Ĺ��ɾ���
	void CMatrix4X4Mgr::InsertValue(float *m,float *m1,float *m2,float percent);

	//�Ƕ�ת����
	float Angle2Radian(float Angle);

	//����pSrcMatrix���Ƶ�����pDestMatrix
	void Copy(float *pDestMatrix,float *pSrcMatrix);

	//����任(x,y,z)ͨ������pMatrix�任Ϊ(pX,pY,pZ)
	void VertexTransform(float *pMatrix,float x,float y,float z,float *pX,float *pY,float *pZ);

	//�������������
	void SetCameraMatrix(float *pMatrix,
		float x,float y,float z,//�����λ��
		float zRadian,float yRadian,float xRadian//ŷ����
		);

	//������(x,y,z)Ϊ������X����ת����
	void SetEddyXWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//������(x,y,z)Ϊ������Y����ת����
	void SetEddyYWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//������(x,y,z)Ϊ������Z����ת����
	void SetEddyZWithFocus(float *pMatrix,float radian,float x,float y,float z);

	//�������ž���
	void SetZoomMatrix(float *pMatrix,float sx,float sy,float sz);

	//������X����ת����
	void SetEddyXMatrix(float *pMatrix,float radian);

	//������Y����ת����
	void SetEddyYMatrix(float *pMatrix,float radian);

	//������Z����ת����
	void SetEddyZMatrix(float *pMatrix,float radian);

	//����ƽ�ƾ���
	void SetMoveMatrix(float *pMatrix,float dx,float dy,float dz);

	//���õ�λ����(���Խ�����ȫ1)
	void SetIdentityMatrix(float *pMatrix);

	//����͸��ͶӰ����(ԭ��Ϊ�ӵ�,near1Ϊ�����浽ԭ��ľ���,far1ΪԶ���浽ԭ��ľ���)
	void SetPerspectiveMatrix(
		float *pMatrix,
		float near1,
		float far1,
		float left,//ͶӰ����߽�
		float right,//ͶӰ���ұ߽�
		float top,//ͶӰ���ϱ߽�
		float bottom//ͶӰ���±߽�
		);

	//4X4����˷�m=m1*m2;
	void Mul(float *m,float *m1,float *m2);

	CMatrix4X4Mgr();

	~CMatrix4X4Mgr();

	static CMatrix4X4Mgr & GetSingle()
	{
		static CMatrix4X4Mgr Single;
		return Single;
	}

protected:

	//�����б�(����4X4�������еĸ��ϱ任)
#define MATRIX_LIST_MAX_COUNT 1024
	float *m_pMatrixList[MATRIX_LIST_MAX_COUNT];

	//��������
	unsigned long m_uMatrixCount;
};

#endif