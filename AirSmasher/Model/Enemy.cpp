#include "Enemy.h"
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
    transform_.position_.z = 10.0f;
    speed_ = 1.0f;
}

//マレットの動き
void Enemy::MoveMallet()
{
  /*  if (isPut_)
    {
        transform_.position_.x -= 0.2;
    }
    else
    {
        transform_.position_.x += 0.2f;
    }*/
}

//マレットを台に置くかどうか
bool Enemy::IsPut()
{
    return true;
}
