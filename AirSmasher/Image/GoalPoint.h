#pragma once
#include "../Engine/GameObject.h"
class GoalPoint : public GameObject
{
	short enemyPoint_;
	short playerPoint_;
	short hPict_[10];
public:
	//コンストラクタ
//引数：parent  親オブジェクト（SceneManager）
	GoalPoint(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void GoalEnemy();
	void GoalPlayer();
};

