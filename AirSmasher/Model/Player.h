#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//�����V�[�����Ǘ�����N���X
class Player : public GameObject
{
	int hModel_;
	XMFLOAT3 mousePos;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};