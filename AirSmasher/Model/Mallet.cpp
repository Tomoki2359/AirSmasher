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
    : GameObject(parent, name), isPut_(false),radius_(1.0f),isSuppress_(false),first_(true)
    ,isGoal_(false),count_(0)
{
}

//������
void Mallet::Initialize()
{
    hModel_ = Model::Load("Assets\\Mallet.fbx");
    assert(hModel_ >= 0);
    SetInit();
    collision = new CircleCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), radius_,0.0f);
    AddCircleCollider(collision);
    Instantiate<Shadow>(this);
    malletSquar_ = { {0,0},{0,0 }, { 0,0},{0,0 }};
    scale_ = { 1.0f,1.0f };
}

//�X�V
void Mallet::Update()
{
    //��񂾂��s����������
    if (first_)
    {
        RayCastData data;
        data.start = transform_.position_;   //���C�̔��ˈʒu
        data.start.y = 0;
        data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

        Stage* pStage = (Stage*)FindObject("Stage");
        int hModelStage = pStage->HandleModelStage();

        Model::RayCast(hModelStage, data); //���C�𔭎�

        scale_.x = pStage->GetScaleX();
        scale_.y = pStage->GetScaleZ();

        Pack* pPack_ = (Pack*)FindObject("Pack");
        int hModelPack = pPack_->HandleModelPack();

        data.start = pPack_->GetPosition();
        data.start.y = 3;
        Model::RayCast(hModelStage, data); //���C�𔭎�

        packFront_ = -data.dist;
    }
    //�O��̈ʒu�̎擾
    previousMalletPos_ = transform_.position_;
    if (!isGoal_)
    {
        if (IsPut())
        {
            isPut_ = true;
            transform_.position_.y = front_;
        }
        else
        {
            isPut_ = false;
            transform_.position_.y = 3.0f;
        }

        //�e�}���b�g�̓���
        MoveMallet();

        //���̕ǂ̐ݒ�
        if (transform_.position_.x >= 5 * scale_.x + 1.0f)
        {
            transform_.position_.x = 5 * scale_.x + 0.25f;
        }
        else if (transform_.position_.x <= -5 * scale_.x - 1.0f)
        {
            transform_.position_.x = -5 * scale_.x - 0.25f;
        }

        //�ő呬�x�̐ݒ�
        if (speed_ >= 2.5f)
        {
            speed_ = 2.5f;
        }

        QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_, &malletSquar_, radius_, dir_);
    }
    else
    {
        transform_.position_.y = 3.0f;
        if (count_ >= 60)
        {
            isGoal_ = false;
            if (IsPut())
            {
                isSuppress_ = true;
            }
            count_ = 0;
        }
        count_++;
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
}