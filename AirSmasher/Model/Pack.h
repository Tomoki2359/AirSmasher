#pragma once
#include"../Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "../Engine/QuadrangleHit.h"
#include "../Image/GoalPoint.h"

//■■シーンを管理するクラス
class Pack : public GameObject
{
	//ポインタ
	Player* pPlayer_;
	Enemy* pEnemy_;
	Stage* pStage;
	GoalPoint* pGoal_;
	CircleCollider* collision;		//当たり判定
	QuadrangleHit* pQuadrangle;	//当たり判定

	//XMFLOAT3 pos_;
	XMFLOAT3 previousPackPos_;	//前のパックの位置
	XMFLOAT3 packDir_;	//向き	
	float packSpeed_;	//速度
	float packRadius_;	//半径
	int hModel_;
	bool isGool_;	//ゴールしたか
	bool ismallet_;	//プレイヤーはtrue
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

	//壁に当たっているか処理
	void IsWall();

	//ゴールしているか処理
	bool IsGoal();

	float GetRadius() { return packRadius_; };

	float GetSpeed() { return packSpeed_; };

	XMFLOAT3 GetDirection() { return XMFLOAT3{ packDir_.x,0,packDir_.z }; };

	//マレットに当たっているか処理
	//void IsMallet();

	//モデル番号
	int HandleModelPack() { return hModel_; };
};