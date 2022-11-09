#include "Transform.h"

Transform::Transform() :
    pTransform_(nullptr),
    matTranslate_(XMMatrixIdentity()),
    matRotate_(XMMatrixIdentity()),
    matScale_(XMMatrixIdentity()),
    position_(XMFLOAT3(0, 0, 0)),
    rotate_(XMFLOAT3(0, 0, 0)),
    scale_(XMFLOAT3(1, 1, 1))
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //ˆÚ“®s—ñ
    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    //‰ñ“]s—ñ
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
    rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
    matRotate_ = rotateZ * rotateX * rotateY;

    //Šg‘åk¬s—ñ
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    Calclation();
    if (pTransform_)    //e‚ª‚¢‚éê‡
    {
        return matScale_ * matRotate_ * matTranslate_ * pTransform_->GetWorldMatrix();
    }
    return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
    return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}

XMFLOAT3 Transform::AddXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x + f2.x,f1.y + f2.y,f1.z + f2.z);
}

XMFLOAT3 Transform::SubXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
}

XMFLOAT3 Transform::MultiplicationXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x * f2.x, f1.y * f2.y, f1.z * f2.z);
}
