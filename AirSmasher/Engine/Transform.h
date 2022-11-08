#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform
{
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列
public:
	Transform* pTransform_; //親のTransform
	XMFLOAT3 position_;	//位置
	XMFLOAT3 rotate_;	//向き
	XMFLOAT3 scale_;	//拡大率

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calclation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();

	//法線変形用行列を取得
	XMMATRIX GetNormalMatrix();

	XMFLOAT3 AddXMFLOAT3(XMFLOAT3 f1,XMFLOAT3 f2);

	XMFLOAT3 SubXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2);
};