#include "Player.h"
#include "../Engine/Model.h"
//コンストラクタ
Player::Player(GameObject* parent)
	: Mallet(parent, "Player")
{
}

//初期化
void Player::Initialize()
{
	transform_.position_.z = -5.0f;
}

//更新
void Player::Update()
{
}

//描画
void Player::Draw()
{
}

//開放
void Player::Release()
{
}