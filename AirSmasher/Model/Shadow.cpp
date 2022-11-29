#include "Shadow.h"
#include "../Engine/Model.h"
//�R���X�g���N�^
Shadow::Shadow(GameObject* parent)
	: GameObject(parent, "Shadow"), hModel_(-1)
{
}

//������
void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets\\Shadow.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Shadow::Update()
{
	//RayCastData data;
	//data.start = transform_.position_;   //���C�̔��ˈʒu
	//data.start.y = 0;
	//data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

	//Stage* pStage = (Stage*)FindObject("Stage");
	//int hModelStage = pStage->HandleModelStage();

	//Model::RayCast(hModelStage, data); //���C�𔭎�
	//transform_.position_.y = -data.dist;
}

//�`��
void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Shadow::Release()
{
}