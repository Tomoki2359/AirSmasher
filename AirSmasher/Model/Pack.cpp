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
	CylinderCollider* collision = new CylinderCollider(XMFLOAT3(0, 0.0f, 0), 0.2f, 0.2f);
	AddCylCollider(collision);
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

void Pack::OnCollision(GameObject* pTarget)
{
	//�e�ɓ��������Ƃ�
	if (pTarget->GetObjectName() == "Player")
	{
		pTarget->KillMe();
	}
}
