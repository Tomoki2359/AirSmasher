#pragma once
#include"../Engine/GameObject.h"
#include"Stage.h"
//■■シーンを管理するクラス
class Shadow : public GameObject
{
	int hModel_;
	Stage* pStage_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Shadow(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};