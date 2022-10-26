#include "Camera.h"

namespace Camera
{
	//変数
	struct MultiCamera
	{
		XMVECTOR position_;	//カメラの位置（視点）
		XMVECTOR target_;	//見る位置（焦点）
		XMMATRIX viewMatrix_;	//ビュー行列
		XMMATRIX projMatrix_;	//プロジェクション行列
	};
	MultiCamera mCamera[2];
}

//初期化
void Camera::Initialize(int WINDOU_WIDTH,int WINDOU_HEIGHT)
{
	for (int i = 0; i < 2; i++)
	{
		mCamera[i].position_ = XMVectorSet(0, 3, -10, 0);	//カメラの位置
		mCamera[i].target_ = XMVectorSet(0, 0, 0, 0);	//カメラの焦点

		//プロジェクション行列
		mCamera[i].projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)WINDOU_WIDTH / (FLOAT)WINDOU_HEIGHT, 0.1f, 100.0f);
	}
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	for (int i = 0; i < 2; i++)
	{
		mCamera[i].viewMatrix_ = XMMatrixLookAtLH(mCamera[i].position_, mCamera[i].target_, XMVectorSet(0, 1, 0, 0));

	}
}

//位置を設定
void Camera::SetPosition(XMVECTOR position, int numCamera)
{
	mCamera[numCamera].position_ = position;
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target, int numCamera)
{
	mCamera[numCamera].target_ = target;
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix(int numCamera)
{
	return mCamera[numCamera].viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix(int numCamera)
{
	return mCamera[numCamera].projMatrix_;
}