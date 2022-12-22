#pragma once
#include "../Engine/GameObject.h"

class LimitTime : public GameObject
{
	short hPict_[10];
	const int MAX_TIME;
	int timer_;
public:
	//コンストラクタ
//引数：parent  親オブジェクト（SceneManager）
	LimitTime(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};