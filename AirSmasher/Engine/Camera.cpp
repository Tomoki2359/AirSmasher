#include "Camera.h"

namespace Camera
{
	//�ϐ�
	struct MultiCamera
	{
		XMVECTOR position_;	//�J�����̈ʒu�i���_�j
		XMVECTOR target_;	//����ʒu�i�œ_�j
		XMMATRIX viewMatrix_;	//�r���[�s��
		XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
	};
	MultiCamera mCamera[2];
}

//������
void Camera::Initialize(int WINDOU_WIDTH,int WINDOU_HEIGHT)
{
	for (int i = 0; i < 2; i++)
	{
		mCamera[i].position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
		mCamera[i].target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

		//�v���W�F�N�V�����s��
		mCamera[i].projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)WINDOU_WIDTH / (FLOAT)WINDOU_HEIGHT, 0.1f, 100.0f);
	}
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	for (int i = 0; i < 2; i++)
	{
		mCamera[i].viewMatrix_ = XMMatrixLookAtLH(mCamera[i].position_, mCamera[i].target_, XMVectorSet(0, 1, 0, 0));

	}
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position, int numCamera)
{
	mCamera[numCamera].position_ = position;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target, int numCamera)
{
	mCamera[numCamera].target_ = target;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix(int numCamera)
{
	return mCamera[numCamera].viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix(int numCamera)
{
	return mCamera[numCamera].projMatrix_;
}