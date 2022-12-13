#include "GoalPoint.h"

//コンストラクタ
GoalPoint::GoalPoint(GameObject* parent)
	: GameObject(parent, "GoalPoint")
{
}

//初期化
void GoalPoint::Initialize()
{
}

//更新
void GoalPoint::Update()
{
}

//描画
void GoalPoint::Draw()
{
}

//開放
void GoalPoint::Release()
{
}

void GoalPoint::GoalEnemy()
{
	enemyPoint_++;
}

void GoalPoint::GoalPlayer()
{
	playerPoint_++;
}
