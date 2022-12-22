#pragma once
#include "Mallet.h"

//■■シーンを管理するクラス
class Player : public Mallet
{
	XMFLOAT3 mousePos;
	bool isCamera_;		//カメラの視点変更
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//開放
	void Release() override;

	//何かに当たった
	//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;

	//当たっていない
	//引数：pTarget 当たった相手
	void OffCollision(GameObject* pTarget) override;

	//初期化
	void SetInit() override;

	//マレットの動き
	void MoveMallet() override;

	//置く処理
	bool IsPut() override;
	//XMFLOAT3 GetDirection() { return dir_; };

	//XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	//XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };

	//XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousPos_.x,0,previousPos_.z }; };

	//float GetSpeed() { return speed_; }
};