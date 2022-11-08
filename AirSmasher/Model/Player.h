#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//■■シーンを管理するクラス
class Player : public GameObject
{
	int hModel_;
	XMFLOAT3 mousePos;
	XMFLOAT3 dir_;
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

	XMFLOAT3 Direction() { return dir_; };
};