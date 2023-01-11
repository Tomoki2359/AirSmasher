#include "ResultPlayer.h"
#include "../Option.h"
#include "../Engine/Image.h"
//コンストラクタ
ResultPlayer::ResultPlayer(GameObject* parent)
	: GameObject(parent, "ResultPlayer"),hPict_(-1)
{
}

//初期化
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

//更新
void ResultPlayer::Update()
{
}

//描画
void ResultPlayer::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void ResultPlayer::Release()
{
}