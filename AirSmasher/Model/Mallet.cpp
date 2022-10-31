#include "Mallet.h"
#include "../Engine/Model.h"
//コンストラクタ
Mallet::Mallet(GameObject* parent)
	: GameObject(parent, "Mallet"), hModel_(-1)
{
}

//初期化
void Mallet::Initialize()
{
	hModel_ = Model::Load("Assets\\Mallet.fbx");
	assert(hModel_ >= 0);

}

//更新
void Mallet::Update()
{
}

//描画
void Mallet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Mallet::Release()
{
}