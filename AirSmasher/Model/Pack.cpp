#include "Pack.h"
#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Math.h"

//コンストラクタ
Pack::Pack(GameObject* parent)
	: GameObject(parent, "Pack"), hModel_(-1), radius_(1.0f)
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
	CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), radius_);
	AddCircleCollider(collision);
	Model::SetColor(hModel_, 0, 150, 150);
	dir_ = XMFLOAT3(-0.2f, 0.0f, -0.2f);
	speed_ = 1.0f;

	packSquar_ = { {0,0},{0,0 }, { 0,0},{0,0 }
};
}

//更新
void Pack::Update()
{
	pPlayer_ = (Player*)FindObject("Player");
	assert(pPlayer_ != nullptr);

	pEnemy_ = (Enemy*)FindObject("Enemy");
	assert(pEnemy_ != nullptr);

	if (isGool_)
	{
		transform_.position_ = pPlayer_->GetPosition();
		transform_.position_.y = 0;

		if (pPlayer_->GetSuppress())
		{
			isGool_ = false;
		}
	}
	else
	{
		previousPackPos_ = transform_.position_;

		XMVECTOR vdir_ = XMLoadFloat3(&dir_);
		vdir_ = XMVector3Normalize(vdir_);
		vdir_ = vdir_ * speed_;
		XMStoreFloat3(&dir_, vdir_);
		//transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }));
		transform_.position_ = Math::AddXMFLOAT3(transform_.position_, dir_);
		QuadrangleHit::CreateSquar(transform_.position_, previousPackPos_, &packSquar_, radius_, dir_);
		//壁の当たり処理
		IsWall();

		//ゴールに落ちたか
		IsGoal();
		if (pPlayer_->GetPut())
		{
			if (QuadrangleHit::HitTest(packSquar_, pPlayer_->GetSquare()))
			{
				IsMallet(pPlayer_);
			}
		}
	}
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
		/*pPlayer_ = (Player*)FindObject("Player");
		assert(pPlayer_ != nullptr);*/
		IsMallet(pPlayer_);
	}
	else if (pTarget->GetObjectName() != "Player")
	{
		pPlayer_->SetSuppress(false);
	}
	if (pTarget->GetObjectName() == "Enemy")
	{
		IsMallet(pEnemy_);
	}
	else if (pTarget->GetObjectName() != "Enemy")
	{
		pEnemy_->SetSuppress(false);
	}
}

void Pack::IsMallet(Mallet* pMallet)
{
	if (pMallet->GetPut())
	{
		//前のマレットの位置
		XMFLOAT3 malletPos = pMallet->GetPreviousPosition();
		malletPos.y = 0;

		//マレットの動いた方向
		XMFLOAT3 malletDir = pMallet->GetDirection();
		malletDir.y = 0;
		//移動方向
			//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetPosition().x,0,-pPlayer_->GetPosition().z });
			//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
			//dir_ = Math::FacingConversion(Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()), XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
			//XMFLOAT3 packPos = transform_.position_;

	/*	XMVECTOR vMalletDir = XMVector3Normalize(XMLoadFloat3(&malletDir));
		vMalletDir = vMalletDir * radius_;
		XMStoreFloat3(&malletDir, vMalletDir);
		transform_.position_ = Math::AddXMFLOAT3(transform_.position_,malletDir);*/

		

		//ズレの修正
		/*transform_.position_ = XMFLOAT3{ pMallet->GetPosition().x,0,pMallet->GetPosition().z };
		if (dir_.x <= 0)
		{
			XMVECTOR vDir = XMVector3Normalize(XMLoadFloat3(&dir_));
			vDir = vDir * radius_ * 4;
			XMStoreFloat3(&dir_, vDir);
		}
		else
		{
			XMVECTOR vDir = XMVector3Normalize(XMLoadFloat3(&dir_));
			vDir = -vDir * radius_ * 4;
			XMStoreFloat3(&dir_, vDir);
		}
		transform_.position_ = Math::AddXMFLOAT3(transform_.position_, dir_);*/
		if (!pMallet->GetSuppress())
		{
			XMFLOAT3 pos = Math::SubtractionXMFLOAT3(transform_.position_, pMallet->GetPosition());
			XMVECTOR vpos = XMLoadFloat3(&pos);	//ズレた位置
			float addRadius = radius_ + pMallet->GetRadius();
			XMVECTOR vdir = XMLoadFloat3(&dir_);	//中心と中心の正しい距離
			vdir = XMVector3Normalize(vdir);
			vdir = vdir * addRadius;
			XMStoreFloat3(&pos, -(vdir - vpos));
			transform_.position_ = Math::AddXMFLOAT3(transform_.position_, pos);
		}
		else
		{
			dir_ = XMFLOAT3{ 0,0,0 };
			speed_ = 0;
		}

		//パックの中心とマレットの中心の向きベクトルとプレイヤーの向きベクトルで向きを求める
		XMFLOAT3 sub = Math::SubtractionXMFLOAT3( pMallet->GetPosition(), transform_.position_);
		//XMFLOAT3 sub = Math::SubtractionXMFLOAT3(transform_.position_, malletPos);

		//XMVECTOR dir = XMVector3Normalize(XMVector3Normalize(XMLoadFloat3(&sub)) - XMVector3Normalize(XMLoadFloat3(&malletDir)));
		//XMStoreFloat3(&dir_, XMVector3Normalize(dir));

		dir_ = Math::FacingConversion(malletDir,sub );
		
		//その方向に移動
		speed_ = (pMallet->GetSpeed() + speed_) / 2;

		/*XMVECTOR vDir = XMVector3Normalize(XMLoadFloat3(&dir_));
		vDir = vDir * speed_;
		XMStoreFloat3(&dir_, vDir);*/

		
	}
}

