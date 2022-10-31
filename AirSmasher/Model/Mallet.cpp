#include "Mallet.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Mallet::Mallet(GameObject* parent)
	: GameObject(parent, "Mallet"), hModel_(-1)
{
}

//������
void Mallet::Initialize()
{
	hModel_ = Model::Load("Assets\\Mallet.fbx");
	assert(hModel_ >= 0);

}

//�X�V
void Mallet::Update()
{
}

//�`��
void Mallet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Mallet::Release()
{
}