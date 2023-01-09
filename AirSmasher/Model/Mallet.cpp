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
    : GameObject(parent, name), isPut_(false),malletRadius_(1.0f),isSuppress_(false),first_(true)
    ,isGoal_(false),goalCount_(0)
{
}

//������
void Mallet::Initialize()
{
    hModel_ = Model::Load("Assets\\Mallet.fbx");
    assert(hModel_ >= 0);
    SetInit();
    collision = new CircleCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), malletRadius_,0.0f);
    AddCircleCollider(collision);
    Instantiate<Shadow>(this);
    stageScale_ = { 1.0f,1.0f };
    pQuadrangle = new QuadrangleHit();
    AddSquareBox(pQuadrangle);
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

        stageScale_.x = pStage->GetScaleX();
        stageScale_.y = pStage->GetScaleZ();

        Pack* pPack_ = (Pack*)FindObject("Pack");
        int hModelPack = pPack_->HandleModelPack();

        data.start = pPack_->GetPosition();
        data.start.y = 3;
        Model::RayCast(hModelStage, data); //���C�𔭎�

        packFront_ = -data.dist;
    }
    //�O��̈ʒu�̎擾
    previousMalletPos_ = transform_.position_;

    //�S�[��������
    if (!isGoal_)
    {
        if (IsPut())
        {
            isPut_ = true;
            transform_.position_.y = stageFront_;
        }
        else
        {
            isPut_ = false;
            transform_.position_.y = 3.0f;
        }

        //�e�}���b�g�̓���
        MoveMallet();

        //���̕ǂ̐ݒ�
        if (transform_.position_.x >= 5 * stageScale_.x + 1.0f)
        {
            transform_.position_.x = 5 * stageScale_.x + 0.25f;
        }
        else if (transform_.position_.x <= -5 * stageScale_.x - 1.0f)
        {
            transform_.position_.x = -5 * stageScale_.x - 0.25f;
        }

        //�ő呬�x�̐ݒ�
        if (malletSpeed_ >= 2.5f)
        {
            malletSpeed_ = 2.5f;
        }

        pQuadrangle->CreateSquar(transform_.position_, previousMalletPos_, malletRadius_, malletDir_);
    }
    else
    {
        //�S�[���������̏���
        transform_.position_.y = 3.0f;
        if (--goalCount_ <= 0)
        {
            isGoal_ = false;
            if (IsPut())
            {
                isSuppress_ = true;
            }
            //goalCount_ = 0;
        }
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