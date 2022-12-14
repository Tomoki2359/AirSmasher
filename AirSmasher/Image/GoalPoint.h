#pragma once
#include "../Engine/GameObject.h"
class GoalPoint : public GameObject
{
	short enemyPoint_;
	short playerPoint_;
	short hPict_[10];
public:
	//�R���X�g���N�^
//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GoalPoint(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void GoalEnemy();
	void GoalPlayer();
};

