#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

namespace Model
{
	struct MODEL
	{
		Fbx* pFbx;
		Transform TransformModel;
		std::string FileModel;
		float alpha_;
		XMFLOAT3 color_;
		MODEL() : pFbx(nullptr),
			FileModel(""),
			alpha_(1),
			color_(XMFLOAT3(1.0f, 1.0f, 1.0f))
		{
		}
	};
	int Load(std::string fileName);
	void SetTransform(int hModel_, Transform transform_);
	void Draw(int hModel_);
	void Release();

	void RayCast(int hModel, RayCastData& rayData);	//レイキャスト

	void SegmentRayCast(int hModel, RayCastData& rayData);	//レイキャスト

	void AllRelease();
	void SetAlpha(int hModel_, int alpha);	//透明度の取得
	void SetColor(int hModel_, int red, int green, int blue);	//RGB
};

