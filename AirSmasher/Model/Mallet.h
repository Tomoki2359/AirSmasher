#pragma once
#include"../Engine/GameObject.h"
#include "Stage.h"
#include "../QuadrangleHit.h"
#include "Shadow.h"

//■■シーンを管理するクラス
class Mallet : public GameObject
{
	int hModel_;
protected:
	XMFLOAT3 dir_;			//向き	
	XMFLOAT3 previousMalletPos_;	//前のマレットの位置
	float speed_;			//マレットの速度
	bool isPut_;			//マレットをテーブルにつけているかどうか
	Stage* pStage_;			//ステージのポインタ
	Shadow* pShadow_;			//影のポインタ
	SquareBox malletSquar_;	//前回と今の四角形
	float radius_;	//半径

	float front_;

	bool first_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mallet(GameObject* parent);

	Mallet(GameObject* parent, std::string name);

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

	//向きのゲッター
	//戻り値 マレットの移動する方向
	XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };
	
	//マレットの前回の位置
	//戻り値　マレットの前回いた位置
	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousMalletPos_.x,0,previousMalletPos_.z }; };

	//マレットの動いた速度
	//戻り値　マレットの速度
	float GetSpeed() { return speed_; }

	//マレットが台についているかどうか
	//戻り値　台についているならtrue
	bool GetPut() { return isPut_; };

	SquareBox GetSquare() { return malletSquar_; };

	float GetFront() { return front_; };

	//継承したマレットの初期化
	virtual void SetInit() = 0;

	//継承したマレットの動き関係
	virtual void MoveMallet() = 0;

	//マレットを地面についているかどうか
	virtual bool IsPut() = 0;
};