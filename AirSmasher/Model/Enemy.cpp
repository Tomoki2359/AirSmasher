#include "Enemy.h"
#include "Pack.h"
#include "../Engine/Math.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    : Mallet(parent, "Enemy")
{
    transform_.position_.y = 0.3;
#ifdef _DEBUG
    isStopMove = false;
#endif

}

//開放
void Enemy::Release()
{
}

//当たったときの判定
void Enemy::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        if (isSuppress_)
        {
            transform_.position_.y = 0.25f;
            AutoDir();
            transform_.position_ = Math::SubtractionXMFLOAT3(transform_.position_, Math::MultiplicationXMFLOAT3( malletDir_,2));
            //countFuture_ = 2;
        }
    }
}

void Enemy::OffCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        isSuppress_ = false;
    }
}


//初期化
void Enemy::SetInit()
{
    transform_.position_.z = 15.0f;
    malletSpeed_ = 0.5f;
    enemyPosition_ = transform_.position_;
}

//マレットの動き
void Enemy::MoveMallet()
{
#ifdef _DEBUG
    if (Input::IsKeyDown(DIK_1))
    {
        isStopMove = !isStopMove;
    }
    if (isStopMove)
        return;
#endif
    Pack* pPack = (Pack*)FindObject("Pack");
    
    XMFLOAT3 packPos = pPack->GetPosition();
    packPos.y = 0;
    XMFLOAT3 packDir = pPack->GetDirection();
    packDir.y = 0;

    //パックが相手ゴールに向かうように動かす

    /*malletDir_ = Math::SubtractionXMFLOAT3(transform_.position_, previousMalletPos_);

    XMVECTOR vDir = XMLoadFloat3(&malletDir_);
    vDir = XMVector3Length(vDir);
    malletSpeed_ = XMVectorGetX(vDir);
    XMStoreFloat3(&malletDir_, vDir);*/

   // transform_.position_.x = packPos.x;
    //malletDir_ = { -transform_.position_.x,0,-transform_.position_.z - 33 };
    if (transform_.position_.z >= 9.5f * stageScale_.y)
    {
        transform_.position_.z = 9.5f * stageScale_.y - 0.125f;
    }
    else if (transform_.position_.z <= 0)
    {
        transform_.position_.z = 0;
    }

    if (pPack->GetPosition().z >= 0 && !isPrediction_ && pPack->GetDirection().z >= 0)
    {
        AutoDir();
    }
    if (countFuture_ == 0)
    {
        transform_.position_ = Math::AddXMFLOAT3(transform_.position_, malletDir_);
        enemyPosition_ = transform_.position_;
        isPrediction_ = false;
    }
    else if(transform_.position_.x != enemyPosition_.x && transform_.position_.z != enemyPosition_.z)
    {
        XMFLOAT3 des_ = Math::SubtractionXMFLOAT3(enemyPosition_ ,transform_.position_);
        XMVECTOR vdes = XMVector3Normalize(XMLoadFloat3(&des_));
        vdes = vdes * malletSpeed_;
        XMStoreFloat3(&des_, (vdes));
        /*if (0 == (transform_.position_.x - Math::AddXMFLOAT3(transform_.position_, des_).x) * (enemyPosition_.y - transform_.position_.y) + (transform_.position_.y - Math::AddXMFLOAT3(transform_.position_, des_).y) * (transform_.position_.x - enemyPosition_.x))
        {
            transform_.position_ = enemyPosition_;
            return;
        }*/
        transform_.position_ = Math::AddXMFLOAT3(transform_.position_, des_);
    }
    /*else if(pPack->GetPosition().z < 0)
    {
        
    }*/
    countFuture_--;
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
    float predictionSpeed_ = pPack->GetSpeed();
    float R = (float)(rand() % 200) / 10;
    for (int i = 0; i < 60; i++)
    {
        XMVECTOR vPredictionDir_ = XMLoadFloat3(&predictionDir_);
        vPredictionDir_ = XMVector3Normalize(vPredictionDir_);
        vPredictionDir_ = vPredictionDir_ * predictionSpeed_;
        XMStoreFloat3(&predictionDir_, vPredictionDir_);
        predictionPos_ = Math::AddXMFLOAT3(predictionPos_, predictionDir_);

        if (predictionPos_.x >= 5 * stageScale_.x + 1.0f)
        {
            predictionDir_.x = -predictionDir_.x;
            predictionPos_.x = 5 * stageScale_.x + 0.25f;
        }
        else if (predictionPos_.x <= -5 * stageScale_.x - 1.0f)
        {
            predictionDir_.x = -predictionDir_.x;
            predictionPos_.x = -5 * stageScale_.x - 0.25f;
        }/*
        if (predictionPos_.z >= 9.5f * stageScale_.y - 1.0f)
        {
            malletDir_.z = -malletDir_.z;
            predictionPos_.z = 9.5f * stageScale_.y - 1.0f;
        }
        else if (predictionPos_.z <= -9.5f * stageScale_.y + 1.0f)
        {
            malletDir_.z = -malletDir_.z;
            predictionPos_.z = -9.5f * stageScale_.y + 1.0f;
        }*/
        if (predictionPos_.z >= 10 + R)
        {
            countFuture_ = i;
            isPrediction_ = true;
            break;
        }
    }
    if (!isPrediction_)
        return;
    //パックの中心とマレットの中心の向きベクトルとプレイヤーの向きベクトルで向きを求める
   /* XMFLOAT3 sub = Math::SubtractionXMFLOAT3(pMallet->GetPosition(), transform_.position_);
    sub.y = 0.0f;

    sub = Math::FacingConversion(malletDir, sub);
    malletDir_ = Math::FacingConversion(sub, malletDir_);*/

    //上のコメントにしている処理のmalletDir_がゴールを狙う場所になるようにマレットの位置と向きを計算する
    XMFLOAT3 aim_ = { -predictionPos_.x,0,-predictionPos_.z - 33 };//4

     //1
    XMFLOAT3 pos;// = Math::SubtractionXMFLOAT3(predictionPos_, predictionPos_);
    //pos.y = 0.0f;
    //XMVECTOR vpos = XMLoadFloat3(&pos);	//ズレた位置
    float addRadius = malletRadius_ + pPack->GetRadius();
    //XMVECTOR vdir = XMLoadFloat3(&malletDir_);	//中心と中心の正しい距離
    //vdir = XMVector3Normalize(vdir);
    XMVECTOR vdir = XMLoadFloat3(&predictionDir_);
    vdir = XMVector3Normalize(vdir);

    vdir = vdir * addRadius;
    XMStoreFloat3(&pos, (vdir));

    enemyPosition_ = Math::AddXMFLOAT3(predictionPos_, pos);
    //transform_.position_ = predictionPos_;
    //1

    XMFLOAT3 sub = Math::FacingConversion(aim_, predictionDir_);//3

    //XMFLOAT3 malletdir = Math::FacingConversion(transform_.position_, predictionPos_);
    //malletDir_ = Math::FacingConversion(sub, predictionDir_);
    malletDir_ = Math::FacingConversion(sub, pos);

    //malletDir_ = Math::FacingConversion(sub, malletdir);

    //XMFLOAT3 sub = Math::SubtractionXMFLOAT3(transform_.position_,predictionPos_);
    //malletDir_ = Math::FacingConversion(aim_ ,sub);
    //malletDir_ = Math::FacingConversion(malletDir_,sub);
    //malletDir_ = sub;
    //transform_.position_.z = -transform_.position_.z;
    //transform_.position_.x = -transform_.position_.x;
    //transform_.position_ = Math::SubtractionXMFLOAT3(transform_.position_, pos);
}
