#include "ResultScene.h"
#include "Image/ResultPoint.h"
#include "Image/ResultPlayer.h"
//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//������
void ResultScene::Initialize()
{
	Instantiate<ResultPoint>(this);
	Instantiate<ResultPlayer>(this);
}

//�X�V
void ResultScene::Update()
{
}

//�`��
void ResultScene::Draw()
{
}

//�J��
void ResultScene::Release()
{
}