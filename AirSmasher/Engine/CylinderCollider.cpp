#include "CylinderCollider.h"

//半径と中心の取得
CylinderCollider::CylinderCollider(XMFLOAT3 center, float radius, float height)
{
	center_ = center;
	radius_ = radius;
	height_ = height;
}

//コライダーの半径
float CylinderCollider::GetRadius()
{
	return radius_;
}

//コライダーの中心
XMFLOAT3 CylinderCollider::GetCenter()
{
	return center_;
}

float CylinderCollider::GetHeight()
{
	return height_;
}
