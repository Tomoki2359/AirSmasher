#include "Pack.h"
#include "../Engine/Model.h"
//コンストラクタ
Pack::Pack(GameObject* parent)
	: GameObject(parent, "Pack"), hModel_(-1)
{
}

//初期化
void Pack::Initialize()
{
	hModel_ = Model::Load("Assets\\Pack.fbx");
	assert(hModel_ >= 0);
	//transform_.scale_.x = 2.0f;
	//transform_.scale_.z = 2.0f;
	CylinderCollider* collision = new CylinderCollider(XMFLOAT3(0, 0.0f, 0), 0.2f, 0.2f);
	AddCylCollider(collision);
}

//更新
void Pack::Update()
{
}

//描画
void Pack::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Pack::Release()
{
}

void Pack::OnCollision(GameObject* pTarget)
{
	//弾に当たったとき
	if (pTarget->GetObjectName() == "Player")
	{
		pTarget->KillMe();
	}
}
