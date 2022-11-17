#pragma once
#include"../Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "../QuadrangleHit.h"

//�����V�[�����Ǘ�����N���X
class Pack : public GameObject
{
	int hModel_;
	//XMFLOAT3 pos_;
	XMFLOAT3 previousMalletPos_;	//�O�̃p�b�N�̈ʒu
	XMFLOAT3 dir_;
	float speed_;
	Player* pPlayer_;
	Enemy* pEnemy_;
	Stage* pStage;
	SquareBox packSquar_;
	float radius_;
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

	//�ǂɓ������Ă��邩����
	void IsWall();
	
	//�S�[�����Ă��邩����
	void IsGoal();

	//�}���b�g�ɓ������Ă��邩����
	void IsMallet();

	//���f���ԍ�
	int HandleModelPack() { return hModel_; };
};