#include "GoalPoint.h"
#include "../Engine/Image.h"

//コンストラクタ
GoalPoint::GoalPoint(GameObject* parent)
	: GameObject(parent, "GoalPoint"),enemyPoint_(0),playerPoint_(0)
{
	for (short i = 0; i < sizeof(hPict_) / sizeof(short); i++)
	{
		hPict_[i] = -1;
	}
}

//初期化
void GoalPoint::Initialize()
{
	std::string name_ = "Assets\\Number";
	std::string file_ = ".png";
	for (int i = 0; i < (sizeof(hPict_)  / sizeof(short)) - 1; i++)
	{
		std::string fileName_ = name_ + std::to_string(i) + file_;
		hPict_[i] = Image::Load(fileName_);
		assert(hPict_[i] >= 0);
	}
	std::string fileName_ = name_ + file_;
	hPict_[sizeof(hPict_)] = Image::Load(fileName_);
	transform_.position_.y = 0.8f;
}

//更新
void GoalPoint::Update()
{
}

//描画
void GoalPoint::Draw()
{
	float posX_ = 0.45f;
	if (enemyPoint_ >= 10)
	{
		transform_.position_.x = posX_;
		Image::SetTransform(hPict_[enemyPoint_ / 10], transform_);
		Image::Draw(hPict_[enemyPoint_ / 10]);
		posX_ += 0.15f;
	}
	transform_.position_.x = posX_;
	Image::SetTransform(hPict_[enemyPoint_ % 10], transform_);
	Image::Draw(hPict_[enemyPoint_ % 10]);
	posX_ += 0.1f;

	transform_.position_.x = posX_;
	Image::SetTransform(hPict_[sizeof(hPict_)], transform_);
	Image::Draw(hPict_[sizeof(hPict_)]);
	posX_ += 0.1f;

	if (playerPoint_ >= 10)
	{
		transform_.position_.x = posX_;
		Image::SetTransform(hPict_[playerPoint_ / 10], transform_);
		Image::Draw(hPict_[playerPoint_ / 10]);
		posX_ += 0.15f;
	}
	transform_.position_.x = posX_;
	Image::SetTransform(hPict_[playerPoint_ % 10], transform_);
	Image::Draw(hPict_[playerPoint_ % 10]);
}

//開放
void GoalPoint::Release()
{
}

void GoalPoint::GoalEnemy()
{
	enemyPoint_++;
}

void GoalPoint::GoalPlayer()
{
	playerPoint_++;
}
