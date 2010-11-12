//AK3D ����������
#ifndef _AK3DBONESMGR_H_
#define _AK3DBONESMGR_H_

#include "AK3DStruct.h"
#include "Matrix4X4Mgr.h"

class CAK3DBonesMgr
{
public:

	//��ȡ���ֵ֡
	unsigned long GetMaxFrame();

	//���õ�ǰ������֡�汾(uFrameΪ��ǰ���ŵ�֡��)
	void SetPlayFrame(unsigned long uFrame);

	//���ҹ�������ṹ
	struct AK3D_BONES_CTRL * FindBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones);

	//ɾ������͹���������
	void RemoveBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones);

	//��������֡�б�Ԫ��
	bool CreateBonesTreeListElement(unsigned long uStartFrame);

	//������֡�б�����
	void TaxisBonesTreeFrameList();

	//��������͹�������
	struct AK3D_BONES_CTRL * CreateBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones,float Power);

	//�������й����������þ���,ʹ���������ڶ���ľ�����Ч
	void UpdateBonesTreeMatrix();

	//����֡�б�����(����ʼ֡����С��������)
	void TaxisBonesFrame(struct AK3D_BONES *pBones);

	//ɾ������֡
	void RemoveBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame);

	//���ҹ����ؼ�֡
	struct AK3D_BONES_FRAME * FindBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame);

	//����֡(���й���������һ��uStartFrame����֡)
	bool CreateFrame(unsigned long uStartFrame);

	//ɾ��֡(���й�����ɾ��һ��uStartFrame����֡)
	void RemoveFrame(unsigned long uStartFrame);

	//ɾ������
	void RemoveBones(struct AK3D_BONES *pBones);

	//ɾ�����ù�����
	void RemoveAll();

	//������pBones1�����pBones2�Ĺ�ϵ,
	/*����:
	0=û�����¼���ϵ;
	1=pBones1��pBones2���ϼ�;
	2=pBones2��pBones1���ϼ�;
	3=��������ͬ��;
	*/
	short CheckBones(struct AK3D_BONES *pBones1,struct AK3D_BONES *pBones2);

	//�ӹ���pSonBones���ӵ�������pFatherBones
	bool JoinBones(struct AK3D_BONES *pSonBones,struct AK3D_BONES *pFatherBones);

	//��ȡ���й���ΨһID
	unsigned long GetFreeID();

	//���ҹ���(ͨ��ΨһID)
	struct AK3D_BONES * FindBones(unsigned long uID);

	//���ҹ���(ͨ��Ψһ����)
	struct AK3D_BONES * CAK3DBonesMgr::FindBones(char *pName);

	//��������
	struct AK3D_BONES * CreateBones();

	CAK3DBonesMgr();

	~CAK3DBonesMgr();

public:

	//�������б�
	CAKList m_RootBonesList;

	//������֡�б�(ÿ��Ԫ�ش���һ��֡��)
	CAKList m_BonesTreeFrameList;
};

#endif