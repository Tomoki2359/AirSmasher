#include "GoalPoint.h"

//�R���X�g���N�^
GoalPoint::GoalPoint(GameObject* parent)
	: GameObject(parent, "GoalPoint")
{
}

//������
void GoalPoint::Initialize()
{
}

//�X�V
void GoalPoint::Update()
{
}

//�`��
void GoalPoint::Draw()
{
}

//�J��
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
