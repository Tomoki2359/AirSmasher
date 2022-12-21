#include "LimitTime.h"
#include "../Engine/Image.h"
#include "../Engine/Time.h"

//�R���X�g���N�^
LimitTime::LimitTime(GameObject* parent)
	: GameObject(parent, "LimitTime"),timer_(180)
{
	for (short i = 0; i < 10; i++)
	{
		hPict_[i] = -1;
	}
}

//������
void LimitTime::Initialize()
{
	std::string name_ = "Assets\\Number";
	std::string file_ = ".png";
	for (int i = 0; i < 10; i++)
	{
		std::string fileName_ = name_ + std::to_string(i) + file_;
		hPict_[i] = Image::Load(fileName_);
		assert(hPict_[i] >= 0);
	}
	transform_.position_.y = 0.8f;
	Time::Reset();
}

//�X�V
void LimitTime::Update()
{
	timer_ = MAX_TIME - (int)Time::GetTime();
}

//�`��
void LimitTime::Draw()
{
	Transform trans = transform_;
	trans.position_.x = -0.8f;
	if (timer_ / 100 > 0)
	{
		Image::SetTransform(hPict_[timer_ / 100], trans);
		Image::Draw(hPict_[timer_ / 100]);

		trans.position_.x += 0.15f;
		Image::SetTransform(hPict_[(timer_ / 10) - 10], trans);
		Image::Draw(hPict_[(timer_ / 10) - 10]);


		trans.position_.x += 0.15f;
	}
	else if (timer_ / 10 > 0)
	{
		Image::SetTransform(hPict_[timer_ / 10], trans);
		Image::Draw(hPict_[timer_ / 10]);


		trans.position_.x += 0.15f;
	}
	Image::SetTransform(hPict_[timer_ % 10], trans);
	Image::Draw(hPict_[timer_ % 10]);
}

void LimitTime::Release()
{
}
