#pragma once
#include "../Engine/GameObject.h"
class ResultPoint : public GameObject
{
	short enemyPoint_;
	short playerPoint_;
	short hPict_[11];
public:
	//�R���X�g���N�^
//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultPoint(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//void SetPlayerPoint(int p);
	//void SetEnemyPoint(int p);
};