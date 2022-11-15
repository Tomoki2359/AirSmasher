#include "Mallet.h"
#include "../Engine/Model.h"
#include "Pack.h"
//#include "../Engine/Math.h"

//�R���X�g���N�^
Mallet::Mallet(GameObject* parent)
    : Mallet(parent, "Mallet")
{
}

Mallet::Mallet(GameObject* parent, std::string name)
    : GameObject(parent, name)
{
}

//������
void Mallet::Initialize()
{
    hModel_ = Model::Load("Assets\\Mallet.fbx");
    assert(hModel_ >= 0);
    SetInit();
    CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), 1.0f);
    AddCircleCollider(collision);
}

//�X�V
void Mallet::Update()
{
    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.start.y = 0;
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

    Stage* pStage = (Stage*)FindObject("Stage");
    int hModelStage = pStage->HandleModel();

    Model::RayCast(hModelStage, data); //���C�𔭎�

    if (IsPut())
    {
        //isPut_ = true;
        if (data.hit)
        {
            transform_.position_.y = -data.dist;
        }
    }
    else
    {
        transform_.position_.y = 3.0f;
    }
    MoveMallet();

    data.dir = XMFLOAT3{1.0,0,0};
    Model::SegmentRayCast(hModelStage, data);
    XMVECTOR vNormal = XMVector3Cross(XMLoadFloat3(&data.side1), XMLoadFloat3(&data.side2));
    XMFLOAT3 side;
    XMStoreFloat3(&side, vNormal);
    //�ǂɂԂ�����������]��
    if (side.x > 0)
    {
        isPut_ = true;
        transform_.position_.x = (int)transform_.position_.x - 0.2f;
    }

    if (side.x < 0)
    {
        isPut_ = false;
        transform_.position_.x = (int)transform_.position_.x + 0.2f;
    }

    data.start = transform_.position_;
    data.start.x = 0;
    data.dir = XMFLOAT3{ 1.0f,0.0f,0.0f };
    Model::SegmentRayCast(hModelStage, data);
    vNormal = XMVector3Cross(XMLoadFloat3(&data.side1), XMLoadFloat3(&data.side2));
    XMStoreFloat3(&side, vNormal);
    if (side.z > 0)
    {
        transform_.position_.z = (int)transform_.position_.z - 0.2f;
    }

    if (side.z < 0)
    {
        transform_.position_.z = (int)transform_.position_.z + 0.2f;
    }
}

//�`��
void Mallet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Mallet::Release()
{
}

void Mallet::OnCollision(GameObject* pTarget)
{
    //RayCastData data;
    //data.start = transform_.position_;   //���C�̔��ˈʒu
    //data.start.y = 0;
    //data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    ////�p�b�N�ɐG��Ă�Ƃ�
    //if (pTarget->GetObjectName() == "Pack")
    //{
    //    Pack* pPack_ = (Pack*)FindObject("Pack");
    //    int hModelPack = pPack_->HandleModelPack();
    //    Model::RayCast(hModelPack, data); //���C�𔭎�

    //    if (data.hit)
    //    {
    //        transform_.position_.y = -data.dist;
    //    }
    //}
    //else
    //{
    //    Stage* pStage = (Stage*)FindObject("Stage");
    //    int hModelStage = pStage->HandleModel();

    //    Model::RayCast(hModelStage, data); //���C�𔭎�

    //    if (data.hit)
    //    {
    //        transform_.position_.y = -data.dist;
    //    }
    //}
}