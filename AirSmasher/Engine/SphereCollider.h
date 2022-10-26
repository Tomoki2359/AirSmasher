#pragma once
#include "Direct3D.h"

class SphereCollider
{
	XMFLOAT3 center_;
	float radius_;
public:
	SphereCollider(XMFLOAT3 center, float radius);
	float GetRadius();			//半径
	XMFLOAT3 GetCenter_();		//シェーダの位置
};

