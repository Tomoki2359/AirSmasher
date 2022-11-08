#include "CircleCollider.h"

//���a�ƒ��S�̎擾
CircleCollider::CircleCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	radius_ = radius;
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
