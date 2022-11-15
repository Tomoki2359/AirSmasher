#include "Enemy.h"
#include "../Engine/Math.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    : Mallet(parent, "Enemy")
{
}

//�J��
void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
}

void Enemy::SetInit()
{
    transform_.position_.z = 10.0f;
}

void Enemy::MoveMallet()
{
    if (isPut_)
    {
        transform_.position_.x -= 0.2;
    }
    else
    {
        transform_.position_.x += 0.2f;
    }
}

bool Enemy::IsPut()
{
    return true;
}
