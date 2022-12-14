#include "Player.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "../Engine/Math.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    : Mallet(parent, "Player")
{
    malletSquar_ = { {0,0},{0,0 }, { 0,0},{0,0 }
};
}

//�J��
void Player::Release()
{
}

//���������Ƃ��̔���
void Player::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        if (isSuppress_)
        {
            transform_.position_.y = 0.25f;
        }
    }
}

void Player::OffCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Pack")
    {
        isSuppress_ = false;
    }
}

//������
void Player::SetInit()
{
    transform_.position_.z = -20.0f;
    Camera::SetPosition(XMVectorSet(0, 57, -45, 0));
    Camera::SetTarget(XMVectorSet(0, -15, 3, 0));
    mousePos = Input::GetMousePosition();
    isCamera_ = true;
    speed_ = 1.0f;
}

//�}���b�g�̓���
void Player::MoveMallet()
{
    //�ړ�����
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;

    XMFLOAT3 mousePosNow = Math::DivisionXMFLOAT3(XMFLOAT3{ (Input::GetMouseMove().x), Input::GetMouseMove().z, Input::GetMouseMove().y }, 19);

    //�����A�X�s�[�h�̐ݒ�
    transform_.position_.x += (mousePosNow.x);// - mousePos.x);
    transform_.position_.z -= (mousePosNow.z); // -mousePos.z);
    dir_ = Math::SubtractionXMFLOAT3(mousePosNow, mousePos);

    XMVECTOR vDir = XMLoadFloat3(&dir_);
    vDir = XMVector3Length(vDir);
    //speed_ = XMVectorGetX(vDir);
    XMStoreFloat3(&dir_, vDir);

    mousePos = mousePosNow;

    if (Input::IsMouceDown(1))
    {
        if (!isCamera_)
        {
            isCamera_ = true;
        }
        else
        {
            isCamera_ = false;
        }
       
    }

    //�J�����̈ʒu�ݒ�
    if (isCamera_)
    {
        Camera::SetPosition(XMVectorSet(0, 57, -45, 0));
        Camera::SetTarget(XMVectorSet(0, -15, 3, 0));
    }
    else
    {
        Camera::SetPosition(XMVectorSet(0, 15, -60 , 0));
        Camera::SetTarget(XMVectorSet(0, 0, 10, 0));
    }

    //�ǂ���o�Ȃ��悤��
    if (transform_.position_.z >= 0)
    {
        transform_.position_.z = 0;
    }
    else if (transform_.position_.z <= -9.5f * scale_.y)
    {
        transform_.position_.z = -9.5f * scale_.y + 0.125f;
    }

    QuadrangleHit::CreateSquar(transform_.position_, previousMalletPos_, &malletSquar_, radius_, dir_);
}

//���u�����ǂ���
bool Player::IsPut()
{
    if (Input::IsMouceDown(0))
    {
        isSuppress_ = true;
    }
    if (Input::IsMouce(0))
    {
        collision->SetDimension(0.0f);
        return true;
    }
    collision->SetDimension(1.0f);
    return false;
}
