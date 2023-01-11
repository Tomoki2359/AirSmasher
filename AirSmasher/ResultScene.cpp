#include "ResultScene.h"
#include "Image/ResultPoint.h"
#include "Image/ResultPlayer.h"
//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//初期化
void ResultScene::Initialize()
{
	Instantiate<ResultPoint>(this);
	Instantiate<ResultPlayer>(this);
}

//更新
void ResultScene::Update()
{
}

//描画
void ResultScene::Draw()
{
}

//開放
void ResultScene::Release()
{
}