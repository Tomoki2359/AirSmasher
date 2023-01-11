#include "ResultPlayer.h"
#include "../Option.h"
#include "../Engine/Image.h"
//�R���X�g���N�^
ResultPlayer::ResultPlayer(GameObject* parent)
	: GameObject(parent, "ResultPlayer"),hPict_(-1)
{
}

//������
void ResultPlayer::Initialize()
{
	int pPoint = Option::GetPlayerPoint();
	int ePoint = Option::GetEnemyPoint();
	if (pPoint > ePoint)
	{
		hPict_ = Image::Load(L"Assets\\Winner.png");
	}
	else if (pPoint < ePoint)
	{
		hPict_ = Image::Load(L"Assets\\Loser.png");
	}
	else
	{
		hPict_ = Image::Load(L"Assets\\Draw.png");
	}
	transform_.position_.y = 0.5f;
}

//�X�V
void ResultPlayer::Update()
{
}

//�`��
void ResultPlayer::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void ResultPlayer::Release()
{
}