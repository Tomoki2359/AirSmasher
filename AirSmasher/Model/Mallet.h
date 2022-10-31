#pragma once
#include"../Engine/GameObject.h"
#include "../Engine/SceneManager.h"
//■■シーンを管理するクラス
class Mallet : public GameObject
{
protected:
	int hModel_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mallet(GameObject* parent);

	Mallet(GameObject* parent,std::string name);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};