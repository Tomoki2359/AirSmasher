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

//������
void Enemy::SetInit()
{
    transform_.position_.z = 10.0f;
}

//�}���b�g�̓���
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

//�}���b�g���ɒu�����ǂ���
bool Enemy::IsPut()
{
    return true;
}
