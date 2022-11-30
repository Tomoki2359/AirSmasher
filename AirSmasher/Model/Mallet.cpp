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
    : GameObject(parent, name), isPut_(false),radius_(1.0f),isSuppress_(false)
{
}

//初期化
void Mallet::Initialize()
{
    hModel_ = Model::Load("Assets\\Mallet.fbx");
    assert(hModel_ >= 0);
    SetInit();
    CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), radius_);
    AddCircleCollider(collision);
    Instantiate<Shadow>(this);
    malletSquar_ = { {0,0,0,0} , {0,0,0,0} };
}

//更新
void Mallet::Update()
{
    if (first_)
    {
        RayCastData data;
        data.start = transform_.position_;   //レイの発射位置
        data.start.y = 0;
        data.dir = XMFLOAT3(0, -1, 0);       //レイの方向

        Stage* pStage = (Stage*)FindObject("Stage");
        int hModelStage = pStage->HandleModelStage();

        Model::RayCast(hModelStage, data); //レイを発射

        front_ = -data.dist;

        //Pack* pPack_ = (Pack*)FindObject("Pack");
        //int hModelPack = pPack_->HandleModelPack();

        //data.start = pPack_->GetPosition();
        //data.start.y = 3;
        //Model::RayCast(hModelStage, data); //レイを発射

        //packFront_ = -data.dist;
    }
    isSuppress_ = false;
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


    MoveMallet();

    //data.dir = XMFLOAT3{1.0,0,0};
    //Model::SegmentRayCast(hModelStage, data);
    //XMVECTOR vNormal = XMVector3Cross(XMLoadFloat3(&data.side1), XMLoadFloat3(&data.side2));
    //XMFLOAT3 side;
    //XMStoreFloat3(&side, vNormal);
    ////壁にぶつかったら方向転換
    //if (side.x > 0)
    //{
    //    isPut_ = true;
    //    transform_.position_.x = (int)transform_.position_.x - 0.2f;
    //}

    //if (side.x < 0)
    //{
    //    isPut_ = false;
    //    transform_.position_.x = (int)transform_.position_.x + 0.2f;
    //}

    //data.start = transform_.position_;
    //data.start.x = 0;
    //data.dir = XMFLOAT3{ 1.0f,0.0f,0.0f };
    //Model::SegmentRayCast(hModelStage, data);
    //vNormal = XMVector3Cross(XMLoadFloat3(&data.side1), XMLoadFloat3(&data.side2));
    //XMStoreFloat3(&side, vNormal);
    //if (side.z > 0)
    //{
    //    transform_.position_.z = (int)transform_.position_.z - 0.2f;
    //}

    //if (side.z < 0)
    //{
    //    transform_.position_.z = (int)transform_.position_.z + 0.2f;
    //}
    QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_, &malletSquar_, radius_, dir_);
    
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
    //RayCastData data;
    //data.start = transform_.position_;   //レイの発射位置
    //data.start.y = 0;
    //data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    ////パックに触れてるとき
    //if (pTarget->GetObjectName() == "Pack")
    //{
    //    Pack* pPack_ = (Pack*)FindObject("Pack");
    //    int hModelPack = pPack_->HandleModelPack();
    //    Model::RayCast(hModelPack, data); //レイを発射

    //    if (data.hit)
    //    {
    //        transform_.position_.y = -data.dist;
    //    }
    //}
    //else
    //{
    //    Stage* pStage = (Stage*)FindObject("Stage");
    //    int hModelStage = pStage->HandleModel();

    //    Model::RayCast(hModelStage, data); //レイを発射

    //    if (data.hit)
    //    {
    //        transform_.position_.y = -data.dist;
    //    }
    //}
}