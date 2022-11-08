#pragma once
#include "Direct3D.h"

class CircleCollider
{
	XMFLOAT3 center_;
	float radius_;
public:
	CircleCollider(XMFLOAT3 center, float radius);
	float GetRadius();			//���a
	XMFLOAT3 GetCenter();		//�V�F�[�_�̈ʒu
};

