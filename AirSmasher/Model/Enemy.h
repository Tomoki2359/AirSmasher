#pragma once
#include "Mallet.h"

//■■シーンを管理するクラス
class Enemy : public Mallet
{
	int countFuture_;
	XMFLOAT3 enemyPosition_;
	bool isPrediction_;
#ifdef _DEBUG
	bool isStopMove;
#endif
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//開放
	void Release() override;

	//何かに当たった
//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;

	void OffCollision(GameObject* pTarget) override;

	void SetInit() override;

	void MoveMallet() override;

	bool IsPut() override;
	
	//向き調整
	void AutoDir();
};