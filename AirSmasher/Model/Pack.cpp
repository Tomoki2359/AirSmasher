#include "Pack.h"
#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Math.h"

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
	//transform_.position_.y = 0.3f;
	CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), 0.5f);
	AddCircleCollider(collision);
	//dir_ = XMFLOAT3(0.2f, 0.0f, -0.2f);
}

//�X�V
void Pack::Update()
{
	XMVECTOR vDir = XMLoadFloat3(&dir_);
	vDir = XMVector3Length(vDir);
	//transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::DivisionXMFLOAT3(Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }), 10));
	//transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }));
	transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3(dir_, speed_));

	//�ǂ̓����菈��
	IsWall();
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
		pPlayer_ = (Player*)FindObject("Player");
		assert(pPlayer_ != nullptr);
		//�ړ�����
		//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetPosition().x,0,-pPlayer_->GetPosition().z });
		//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
		//dir_ = Math::FacingConversion(Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()), XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
		dir_ = Math::FacingConversion(Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPreviousPosition()), XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
		/*XMVECTOR vPack = XMLoadFloat3(&Math::SubtractionXMFLOAT3( transform_.position_,pPlayer_->GetPosition()));
		vPack = XMVector3Normalize(vPack);
		XMVECTOR vPlayer = XMLoadFloat3(&pPlayer_->GetPosition());
		XMStoreFloat3(&dir_, vPlayer - vPack);*/

		//pPlayer_->SetPosition(Math::AddXMFLOAT3(pPlayer_->GetPosition(),Math::GetDistance(pPlayer_->GetPosition(),transform_.position_)));
		//�Y���̏C��
		//transform_.position_ = Math::AddXMFLOAT3(transform_.position_,Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()));

		//���̕����Ɉړ�
		//XMVECTOR vDir = XMLoadFloat3(&dir_);
		//vDir = XMVector3Length(vDir);
		//speed_ = XMVectorGetX(vDir);
		speed_ = pPlayer_->GetSpeed() + 0.05f;
			//Math::DivisionXMFLOAT3(Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }), 10);
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

	//�ǂɂԂ�����������]��
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
