#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3* s1, XMFLOAT3* s2,float* length,XMFLOAT3* pos);

	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3* s1, XMFLOAT3* s2, float* length, XMFLOAT3* pos);

	XMFLOAT3 FacingConversion(XMFLOAT3 myDir, XMFLOAT3 pairDir);

	XMFLOAT3 AddXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2);

	XMFLOAT3 AddXMFLOAT3(XMFLOAT3 f1, float f2);

	XMFLOAT3 SubtractionXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2);

	XMFLOAT3 SubtractionXMFLOAT3(XMFLOAT3 f1, float f2);

	XMFLOAT3 MultiplicationXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2);

	XMFLOAT3 MultiplicationXMFLOAT3(XMFLOAT3 f1, float f2);

	XMFLOAT3 DivisionXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2);

	XMFLOAT3 DivisionXMFLOAT3(XMFLOAT3 f1, float f2);

	XMFLOAT3 GetDisplacement(XMFLOAT3 f1,XMFLOAT3 f2);
};

