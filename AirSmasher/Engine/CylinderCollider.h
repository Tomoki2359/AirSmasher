#pragma once
#include "Direct3D.h"

class CylinderCollider
{
	XMFLOAT3 center_;
	float radius_;
	float height_;
public:
	CylinderCollider(XMFLOAT3 center, float radius, float height);
	float GetRadius();			//���a
	XMFLOAT3 GetCenter();		//�V�F�[�_�̈ʒu
	float GetHeight();			//����
};

