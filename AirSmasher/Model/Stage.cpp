#include "Stage.h"
#include "../Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_(-1)
{
}

//初期化
void Stage::Initialize()
{
	hModel_ = Model::Load("Assets\\Table.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = 5.0f;
	transform_.scale_.z = 5.0f;
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}