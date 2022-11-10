#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "Stage.h"
#include "../Engine/Math.h"

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
	//transform_.position_.y = 1.0f;
	Camera::SetPosition(XMVectorSet(0, 15, -30, 0));
	Camera::SetTarget(XMVectorSet(0, 0, 5, 0));
    //Camera::SetPosition(XMVectorSet(0, 15, -20, 0));
    //Camera::SetTarget(XMVectorSet(0, 0, -10, 0));
	mousePos = Input::GetMousePosition();
    CircleCollider* collision = new CircleCollider(XMFLOAT3(0, 0.0f, 0), 1.0f);
    AddCircleCollider(collision);
}

//更新
void Player::Update()
{
    previousPos_ = transform_.position_;
    //Stage* pStage = (Stage*)FindObject("Stage");
    //int hModelStage = pStage->HandleModel();

    //移動処理
    float w = (float)Direct3D::scrWidth / 2.0f;
    float h = (float)Direct3D::scrHeight / 2.0f;

    //XMFLOAT3 mousePosNow = XMFLOAT3{ (Input::GetMousePosition().x - w), Input::GetMousePosition().z, Input::GetMousePosition().y - h });
    XMFLOAT3 mousePosNow = Math::DivisionXMFLOAT3(XMFLOAT3{ (Input::GetMousePosition().x - w), Input::GetMousePosition().z, Input::GetMousePosition().y - h }, 20);

    /* transform_.position_.x += (mousePosNow.x - mousePos.x) / 20;
     transform_.position_.z -= (mousePosNow.z - mousePos.z) / 20;*/
    transform_.position_.x += (mousePosNow.x - mousePos.x);
    transform_.position_.z -= (mousePosNow.z - mousePos.z);
    dir_ = Math::SubtractionXMFLOAT3(mousePosNow, mousePos);

    XMVECTOR vDir = XMLoadFloat3(&dir_);
    vDir = XMVector3Length(vDir);
    speed_ = XMVectorGetX(vDir);
    XMStoreFloat3(&dir_, vDir);

    mousePos = mousePosNow;

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