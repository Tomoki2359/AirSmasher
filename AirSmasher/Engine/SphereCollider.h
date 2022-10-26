#pragma once
#include "Direct3D.h"

class SphereCollider
{
	XMFLOAT3 center_;
	float radius_;
public:
	SphereCollider(XMFLOAT3 center, float radius);
	float GetRadius();			//���a
	XMFLOAT3 GetCenter_();		//�V�F�[�_�̈ʒu
};

