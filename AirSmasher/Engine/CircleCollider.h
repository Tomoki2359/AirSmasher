#pragma once
#include "Direct3D.h"

class CircleCollider
{
	XMFLOAT3 center_;
	float radius_;
public:
	CircleCollider(XMFLOAT3 center, float radius);
	float GetRadius();			//半径
	XMFLOAT3 GetCenter();		//シェーダの位置
};

