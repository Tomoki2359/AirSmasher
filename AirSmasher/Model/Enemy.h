#pragma once
#include "Mallet.h"

//�����V�[�����Ǘ�����N���X
class Enemy : public Mallet
{
	int countFuture_;
	XMFLOAT3 enemyPosition_;
	bool isPrediction_;
#ifdef _DEBUG
	bool isStopMove;
#endif
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);

	//�J��
	void Release() override;

	//�����ɓ�������
//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;

	void OffCollision(GameObject* pTarget) override;

	void SetInit() override;

	void MoveMallet() override;

	bool IsPut() override;
	
	//��������
	void AutoDir();
};