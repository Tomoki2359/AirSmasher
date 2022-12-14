#include "PlayScene.h"
#include "Model/Stage.h"
#include "Model/Player.h"
#include "Model/Enemy.h"
#include "Model/Pack.h"
#include "Image/GoalPoint.h"
//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Pack>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<GoalPoint>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}