#include "Shadow.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Shadow::Shadow(GameObject* parent)
	: GameObject(parent, "Shadow"), hModel_(-1)
{
}

//������
void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets\\Shadow.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Shadow::Update()
{
	transform_.position_.y = -pParent_->GetPosition().y;
}

//�`��
void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Shadow::Release()
{
}