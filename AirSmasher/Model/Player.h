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

	XMFLOAT3 GetDirection() { return dir_; };

	XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	float GetSpeed() { return speed_; }
};