#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player")
{
}

//������
void Player::Initialize()
{
	hModel_ = Model::Load("Assets\\Mallet.fbx");
	assert(hModel_ >= 0);
	transform_.position_.z = -13.0f;
	Camera::SetPosition(XMVectorSet(0, 10, -30, 0));
	Camera::SetTarget(XMVectorSet(0, 0, 5, 0));
	//mousePos = Input::GetMousePosition();
}

//�X�V
void Player::Update()
{
	XMFLOAT3 mousePosNow = Input::GetMousePosition();

	//�r���[�|�[�g�s��
	float w = (float)Direct3D::scrWidth / 2.0f;
	float h = (float)Direct3D::scrHeight / 2.0f;
	XMMATRIX vp = {
		w, 0,0,0,
		0,-h,0,0,
		0, 0,1,0,
		w, h,0,1
	};

	//�e�s��̋t�s��
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMVECTOR vMousePos = XMLoadFloat3(&mousePos);
	XMVECTOR vMousePosNow = XMLoadFloat3(&mousePosNow);
	//vMousePos = XMVector3TransformCoord(vMousePos, invVP * invPrj * invView);
	vMousePosNow = XMVector3TransformCoord(vMousePosNow, invVP * invPrj * invView);
	XMStoreFloat3(&mousePos, vMousePos);
	XMStoreFloat3(&mousePosNow, vMousePosNow);
	transform_.position_.x = mousePosNow.x;
	//transform_.position_.y = mousePosNow.y;
	//transform_.position_.z = mousePosNow.z;

	//mousePos = mousePosNow;
}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}