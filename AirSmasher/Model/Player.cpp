#include "Player.h"
//#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
//#include "Stage.h"
//#include "Pack.h"
#include "../Engine/Math.h"

//コンストラクタ
Player::Player(GameObject* parent)
    : Mallet(parent, "Player")
{
    malletSquar_ = { {0,0},{0,0 }, { 0,0},{0,0 }
};
}

//開放
void Player::Release()
{
}

//当たったときの判定
void Player::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        if (isSuppress_)
        {
            transform_.position_.y = 0.25f;
        }
    }
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

void Player::OffCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        isSuppress_ = false;
    }
}

//初期化
void Player::SetInit()
{
    transform_.position_.z = -20.0f;
    //transform_.position_.y = 1.0f;
    //Camera::SetPosition(XMVectorSet(0, 50, 4, 0));
    //Camera::SetTarget(XMVectorSet(0, 0, 5, 0));
    //Camera::SetPosition(XMVectorSet(0, 15, -50, 0));
    //Camera::SetTarget(XMVectorSet(0, 0, 0, 0));
    Camera::SetPosition(XMVectorSet(0, 57, -45, 0));
    Camera::SetTarget(XMVectorSet(0, -15, 3, 0));
    mousePos = Input::GetMousePosition();
    isCamera_ = true;
}

//マレットの動き
void Player::MoveMallet()
{
   

    //移動処理
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;

    //XMFLOAT3 mousePosNow = XMFLOAT3{ (Input::GetMousePosition().x - w), Input::GetMousePosition().z, Input::GetMousePosition().y - h });
    XMFLOAT3 mousePosNow = Math::DivisionXMFLOAT3(XMFLOAT3{ (Input::GetMousePosition().x - w), Input::GetMousePosition().z, Input::GetMousePosition().y - h }, 19);

    /* transform_.position_.x += (mousePosNow.x - mousePos.x) / 20;
     transform_.position_.z -= (mousePosNow.z - mousePos.z) / 20;*/
    transform_.position_.x += (mousePosNow.x - mousePos.x);
    transform_.position_.z -= (mousePosNow.z - mousePos.z);
    dir_ = Math::SubtractionXMFLOAT3(mousePosNow, mousePos);

    XMVECTOR vDir = XMLoadFloat3(&dir_);
    vDir = XMVector3Length(vDir);
    speed_ = XMVectorGetX(vDir);
    XMStoreFloat3(&dir_, vDir);

    mousePos = mousePosNow;

    if (Input::IsMouceDown(1))
    {
        if (!isCamera_)
        {
            isCamera_ = true;
        }
        else
        {
            isCamera_ = false;
        }
       
    }
    else
    {
    /*    Camera::SetPosition(XMVectorSet(0, 30, -60, 0));
        Camera::SetTarget(XMVectorSet(0, 0, 10, 0));*/
    }

    if (isCamera_)
    {
        Camera::SetPosition(XMVectorSet(0, 57, -45, 0));
        Camera::SetTarget(XMVectorSet(0, -15, 3, 0));
    }
    else
    {
        Camera::SetPosition(XMVectorSet(0, 15, -60 , 0));
        Camera::SetTarget(XMVectorSet(0, 0, 10, 0));
    }

    if (transform_.position_.z >= 0)
    {
        transform_.position_.z = 0;
    }

    QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_, &malletSquar_, radius_, dir_);
}

//台を置くかどうか
bool Player::IsPut()
{
    if (Input::IsMouceDown(0))
    {
        isSuppress_ = true;
    }
    if (Input::IsMouce(0))
    {
        collision->SetDimension(0.0f);
        return true;
    }
    collision->SetDimension(1.0f);
    return false;
}
