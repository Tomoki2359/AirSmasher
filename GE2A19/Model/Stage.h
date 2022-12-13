#pragma once
#include"../Engine/GameObject.h"
//■■シーンを管理するクラス
class Stage : public GameObject
{
	int hModel_;
	const float scaleX_;
	const float scaleZ_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//モデル番号
	int HandleModelStage() { return hModel_; };

	float GetScaleX() { return scaleX_; };

	float GetScaleZ() { return scaleZ_; };
};