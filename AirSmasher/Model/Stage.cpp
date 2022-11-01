#include "Stage.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_(-1)
{
}

//������
void Stage::Initialize()
{
	hModel_ = Model::Load("Assets\\Table.fbx");
	assert(hModel_ >= 0);
	transform_.scale_.x = 2.0f;
	transform_.scale_.z = 2.0f;
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