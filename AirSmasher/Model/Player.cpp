#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "Stage.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player")
{
}

//初期化
void Player::Initialize()
{
	hModel_ = Model::Load("Assets\\Mallet.fbx");
	assert(hModel_ >= 0);
	//transform_.position_.z = -13.0f;
	transform_.position_.y = 1.0f;
	Camera::SetPosition(XMVectorSet(0, 15, -30, 0));
	Camera::SetTarget(XMVectorSet(0, 0, 5, 0));
    //Camera::SetPosition(XMVectorSet(0, 15, -20, 0));
    //Camera::SetTarget(XMVectorSet(0, 0, -10, 0));
	mousePos = Input::GetMousePosition();
    CylinderCollider* collision = new CylinderCollider(XMFLOAT3(0, 0.0f, 0), 0.2f,0.2f);
    AddCylCollider(collision);

}

//更新
void Player::Update()
{

	Stage* pStage = (Stage*)FindObject("Stage");
	int hModelStage = pStage->HandleModel();

    ////ビューポート行列
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;

    XMFLOAT3 mousePosNow = XMFLOAT3{ Input::GetMousePosition().x - w, Input::GetMousePosition().y - h, Input::GetMousePosition().z };

    transform_.position_.x += (mousePosNow.x - mousePos.x) / 20;
    transform_.position_.z += -(mousePosNow.y - mousePos.y) / 20;
    mousePos = mousePosNow;

    

    if (Input::IsMouceDown(0))
    {
        int o = 0;
    }

}

//描画
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}