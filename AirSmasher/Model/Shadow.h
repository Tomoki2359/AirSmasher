#pragma once
#include"../Engine/GameObject.h"
#include"Stage.h"
//�����V�[�����Ǘ�����N���X
class Shadow : public GameObject
{
	int hModel_;
	Stage* pStage_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Shadow(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};