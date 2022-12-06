#include "Shadow.h"
#include "../Engine/Model.h"
//コンストラクタ
Shadow::Shadow(GameObject* parent)
	: GameObject(parent, "Shadow"), hModel_(-1)
{
}

//初期化
void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets\\Shadow.fbx");
	assert(hModel_ >= 0);
}

//更新
void Shadow::Update()
{
	transform_.position_.y = -pParent_->GetPosition().y;
}

//描画
void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Shadow::Release()
{
}