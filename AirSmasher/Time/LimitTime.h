#pragma once
#include "../Engine/GameObject.h"

class LimitTime : public GameObject
{
	short hPict_[10];
	const int MAX_TIME;
	int timer_;
public:
	//�R���X�g���N�^
//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	LimitTime(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};