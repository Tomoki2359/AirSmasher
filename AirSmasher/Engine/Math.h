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

	XMFLOAT3 SignChange(XMFLOAT3 f1);

	XMFLOAT3 GetDisplacement(XMFLOAT3 f1,XMFLOAT3 f2);

	float GetRadian(XMFLOAT3 f1, XMFLOAT3 f2);

	//整数を取得する関数
	//第一引数 : 対象の値 第二引数 : 求める最小の桁 第三引数 : 求める最大の桁
	int GetDigits(int value, int m, int n);

	//小数点以下の値を取得する関数
	//第一引数 : 対象の値 第二/三引数 小数第m～n位
	float GetFraction(float value, int m, int n);	//情報落ちして一部の値が取得できない
	//小数点以下の指定した桁を整数値で取得する関数
	int GetFraction(float value, int m);

	/// <summary>
	/// 解の公式
	/// </summary>
	/// <param name="p1">位置</param>
	/// <param name="p2">位置</param>
	/// <returns>答え</returns>
	XMFLOAT2 SolutionFormula(float p1, float p2);
};

