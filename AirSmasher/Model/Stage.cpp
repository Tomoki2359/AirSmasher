#include "Stage.h"
#include "../Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_(-1),scaleX_(4.0f),scaleZ_(3.5f)
{
}

//初期化
void Stage::Initialize()
{
	hModel_ = Model::Load("Assets\\Table3.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = scaleX_;
	transform_.scale_.z = scaleZ_;
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