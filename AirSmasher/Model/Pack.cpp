#include "Pack.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Pack::Pack(GameObject* parent)
	: GameObject(parent, "Pack"), hModel_(-1)
{
}

//������
void Pack::Initialize()
{
	hModel_ = Model::Load("Assets\\Pack.fbx");
	assert(hModel_ >= 0);
	//transform_.scale_.x = 2.0f;
	//transform_.scale_.z = 2.0f;
}

//�X�V
void Pack::Update()
{
}

//�`��
void Pack::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Pack::Release()
{
}