#include "Player.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Mallet(parent, "Player")
{
}

//������
void Player::Initialize()
{
	transform_.position_.z = -5.0f;
}

//�X�V
void Player::Update()
{
}

//�`��
void Player::Draw()
{
}

//�J��
void Player::Release()
{
}