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
	bool IsKey(int keyCode);				//�L�[�������Ă���
	bool IsKeyDown(int keyCode);			//�L�[����������
	bool IsKeyUp(int keyCode);				//�L�[�𗣂�����
	bool IsKeyUpDown(int keyCode);			//�L�[���������藣������
	bool IsMouce(int mouceCode);			//�}�E�X�������Ă���
	bool IsMouceDown(int mouceCode);		//�}�E�X����������
	bool IsMouceUp(int mouceCode);			//�}�E�X�𗣂�����
	bool IsMouceUpDown(int mouceCode);		//�}�E�X���������藣������
	XMFLOAT3 GetMousePosition();			//�}�E�X�̈ʒu
	void SetMousePosition(int x, int y);	//�}�E�X�̈ʒu���擾
	bool IsController(int controllerCode, int controllerID = 0);		//�R���g���[���������Ă���
	bool IsControllerDown(int controllerCode, int controllerID = 0);	//�R���g���[������������
	bool IsControllerUp(int controllerCode, int controllerID = 0);		//�R���g���[���𗣂�����
	bool IsControllerUpDown(int controllerCode, int controllerID = 0);	//�R���g���[�����������藣������
	XMFLOAT3 GetPadStickL(int controllerID = 0);	//�R���g���[�������ɉ����Ă���
	XMFLOAT3 GetPadStickR(int controllerID = 0);	//�R���g���[�����E�ɉ����Ă���
	void Release();
};