#include "PlayScene.h"
#include "Model/Stage.h"
#include "Model/Player.h"
#include "Model/Enemy.h"
#include "Model/Pack.h"
#include "Image/GoalPoint.h"
//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Pack>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<GoalPoint>(this);
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}