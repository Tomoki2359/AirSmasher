#include "CircleCollider.h"

//半径と中心の取得
CircleCollider::CircleCollider(XMFLOAT3 center, float radius, float dimension)
{
	center_ = center;
	radius_ = radius;
	dimension_ = dimension;
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

float CircleCollider::GetDimension()
{
	return dimension_;
}

void CircleCollider::SetDimension(float dimension)
{
	dimension_ = dimension;
}
