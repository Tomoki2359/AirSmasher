#include "CircleCollider.h"

//半径と中心の取得
CircleCollider::CircleCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	radius_ = radius;
}

//コライダーの半径
float CircleCollider::GetRadius()
{
	return radius_;
}

//コライダーの中心
XMFLOAT3 CircleCollider::GetCenter()
{
	return center_;
}
