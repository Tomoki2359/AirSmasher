#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
#include "Player.h"
//�����V�[�����Ǘ�����N���X
class Pack : public GameObject
{
	int hModel_;
	XMFLOAT3 pos_;
	XMFLOAT3 dir_;
	float speed_;
	Player* pPlayer_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Pack(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�����ɓ�������
	//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;

	bool IsWall();
};