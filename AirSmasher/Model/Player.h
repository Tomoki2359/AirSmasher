#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
#include "Mallet.h"
//■■シーンを管理するクラス
class Player : public Mallet 
{
	//int hModel_;
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
};