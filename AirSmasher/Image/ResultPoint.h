#pragma once
#include "../Engine/GameObject.h"
class ResultPoint : public GameObject
{
	short enemyPoint_;
	short playerPoint_;
	short hPict_[11];
public:
	//コンストラクタ
//引数：parent  親オブジェクト（SceneManager）
	ResultPoint(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//void SetPlayerPoint(int p);
	//void SetEnemyPoint(int p);
};