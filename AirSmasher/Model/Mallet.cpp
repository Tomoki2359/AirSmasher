#include "Mallet.h"
#include "../Engine/Model.h"
#include "Pack.h"
//#include "../Engine/Math.h"

//コンストラクタ
Mallet::Mallet(GameObject* parent)
    : Mallet(parent, "Mallet")
{
}

Mallet::Mallet(GameObject* parent, std::string name)
    : GameObject(parent, name), isPut_(false),radius_(1.0f),isSuppress_(false),first_(true)
    ,isGoal_(false),count_(0)
{
}

//初期化
void Mallet::Initialize()
{
    hModel_ = Model::Load("Assets\\Mallet.fbx");
    assert(hModel_ >= 0);
    SetInit();
    collision = new CircleCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), radius_,0.0f);
    AddCircleCollider(collision);
    Instantiate<Shadow>(this);
    malletSquar_ = { {0,0},{0,0 }, { 0,0},{0,0 }};
    scale_ = { 1.0f,1.0f };
}

//更新
void Mallet::Update()
{
    //一回だけ行いたいこと
    if (first_)
    {
        RayCastData data;
        data.start = transform_.position_;   //レイの発射位置
        data.start.y = 0;
        data.dir = XMFLOAT3(0, -1, 0);       //レイの方向

        Stage* pStage = (Stage*)FindObject("Stage");
        int hModelStage = pStage->HandleModelStage();

        Model::RayCast(hModelStage, data); //レイを発射

        scale_.x = pStage->GetScaleX();
        scale_.y = pStage->GetScaleZ();

        Pack* pPack_ = (Pack*)FindObject("Pack");
        int hModelPack = pPack_->HandleModelPack();

        data.start = pPack_->GetPosition();
        data.start.y = 3;
        Model::RayCast(hModelStage, data); //レイを発射

        packFront_ = -data.dist;
    }
    //前回の位置の取得
    previousMalletPos_ = transform_.position_;
    if (!isGoal_)
    {
        if (IsPut())
        {
            isPut_ = true;
            transform_.position_.y = front_;
        }
        else
        {
            isPut_ = false;
            transform_.position_.y = 3.0f;
        }

        //各マレットの動き
        MoveMallet();

        //横の壁の設定
        if (transform_.position_.x >= 5 * scale_.x + 1.0f)
        {
            transform_.position_.x = 5 * scale_.x + 0.25f;
        }
        else if (transform_.position_.x <= -5 * scale_.x - 1.0f)
        {
            transform_.position_.x = -5 * scale_.x - 0.25f;
        }

        //最大速度の設定
        if (speed_ >= 2.5f)
        {
            speed_ = 2.5f;
        }

        QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_, &malletSquar_, radius_, dir_);
    }
    else
    {
        transform_.position_.y = 3.0f;
        if (count_ >= 60)
        {
            isGoal_ = false;
            if (IsPut())
            {
                isSuppress_ = true;
            }
            count_ = 0;
        }
        count_++;
    }
}

//描画
void Mallet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Mallet::Release()
{
}

void Mallet::OnCollision(GameObject* pTarget)
{
}