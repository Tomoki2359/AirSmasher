#pragma once
#include "Direct3D.h"

class CircleCollider
{
	XMFLOAT3 center_;
	float radius_;
	float dimension_;
public:
	CircleCollider(XMFLOAT3 center, float radius, float dimension);
	float GetRadius();			//���a
	XMFLOAT3 GetCenter();		//�V�F�[�_�̈ʒu
	float GetDimension();
	void SetDimension(float dimension);		//�R���W���������炷
};

