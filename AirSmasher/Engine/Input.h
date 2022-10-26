#pragma once

#include <dInput.h>
#include < DirectXMath.h >
#include "XInput.h"
#pragma comment(lib,"Xinput.lib")

using namespace DirectX;

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	HRESULT Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);				//キーを押してたら
	bool IsKeyDown(int keyCode);			//キーを押したら
	bool IsKeyUp(int keyCode);				//キーを離したら
	bool IsKeyUpDown(int keyCode);			//キーを押したり離したら
	bool IsMouce(int mouceCode);			//マウスを押してたら
	bool IsMouceDown(int mouceCode);		//マウスを押したら
	bool IsMouceUp(int mouceCode);			//マウスを離したら
	bool IsMouceUpDown(int mouceCode);		//マウスを押したり離したら
	XMFLOAT3 GetMousePosition();			//マウスの位置
	void SetMousePosition(int x, int y);	//マウスの位置を取得
	bool IsController(int controllerCode, int controllerID = 0);		//コントローラを押してたら
	bool IsControllerDown(int controllerCode, int controllerID = 0);	//コントローラを押したら
	bool IsControllerUp(int controllerCode, int controllerID = 0);		//コントローラを離したら
	bool IsControllerUpDown(int controllerCode, int controllerID = 0);	//コントローラを押したり離したら
	XMFLOAT3 GetPadStickL(int controllerID = 0);	//コントローラを左に押してたら
	XMFLOAT3 GetPadStickR(int controllerID = 0);	//コントローラを右に押してたら
	void Release();
};