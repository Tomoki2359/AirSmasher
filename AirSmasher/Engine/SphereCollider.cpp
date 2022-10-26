#include "SphereCollider.h"

//半径と中心の取得
SphereCollider::SphereCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	radius_ = radius;
}

//コライダーの半径
float SphereCollider::GetRadius()
{
	return radius_;
}

//コライダーの中心
XMFLOAT3 SphereCollider::GetCenter_()
{
	return center_;
}
