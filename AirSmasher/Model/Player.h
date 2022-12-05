#pragma once
#include "Mallet.h"

//�����V�[�����Ǘ�����N���X
class Player : public Mallet
{
	XMFLOAT3 mousePos;
	bool isCamera_;		//�J�����̎��_�ύX
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//�J��
	void Release() override;

	//�����ɓ�������
	//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;

	void OffCollision(GameObject* pTarget) override;

	void SetInit() override;

	void MoveMallet() override;

	bool IsPut() override;
	//XMFLOAT3 GetDirection() { return dir_; };

	//XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	//XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };

	//XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousPos_.x,0,previousPos_.z }; };

	//float GetSpeed() { return speed_; }
};