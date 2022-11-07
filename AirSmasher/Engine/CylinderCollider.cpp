#include "CylinderCollider.h"

//���a�ƒ��S�̎擾
CylinderCollider::CylinderCollider(XMFLOAT3 center, float radius, float height)
{
	center_ = center;
	radius_ = radius;
	height_ = height;
}

//�R���C�_�[�̔��a
float CylinderCollider::GetRadius()
{
	return radius_;
}

//�R���C�_�[�̒��S
XMFLOAT3 CylinderCollider::GetCenter()
{
	return center_;
}

float CylinderCollider::GetHeight()
{
	return height_;
}
