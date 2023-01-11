#include "LimitTime.h"
#include "../Option.h"
#include "../Image/GoalPoint.h"
#include "../Engine/Image.h"
#include "../Engine/Time.h"
#include "../Engine/SceneManager.h"

//�R���X�g���N�^
LimitTime::LimitTime(GameObject* parent)
	: GameObject(parent, "LimitTime"),timer_(180), MAX_TIME(180)
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
#ifdef _DEBUG
	static int changeTime = 0;
	//10�b��������
	if (Input::IsKeyDown(DIK_4))
	{
		changeTime -= 10;
	}
	//10�b�x������
	if (Input::IsKeyDown(DIK_5))
	{
		changeTime += 10;
	}
	timer_ = (MAX_TIME + changeTime) - (int)Time::GetTime();
#endif
	if (timer_ <= 0)
	{
		GoalPoint* pGoal = (GoalPoint*)FindObject("GoalPoint");
		assert(pGoal != nullptr);

		Option::SetEnemyPoint(pGoal->GetEnemyPoint());
		Option::SetPlayerPoint(pGoal->GetPlayerPoint());

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
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