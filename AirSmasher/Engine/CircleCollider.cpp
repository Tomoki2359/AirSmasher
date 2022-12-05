#include "CircleCollider.h"

//���a�ƒ��S�̎擾
CircleCollider::CircleCollider(XMFLOAT3 center, float radius, float dimension)
{
	center_ = center;
	radius_ = radius;
	dimension_ = dimension;
}

//�R���C�_�[�̔��a
float CircleCollider::GetRadius()
{
	return radius_;
}

//�R���C�_�[�̒��S
XMFLOAT3 CircleCollider::GetCenter()
{
	return center_;
}

float CircleCollider::GetDimension()
{
	return dimension_;
}

void CircleCollider::SetDimension(float dimension)
{
	dimension_ = dimension;
}
