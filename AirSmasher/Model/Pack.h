#pragma once
#include"../Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
//■■シーンを管理するクラス
class Pack : public GameObject
{
	int hModel_;
	XMFLOAT3 pos_;
	XMFLOAT3 dir_;
	float speed_;
	Player* pPlayer_;
	Enemy* pEnemy_;
	Stage* pStage;
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

	//マレットに当たっている処理
	void IsMallet(Mallet* pMallet);

	//壁に当たっている処理
	void IsWall();
	
	//ゴールしている処理
	void IsGoal();

	//モデル番号
	int HandleModelPack() { return hModel_; };
};