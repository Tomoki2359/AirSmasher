#include "ResultPoint.h"
#include "../Option.h"
#include "../Engine/Image.h"

//�R���X�g���N�^
ResultPoint::ResultPoint(GameObject* parent)
	: GameObject(parent, "ResultPoint"), enemyPoint_(0), playerPoint_(0)
{
	for (short i = 0; i < 11; i++)
	{
		hPict_[i] = -1;
	}
}

//������
void ResultPoint::Initialize()
{
	std::string name_ = "Assets\\Number";
	std::string file_ = ".png";
	for (int i = 0; i < 10; i++)
	{
		std::string fileName_ = name_ + std::to_string(i) + file_;
		hPict_[i] = Image::Load(fileName_);
		assert(hPict_[i] >= 0);
	}
	std::string fileName_ = name_ + file_;
	hPict_[11] = Image::Load(fileName_);
	enemyPoint_ = Option::GetEnemyPoint();
	playerPoint_ = Option::GetPlayerPoint();
}

//�X�V
void ResultPoint::Update()
{
}

//�`��
void ResultPoint::Draw()
{
	float posX_ = -0.45f;
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
	posX_ += 0.1f;

	/*transform_.position_.x = posX_;
	Image::SetTransform(hPict_[11], transform_);
	Image::Draw(hPict_[11]);
	posX_ += 0.1f;*/

	posX_ = 0.45f;

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
}

//�J��
void ResultPoint::Release()
{
}

//void ResultPoint::SetPlayerPoint(int p)
//{
//}
//
//void ResultPoint::SetEnemyPoint(int p)
//{
//}
