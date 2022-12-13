#include "Stage.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_(-1),scaleX_(4.0f),scaleZ_(3.5f)
{
}

//������
void Stage::Initialize()
{
	hModel_ = Model::Load("Assets\\Table3.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = scaleX_;
	transform_.scale_.z = scaleZ_;
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}