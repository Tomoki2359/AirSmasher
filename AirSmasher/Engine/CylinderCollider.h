#pragma once
#include "Direct3D.h"

class CylinderCollider
{
	XMFLOAT3 center_;
	float radius_;
	float height_;
public:
	CylinderCollider(XMFLOAT3 center, float radius, float height);
	float GetRadius();			//半径
	XMFLOAT3 GetCenter();		//シェーダの位置
	float GetHeight();			//高さ
};

