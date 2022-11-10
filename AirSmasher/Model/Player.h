#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//�����V�[�����Ǘ�����N���X
class Player : public GameObject
{
	int hModel_;
	XMFLOAT3 mousePos;
	XMFLOAT3 dir_;
	XMFLOAT3 previousPos_;	//�O�̈ʒu
	float speed_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	XMFLOAT3 GetDirection() { return dir_; };

	XMFLOAT3 GetPreviousPosition() { return previousPos_; };

	float GetSpeed() { return speed_; }
};