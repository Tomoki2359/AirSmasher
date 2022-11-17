#include "Pack.h"
#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Math.h"

//コンストラクタ
Pack::Pack(GameObject* parent)
	: GameObject(parent, "Pack"), hModel_(-1), radius_(0.5f)
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
	CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), 0.5f);
	AddCircleCollider(collision);
	Model::SetColor(hModel_, 0, 150, 150);
	dir_ = XMFLOAT3(0.2f, 0.0f, -0.2f);
	speed_ = 4.0f;
}

//更新
void Pack::Update()
{
	
	XMVECTOR vDir = XMLoadFloat3(&dir_);
	vDir = XMVector3Length(vDir);
	//transform_.position_ = Math::AddXMFLOAT3(transform_.position_,Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }));
	//transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }));
	transform_.position_ = Math::AddXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3(dir_, speed_));

	//壁の当たり処理
	IsWall();

	//ゴールに落ちたか
	//IsGoal();
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
		IsMallet(pPlayer_);
	}
	else if (pTarget->GetObjectName() == "Enemy")
	{
		pEnemy_ = (Enemy*)FindObject("Enemy");
		assert(pEnemy_ != nullptr);
		IsMallet(pEnemy_);
	}
}

void Pack::IsMallet(Mallet* pMallet)
{
	if (pMallet->GetPut())
	{
		XMFLOAT3 malletPos = pMallet->GetPreviousPosition();
		malletPos.y = 0;
		//移動方向
			//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetPosition().x,0,-pPlayer_->GetPosition().z });
			//dir_ = Math::FacingConversion(dir_, XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
			//dir_ = Math::FacingConversion(Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()), XMFLOAT3{ -pPlayer_->GetDirection().x,0,-pPlayer_->GetDirection().z });
			//XMFLOAT3 packPos = transform_.position_;

		//パックの中心とマレットの中心の向きベクトルとプレイヤーの向きベクトルで向きを求める
		XMFLOAT3 sub = Math::SubtractionXMFLOAT3(transform_.position_, pMallet->GetPreviousPosition());
		dir_ = Math::FacingConversion(Math::FacingConversion(sub, XMFLOAT3{ -pMallet->GetDirection().x,0,-pMallet->GetDirection().z }), dir_);

		
		
		/*XMVECTOR vPack = XMLoadFloat3(&Math::SubtractionXMFLOAT3( transform_.position_,pPlayer_->GetPosition()));
		vPack = XMVector3Normalize(vPack);
		XMVECTOR vPlayer = XMLoadFloat3(&pPlayer_->GetPosition());
		XMStoreFloat3(&dir_, vPlayer - vPack);*/

		//pPlayer_->SetPosition(Math::AddXMFLOAT3(pPlayer_->GetPosition(),Math::GetDistance(pPlayer_->GetPosition(),transform_.position_)));
		
		//ズレの修正
		XMMATRIX mRotate = XMMatrixRotationY(Math::GetRadian(sub, XMFLOAT3{0,0,1.0f}));
		//現在位置をベクトルにしておく
		XMFLOAT3 a = malletPos;
		XMVECTOR vPos = XMLoadFloat3(&a);

		//移動ベクトル
		XMFLOAT3 move = { 0, 0, 2.0f };                //奥向きのXMFLOAT3構造体を用意し
		XMVECTOR vMove = XMLoadFloat3(&move);               //それをベクトルにする
		vMove = XMVector3TransformCoord(vMove, mRotate);    //戦車の向きに合わせて回転
		vPos += vMove;
		XMStoreFloat3(&transform_.position_, vPos);
		//transform_.position_ = Math::AddXMFLOAT3(transform_.position_,Math::SubtractionXMFLOAT3(transform_.position_, pPlayer_->GetPosition()));

		//その方向に移動
		XMVECTOR vDir = XMLoadFloat3(&dir_);
		vDir = XMVector3Length(vDir);
		//speed_ = XMVectorGetX(vDir);
		speed_ = (pMallet->GetSpeed() + speed_) / 2;
		//speed_ = pPlayer_->GetSpeed() + 0.2f;
		//Math::DivisionXMFLOAT3(Math::MultiplicationXMFLOAT3(dir_, XMFLOAT3{ XMVectorGetX(vDir),0,XMVectorGetZ(vDir) }), 10);
	}
}

void Pack::IsWall()
{
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
	int hStage = pStage->HandleModelStage();

	//半径分レイキャスト
	RayCastData rData;
	rData.start = transform_.position_;
	rData.start.z = 0;
	rData.dir = XMFLOAT3{0.0f,0.0f,1.0f};
	Model::SegmentRayCast(hStage, rData);
	XMVECTOR vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1) , XMLoadFloat3(&rData.side2));
	XMFLOAT3 side;
	XMStoreFloat3(&side, vNormal);

	//壁にぶつかったら方向転換
	if (side.x > 0)
	{
		dir_.x = -dir_.x;
		transform_.position_.x = (int)transform_.position_.x;
	}

	if (side.x < 0)
	{
		dir_.x = -dir_.x;
		transform_.position_.x = (int)transform_.position_.x;
	}

	rData.start = transform_.position_;
	rData.start.x = 0;
	rData.dir = XMFLOAT3{ 1.0f,0.0f,0.0f };
	Model::SegmentRayCast(hStage, rData);
	vNormal = XMVector3Cross(XMLoadFloat3(&rData.side1), XMLoadFloat3(&rData.side2));
	XMStoreFloat3(&side, vNormal);
	if (side.z > 0)
	{
		dir_.z = -dir_.z;
		transform_.position_.z = (int)transform_.position_.z;
	}
	
	if (side.z < 0)
	{
		dir_.z = -dir_.z;
		transform_.position_.z = (int)transform_.position_.z;
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
	}
}

void Pack::IsMallet()
{
	QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_,&packSquar_,radius_);
}