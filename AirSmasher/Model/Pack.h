#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
#include "Player.h"
//■■シーンを管理するクラス
class Pack : public GameObject
{
	int hModel_;
	XMFLOAT3 pos_;
	XMFLOAT3 dir_;
	float speed_;
	Player* pPlayer_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Pack(GameObject* parent);

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

	bool IsWall();
};