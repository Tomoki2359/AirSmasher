#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize(int WINDOU_WIDTH, int WINDOU_HEIGHT);

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position, int numCamera);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target, int numCamera);

	//ビュー行列を取得
	XMMATRIX GetViewMatrix(int numCamera);

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix(int numCamera);
};