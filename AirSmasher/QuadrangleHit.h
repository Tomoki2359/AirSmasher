#pragma once
#include "Engine/Transform.h"

struct SquareBox		//�������Ă��邩�m�F�p�l�p�`
{
	//x ����;y ����;z �E��;w �E��
	XMFLOAT4 xPos_;		//�O��ƍ��̈ʒu�̒ʂ蓹(x���_)
	//x ����;y ����;z �E��;w �E��
	XMFLOAT4 zPos_;		//�O��ƍ��̈ʒu�̒ʂ蓹(z���_)
};

namespace QuadrangleHit
{
	//�l�p�`����鏈��
	//������	�ʒu;������	�ʒu;	��O����	�l�p�`;	��l����	���a; ��܈���	����
	void CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2,SquareBox* pSquar,float radius,XMFLOAT3 dir);

	bool HitTest(SquareBox s1, SquareBox s2);
};

