#pragma once
#include"../Engine/GameObject.h"
#include "Stage.h"


//�����V�[�����Ǘ�����N���X
class Mallet : public GameObject
{
	int hModel_;
protected:
	XMFLOAT3 dir_;			//����	
	XMFLOAT3 previousMalletPos_;	//�O�̃}���b�g�̈ʒu
	float speed_;			//�}���b�g�̑��x
	bool isPut_;			//�}���b�g���e�[�u���ɂ��Ă��邩�ǂ���
	Stage* pStage_;			//�X�e�[�W�̃|�C���^
	//SquareBox malletSquar_;	//�O��ƍ��œ������Ă��邩�l�p�`
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mallet(GameObject* parent);

	Mallet(GameObject* parent, std::string name);

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

	//XMFLOAT3 GetDirection() { return dir_; };

	//XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	//�����̃Q�b�^�[
	//�߂�l �}���b�g�̈ړ��������
	XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };
	
	//�}���b�g�̑O��̈ʒu
	//�߂�l�@�}���b�g�̑O�񂢂��ʒu
	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousMalletPos_.x,0,previousMalletPos_.z }; };

	//�}���b�g�̓��������x
	//�߂�l�@�}���b�g�̑��x
	float GetSpeed() { return speed_; }

	//�}���b�g����ɂ��Ă��邩�ǂ���
	//�߂�l�@��ɂ��Ă���Ȃ�true
	bool GetPut() { return isPut_; };

	//�p�������}���b�g�̏�����
	virtual void SetInit() = 0;

	//�p�������}���b�g�̓����֌W
	virtual void MoveMallet() = 0;

	//�}���b�g��n�ʂɂ��Ă��邩�ǂ���
	virtual bool IsPut() = 0;
};