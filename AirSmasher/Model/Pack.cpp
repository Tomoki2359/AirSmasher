#include "Pack.h"
#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Math.h"

//コンストラクタ
Pack::Pack(GameObject* parent)
	: GameObject(parent, "Pack"), hModel_(-1), radius_(1.0f),ismallet_(false)
{
}

//初期化
void Pack::Initialize()
{
	hModel_ = Model::Load("Assets\\Pack.fbx");
	assert(hModel_ >= 0);
	collision = new CircleCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), radius_,0.0f);
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

	pGoal_ = (GoalPoint*)FindObject("GoalPoint");
	assert(pGoal_ != nullptr);

	if (isGool_)
	{
		if (ismallet_)
		{
			transform_.position_ = pPlayer_->GetPosition();
			transform_.position_.y = 0;

			if (pPlayer_->GetSuppress())
			{
				isGool_ = false;
			}
		}
		else if (!ismallet_)
		{
			transform_.position_ = pEnemy_->GetPosition();
			transform_.position_.y = 0;

			if (pEnemy_->GetSuppress())
			{
				isGool_ = false;
			}
		}
	}
	else
	{
		previousPackPos_ = transform_.position_;

		XMVECTOR vdir_ = XMLoadFloat3(&dir_);
		vdir_ = XMVector3Normalize(vdir_);
		vdir_ = vdir_ * speed_;
		XMStoreFloat3(&dir_, vdir_);
		transform_.position_ = Math::AddXMFLOAT3(transform_.position_, dir_);
		QuadrangleHit::CreateSquar(transform_.position_, previousPackPos_, &packSquar_, radius_, dir_);
		//壁の当たり処理
		IsWall();

		//マレットと自分の通り道に当たったか(すり抜け防止)
		if (pPlayer_->GetPut() && !isGool_)
		{
			if (QuadrangleHit::HitTest(packSquar_, pPlayer_->GetSquare()))
			{
				IsMallet(pPlayer_);
			}
			else if (QuadrangleHit::HitTest(packSquar_, pEnemy_->GetSquare()))
			{
				IsMallet(pEnemy_);
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
	//マレットに当たった時
	if (pTarget->GetObjectName() == "Player")
	{
		IsMallet(pPlayer_);
	}
	if (pTarget->GetObjectName() == "Enemy")
	{
		IsMallet(pEnemy_);
		//dir_ = XMFLOAT3{-transform_.position_.x , 0 , -transform_.position_.z - 33};
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
		//ズレの修正(めり込み阻止)　1
		if (!pMallet->GetSuppress() && !isGool_)
		{
			XMFLOAT3 pos = Math::SubtractionXMFLOAT3(transform_.position_, pMallet->GetPosition());
			pos.y = 0.0f;
			XMVECTOR vpos = XMLoadFloat3(&pos);	//ズレた位置
			float addRadius = radius_ + pMallet->GetRadius();
			//XMVECTOR vdir = XMLoadFloat3(&dir_);	//中心と中心の正しい距離
			//vdir = XMVector3Normalize(vdir);
			XMVECTOR vdir;
			vdir = XMVector3Normalize(vpos);

			vdir = vdir * addRadius;
			XMStoreFloat3(&pos, (vdir - vpos));
			transform_.position_ = Math::AddXMFLOAT3(transform_.position_, pos);
		}
		else
		{
			dir_ = XMFLOAT3{ 0,0,0 };
			speed_ = 0;
			return;
		}

		//パックの中心とマレットの中心の向きベクトルとプレイヤーの向きベクトルで向きを求める
		XMFLOAT3 sub = Math::SubtractionXMFLOAT3( pMallet->GetPosition(), transform_.position_); //2
		sub.y = 0.0f;

		sub = Math::FacingConversion(malletDir, sub ); //3
		dir_ = Math::FacingConversion(sub, dir_ ); //4
		
		//その方向に移動
		speed_ = (pMallet->GetSpeed() + speed_) / 2;
	}
}

//壁の判定
void Pack::IsWall()
{
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
	//int hStage = pStage->HandleModelStage();

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
	if (transform_.position_.z >= 9.5f * pStage->GetScaleZ() - 1.0f)
	{
		transform_.position_.z = 9.5f * pStage->GetScaleZ() + 0.25f;
		//ゴールに落ちたか
		if (IsGoal())
		{
			ismallet_ = false;
			pGoal_->GoalPlayer();
		}
		dir_.z = -dir_.z;
		transform_.position_.z = 9.5f * pStage->GetScaleZ() - 1.0f;
	}
	else if (transform_.position_.z <= -9.5f * pStage->GetScaleZ() + 1.0f)
	{
		transform_.position_.z = -9.5f * pStage->GetScaleZ() - 0.25f;
		//ゴールに落ちたか
		if (IsGoal())
		{
			ismallet_ = true;
			pGoal_->GoalEnemy();
		}
		dir_.z = -dir_.z;
		transform_.position_.z = -9.5f * pStage->GetScaleZ() + 1.0f;
	}
}

bool Pack::IsGoal()
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
		pPlayer_->SetGoal(isGool_);
		pEnemy_->SetGoal(isGool_);
		return true;
	}
	return false;
}
