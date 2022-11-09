#include "Pack.h"
#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Math.h"
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
	//transform_.position_.y = 0.3f;
	CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), 1.0f);
	AddCircleCollider(collision);
}

//更新
void Pack::Update()
{
	XMVECTOR vDir = XMLoadFloat3(&dir_);
	vDir = XMVector3Length(vDir);
	transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::DivisionXMFLOAT3(Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }),10));
	IsWall();
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
		pPlayer_ = (Player*)FindObject("Player");
		assert(pPlayer_ != nullptr);
		dir_ = Math::FacingConversion(dir_, XMFLOAT3{ pPlayer_->GetPosition().x,0,-pPlayer_->GetPosition().z });
		//pPlayer_->SetPosition(Math::AddXMFLOAT3(pPlayer_->GetPosition(),Math::GetDistance(pPlayer_->GetPosition(),transform_.position_)));
		transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()));
		int i = 0;
	}
}

bool Pack::IsWall()
{
	Stage* pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
	int hStage = pStage->HandleModel();

	RayCastData rData;
	rData.start = transform_.position_;
	rData.start.z = 0;
	rData.dir = XMFLOAT3{0.0f,0.0f,0.2f};
	Model::SegmentRayCast(hStage, rData);
	XMVECTOR vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1) , XMLoadFloat3(&rData.side2));
	XMFLOAT3 side;
	XMStoreFloat3(&side, vNormal);
	if (side.x > 0)
	{
		dir_.x = -dir_.x;
	}

	if (side.x < 0)
	{
		dir_.x = -dir_.x;
	}
	rData.start = transform_.position_;
	rData.start.x = 0;
	rData.dir = XMFLOAT3{ 0.2f,0.0f,0.0f };
	Model::SegmentRayCast(hStage, rData);
	vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1), XMLoadFloat3(&rData.side2));
	side;
	XMStoreFloat3(&side, vNormal);
	if (side.z > 0)
	{
		dir_.z = -dir_.z;
	}
	
	if (side.z < 0)
	{
		dir_.z = -dir_.z;
	}

	return false;
}
