#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//�����V�[�����Ǘ�����N���X
class Mallet : public GameObject
{
protected:
	int hModel_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mallet(GameObject* parent);

	Mallet(GameObject* parent,std::string name);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};