#pragma once
#include"../Engine/GameObject.h"
#include "Stage.h"
//�����V�[�����Ǘ�����N���X
class Mallet : public GameObject
{
	int hModel_;
protected:
	XMFLOAT3 dir_;
	XMFLOAT3 previousPos_;	//�O�̈ʒu
	float speed_;
	bool isPut_;	//�}���b�g���e�[�u���ɂ��Ă��邩�ǂ���
	Stage* pStage_;
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

	XMFLOAT3 GetDirection() { return XMFLOAT3{ dir_.x,0,dir_.z }; };

	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousPos_.x,0,previousPos_.z }; };

	float GetSpeed() { return speed_; }

	virtual void SetInit() = 0;

	virtual void MoveMallet() = 0;

	virtual bool IsPut() = 0;
};