#include "Shadow.h"
#include "../Engine/Model.h"
//コンストラクタ
Shadow::Shadow(GameObject* parent)
	: GameObject(parent, "Shadow"), hModel_(-1)
{
}

//初期化
void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets\\Shadow.fbx");
	assert(hModel_ >= 0);
}

//更新
void Shadow::Update()
{
	//RayCastData data;
	//data.start = transform_.position_;   //レイの発射位置
	//data.start.y = 0;
	//data.dir = XMFLOAT3(0, -1, 0);       //レイの方向

	//Stage* pStage = (Stage*)FindObject("Stage");
	//int hModelStage = pStage->HandleModelStage();

	//Model::RayCast(hModelStage, data); //レイを発射
	//transform_.position_.y = -data.dist;
}

//描画
void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Shadow::Release()
{
}