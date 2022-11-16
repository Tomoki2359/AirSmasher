#pragma once
#include"../Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
//�����V�[�����Ǘ�����N���X
class Pack : public GameObject
{
	int hModel_;
	XMFLOAT3 pos_;
	XMFLOAT3 dir_;
	float speed_;
	Player* pPlayer_;
	Enemy* pEnemy_;
	Stage* pStage;
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

	//�}���b�g�ɓ������Ă��鏈��
	void IsMallet(Mallet* pMallet);

	//�ǂɓ������Ă��鏈��
	void IsWall();
	
	//�S�[�����Ă��鏈��
	void IsGoal();

	//���f���ԍ�
	int HandleModelPack() { return hModel_; };
};