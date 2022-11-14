#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//■■シーンを管理するクラス
class Player : public GameObject
{
	int hModel_;
	XMFLOAT3 mousePos;
	XMFLOAT3 dir_;
	XMFLOAT3 previousPos_;	//前の位置
	float speed_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//何かに当たった
//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;

	//XMFLOAT3 GetDirection() { return dir_; };

	//XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };

	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousPos_.x,0,previousPos_.z }; };

	float GetSpeed() { return speed_; }
};