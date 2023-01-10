#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/QuadrangleHit.h"
#include "Stage.h"
#include "Shadow.h"
//#include "Pack.h"

//class Pack;

//■■シーンを管理するクラス
class Mallet : public GameObject
{
	int hModel_;
protected:
	Stage* pStage_;			//ステージのポインタ
	Shadow* pShadow_;			//影のポインタ
	CircleCollider* collision;  //当たり判定
	QuadrangleHit* pQuadrangle;	//当たり判定
	XMFLOAT3 malletDir_;			//向き	
	XMFLOAT3 previousMalletPos_;	//前のマレットの位置
	XMFLOAT2 stageScale_;
	float malletSpeed_;			//マレットの速度
	float malletRadius_;	//半径
	float stageFront_;	//地面の位置
	float packFront_; //パックの位置
	int goalCount_;
	bool first_;
	bool isPut_;			//マレットをテーブルにつけているかどうか
	bool isSuppress_;		//パックを抑えているか
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
	XMFLOAT3 GetDirection() { return XMFLOAT3{ malletDir_.x,0,malletDir_.z }; };

	//マレットの前回の位置
	//戻り値　マレットの前回いた位置
	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousMalletPos_.x,0,previousMalletPos_.z }; };

	//マレットの動いた速度
	//戻り値　マレットの速度
	float GetSpeed() { return malletSpeed_; }

	//マレットが台についているかどうか
	//戻り値　台についているならtrue
	bool GetPut() { return isPut_; };

	//抑えられる状態かどうか
	//戻り値　パックを抑えられるならtrue
	bool GetSuppress() { return isSuppress_; };

	//float GetFront() { return front_; };

	//float GetPackFront() { return packFront_; };

	float GetRadius() { return malletRadius_; };

	void SetSuppress(bool Sup) { isSuppress_ = Sup; };

	void SetGoal() { goalCount_ = 60; };

	/// <summary>
	/// パックに当たったとき後ろに下がる
	/// </summary>
	/// <param name="dir">方向</param>
	void CrashPack(XMFLOAT3 dir);

	//継承したマレットの初期化
	virtual void SetInit() = 0;

	//継承したマレットの動き関係
	virtual void MoveMallet() = 0;

	//マレットを地面についているかどうか
	virtual bool IsPut() = 0;
};