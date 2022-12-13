#pragma once
#include "../Engine/GameObject.h"
class GoalPoint : public GameObject
{
	int enemyPoint_;
	int playerPoint_;
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
