#include "Enemy.h"
#include "Pack.h"
#include "../Engine/Math.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    : Mallet(parent, "Enemy")
{
    transform_.position_.y = 0.3;
}

//開放
void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
}

//初期化
void Enemy::SetInit()
{
    transform_.position_.z = 15.0f;
}

//マレットの動き
void Enemy::MoveMallet()
{
    Pack* pPack = (Pack*)FindObject("Pack");
    
    XMFLOAT3 packPos = pPack->GetPosition();
    packPos.y = 0;
    XMFLOAT3 packDir = pPack->GetDirection();
    packDir.y = 0;

    //パックが相手ゴールに向かうように動かす

    dir_ = Math::SubtractionXMFLOAT3(transform_.position_, previousMalletPos_);

    XMVECTOR vDir = XMLoadFloat3(&dir_);
    vDir = XMVector3Length(vDir);
    speed_ = XMVectorGetX(vDir);
    XMStoreFloat3(&dir_, vDir);

    transform_.position_.x = packPos.x;

    if (transform_.position_.z >= 9.5f * scale_.y)
    {
        transform_.position_.z = 9.5f * scale_.y - 0.125f;
    }
    else if (transform_.position_.z <= 0)
    {
        transform_.position_.z = 0;
    }

    if (pPack->GetPosition().z >= 0)
    {
        AutoDir();
    }
}

//マレットを台に置くかどうか
bool Enemy::IsPut()
{
    return true;
}

//狙う場所を算出
void Enemy::AutoDir()
{
    Pack* pPack = (Pack*)FindObject("Pack");


  //パックが一定の場所を超えるまたは60フレーム後の未来まで見る
    XMFLOAT3 predictionPos_ = pPack->GetPosition();
    XMFLOAT3 predictionDir_ = pPack->GetDirection();
    for (int i = 0; i < 60; i++)
    {
        XMVECTOR vPredictionDir_ = XMLoadFloat3(&predictionDir_);
        vPredictionDir_ = XMVector3Normalize(vPredictionDir_);
        vPredictionDir_ = vPredictionDir_ * speed_;
        XMStoreFloat3(&predictionDir_, vPredictionDir_);
        transform_.position_ = Math::AddXMFLOAT3(transform_.position_, predictionDir_);

        if (transform_.position_.x >= 5 * scale_.x + 1.0f)
        {
            predictionDir_.x = -predictionDir_.x;
            transform_.position_.x = 5 * scale_.x + 0.25f;
        }
        else if (transform_.position_.x <= -5 * scale_.x - 1.0f)
        {
            predictionDir_.x = -predictionDir_.x;
            transform_.position_.x = -5 * scale_.x - 0.25f;
        }
        if (predictionPos_.z <= 15)
        {
            count_ = i;
            isPrediction_ = true;
            break;
        }
    }

    //パックの中心とマレットの中心の向きベクトルとプレイヤーの向きベクトルで向きを求める
   /* XMFLOAT3 sub = Math::SubtractionXMFLOAT3(pMallet->GetPosition(), transform_.position_);
    sub.y = 0.0f;

    sub = Math::FacingConversion(malletDir, sub);
    dir_ = Math::FacingConversion(sub, dir_);*/

    //上のコメントにしている処理のdir_がゴールを狙う場所になるようにマレットの位置と向きを計算する
    XMFLOAT3 aim_ = { -predictionDir_.x,0,-predictionDir_.z - 33 };
    XMFLOAT3 sub = Math::SubtractionXMFLOAT3(transform_.position_,predictionPos_);

    dir_ = Math::FacingConversion(sub, dir_);
    //transform_.position_.z = -transform_.position_.z;
    //transform_.position_.x = -transform_.position_.x;
}
