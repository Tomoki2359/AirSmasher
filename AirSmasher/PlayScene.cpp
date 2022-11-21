#include "PlayScene.h"
#include "Model/Stage.h"
#include "Model/Player.h"
#include "Model/Enemy.h"
#include "Model/Pack.h"
//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	//Instantiate<Enemy>(this);
	Instantiate<Pack>(this);
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