void Pack::IsWall()
{
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
	int hStage = pStage->HandleModelStage();

	////半径分レイキャスト
	//RayCastData rData;
	//rData.start = transform_.position_;
	//rData.start.z = 0;
	//rData.dir = XMFLOAT3{0.0f,0.0f,1.0f};
	//Model::SegmentRayCast(hStage, rData);
	//XMVECTOR vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1) , XMLoadFloat3(&rData.side2));
	//XMFLOAT3 side;
	//XMStoreFloat3(&side, vNormal);

	////壁にぶつかったら方向転換
	//if (side.x > 0)
	//{
	//	//dir_.x = -dir_.x;
	//	transform_.position_.x = (int)(transform_.position_.x + 1.5f);
	//}

	//if (side.x < 0)
	//{
	//	//dir_.x = -dir_.x;
	//	transform_.position_.x = (int)(transform_.position_.x - 1.5f);
	//}

	//rData.start = transform_.position_;
	//rData.start.x = 0;
	//rData.dir = XMFLOAT3{ 1.0f,0.0f,0.0f };
	//Model::SegmentRayCast(hStage, rData);
	//vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1), XMLoadFloat3(&rData.side2));
	//XMStoreFloat3(&side, vNormal);
	//if (side.z > 0)
	//{
	//	dir_.z = -dir_.z;
	//	transform_.position_.z = (int)(transform_.position_.z + 1.5f);
	//}
	//
	//if (side.z < 0)
	//{
	//	dir_.z = -dir_.z;
	//	transform_.position_.z = (int)(transform_.position_.z - 1.5f);
	//}

	if (transform_.position_.x >= 5 * pStage->GetScaleX() + 1.0f)
	{
		dir_.x = -dir_.x;
		transform_.position_.x = 5 * pStage->GetScaleX() + 0.25f;
	}
	else if (transform_.position_.x <= -5 * pStage->GetScaleX() - 1.0f)
	{
		dir_.x = -dir_.x;
		transform_.position_.x = -5 * pStage->GetScaleX() -0.25f;
	}
	if (transform_.position_.z >= 9.5f * pStage->GetScaleZ())
	{
		dir_.z = -dir_.z;
		transform_.position_.z = 9.5f * pStage->GetScaleZ() - 0.125f;
	}
	else if (transform_.position_.z <= -9.5f * pStage->GetScaleZ())
	{
		dir_.z = -dir_.z;
		transform_.position_.z = -9.5f * pStage->GetScaleZ() + 0.125f;
	}
}

void Pack::IsGoal()
{
	RayCastData data;
	data.start = transform_.position_;   //レイの発射位置
	data.start.y = 0;
	data.dir = XMFLOAT3(0, -1, 0);       //レイの方向

	int hModelStage = pStage->HandleModelStage();

	Model::RayCast(hModelStage, data); //レイを発射

	if (data.hit != true)
	{
		transform_.position_.x = 0;
		transform_.position_.z = 0;
		speed_ = 0;
		isGool_ = true;
	}
}

void Pack::IsMallet()
{
	QuadrangleHit::CreateSquar(transform_.position_, previousPackPos_,&packSquar_,radius_,dir_);
}