#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/QuadrangleHit.h"
#include "Stage.h"
#include "Shadow.h"
//#include "Pack.h"

//class Pack;

//�����V�[�����Ǘ�����N���X
class Mallet : public GameObject
{
	int hModel_;
protected:
	Stage* pStage_;			//�X�e�[�W�̃|�C���^
	Shadow* pShadow_;			//�e�̃|�C���^
	CircleCollider* collision;  //�����蔻��
	QuadrangleHit* pQuadrangle;	//�����蔻��
	XMFLOAT3 malletDir_;			//����	
	XMFLOAT3 previousMalletPos_;	//�O�̃}���b�g�̈ʒu
	XMFLOAT2 stageScale_;
	float malletSpeed_;			//�}���b�g�̑��x
	float malletRadius_;	//���a
	float stageFront_;	//�n�ʂ̈ʒu
	float packFront_; //�p�b�N�̈ʒu
	int goalCount_;
	bool first_;
	bool isPut_;			//�}���b�g���e�[�u���ɂ��Ă��邩�ǂ���
	bool isSuppress_;		//�p�b�N��}���Ă��邩
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
	XMFLOAT3 GetDirection() { return XMFLOAT3{ malletDir_.x,0,malletDir_.z }; };

	//�}���b�g�̑O��̈ʒu
	//�߂�l�@�}���b�g�̑O�񂢂��ʒu
	XMFLOAT3 GetPreviousPosition() { return XMFLOAT3{ previousMalletPos_.x,0,previousMalletPos_.z }; };

	//�}���b�g�̓��������x
	//�߂�l�@�}���b�g�̑��x
	float GetSpeed() { return malletSpeed_; }

	//�}���b�g����ɂ��Ă��邩�ǂ���
	//�߂�l�@��ɂ��Ă���Ȃ�true
	bool GetPut() { return isPut_; };

	//�}�������Ԃ��ǂ���
	//�߂�l�@�p�b�N��}������Ȃ�true
	bool GetSuppress() { return isSuppress_; };

	//float GetFront() { return front_; };

	//float GetPackFront() { return packFront_; };

	float GetRadius() { return malletRadius_; };

	void SetSuppress(bool Sup) { isSuppress_ = Sup; };

	void SetGoal() { goalCount_ = 60; };

	/// <summary>
	/// �p�b�N�ɓ��������Ƃ����ɉ�����
	/// </summary>
	/// <param name="dir">����</param>
	void CrashPack(XMFLOAT3 dir);

	//�p�������}���b�g�̏�����
	virtual void SetInit() = 0;

	//�p�������}���b�g�̓����֌W
	virtual void MoveMallet() = 0;

	//�}���b�g��n�ʂɂ��Ă��邩�ǂ���
	virtual bool IsPut() = 0;
};