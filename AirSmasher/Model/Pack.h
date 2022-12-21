#pragma once
#include"../Engine/GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "../Engine/QuadrangleHit.h"
#include "../Image/GoalPoint.h"

//�����V�[�����Ǘ�����N���X
class Pack : public GameObject
{
	//�|�C���^
	Player* pPlayer_;
	Enemy* pEnemy_;
	Stage* pStage;
	GoalPoint* pGoal_;
	CircleCollider* collision;		//�����蔻��
	QuadrangleHit* pQuadrangle;	//�����蔻��
	
	//XMFLOAT3 pos_;
	XMFLOAT3 previousPackPos_;	//�O�̃p�b�N�̈ʒu
	XMFLOAT3 dir_;	//����	
	float speed_;	//���x
	float radius_;	//���a
	int hModel_;
	bool isGool_;	//�S�[��������
	bool ismallet_;	//�v���C���[��true
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
	bool IsGoal();

	float GetRadius() { return radius_; };

	float GetSpeed() { return speed_; };

	XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };

	//�}���b�g�ɓ������Ă��邩����
	//void IsMallet();

	//���f���ԍ�
	int HandleModelPack() { return hModel_; };
};