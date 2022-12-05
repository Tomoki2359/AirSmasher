#pragma once
#include "Engine/Transform.h"

struct SquareBox		//�������Ă��邩�m�F�p�l�p�`
{
	//�l�p�`�̒��_
	XMFLOAT2 LUPos_;	//����̃|�W�V����
	XMFLOAT2 LDPos_;	//�����̃|�W�V����
	XMFLOAT2 RDPos_;	//�E���̃|�W�V����
	XMFLOAT2 RUPos_;	//�E��̃|�W�V����
};

namespace QuadrangleHit
{
	//�l�p�`����鏈��
	//������	�ʒu;������	�ʒu;	��O����	�l�p�`;	��l����	���a; ��܈���	����
	void CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2,SquareBox* pSquar,float radius,XMFLOAT3 dir);

	bool HitTest(SquareBox s1, SquareBox s2);

	void IsHitLine(XMFLOAT2 l1, XMFLOAT2 l2, XMFLOAT2 l3, XMFLOAT2 l4);
};

