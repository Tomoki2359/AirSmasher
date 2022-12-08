#pragma once
#include "Mallet.h"

//�����V�[�����Ǘ�����N���X
class Enemy : public Mallet
{
	int count_;
	bool isPrediction_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);

	//�J��
	void Release() override;

	//�����ɓ�������
	//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;

	void SetInit() override;

	void MoveMallet() override;

	bool IsPut() override;
	
	void AutoDir();
};