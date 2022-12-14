#include "Model.h"
#include "Define.h"

namespace Model
{
	std::vector<MODEL*> modelList_;
}

int Model::Load(std::string fileName)
{
	MODEL* pLoadModel;
	pLoadModel = new MODEL;
	pLoadModel->FileModel = fileName;

	for (auto itr = modelList_.begin(); itr < modelList_.end(); itr++)
	{
		if (fileName == (*itr)->FileModel)
		{
			pLoadModel->pFbx = (*itr)->pFbx;
			modelList_.push_back(pLoadModel);
			return modelList_.size() - 1;
		}
	}
	pLoadModel->pFbx = new Fbx;
	pLoadModel->pFbx->Load(pLoadModel->FileModel);
	modelList_.push_back(pLoadModel);
	return modelList_.size() - 1;
}


void Model::Draw(int hModel_)
{
	modelList_[hModel_]->pFbx->Draw(modelList_[hModel_]->TransformModel, modelList_[hModel_]->alpha_, modelList_[hModel_]->color_);
}

void Model::Release()
{
	for (int i = 0; i < modelList_.size(); i++)
	{
		bool isExist = false;	//今消そうとしているFbxデータを参照してるやつがいるかどうか
		for (int j = i + 1; j < modelList_.size(); j++)
		{
			if (modelList_[i]->pFbx == modelList_[j]->pFbx)
			{
				isExist = true;
				break;
			}
		}
		//もうそのデータを誰も参照してなければ
		if (!isExist)
		{
			SAFE_DELETE(modelList_[i]->pFbx);
		}
		SAFE_DELETE(modelList_[i]);
	}
	modelList_.clear();
}

void Model::RayCast(int hModel, RayCastData& rayData)
{
	//?@ワールド行列の逆行列
	XMMATRIX matInv = XMMatrixInverse(nullptr,modelList_[hModel]->TransformModel.GetWorldMatrix());

	//?Aレイの通過点を求める
	XMFLOAT3 Point = XMFLOAT3(rayData.start.x + rayData.dir.x, rayData.start.y + rayData.dir.y, rayData.start.z + rayData.dir.z);

	//?BrayData.startに?@をかける
	XMVECTOR vStart = XMLoadFloat3(&rayData.start);
	vStart = XMVector3TransformCoord(vStart, matInv);

	//?C通過点(?A)に?@をかける
	XMVECTOR vPoint = XMVector3TransformCoord(XMLoadFloat3(&Point), matInv);

	//?DrayData.dirを?Bから?Cに向かうベクトルにする
	XMVECTOR vDir = vPoint - vStart;

	XMStoreFloat3(&rayData.start, vStart);
	XMStoreFloat3(&rayData.dir, vDir);

	modelList_[hModel]->pFbx->RayCast(rayData);
}

void Model::SegmentRayCast(int hModel, RayCastData& rayData)
{
	//?@ワールド行列の逆行列
	XMMATRIX matInv = XMMatrixInverse(nullptr, modelList_[hModel]->TransformModel.GetWorldMatrix());

	//?Aレイの通過点を求める
	XMFLOAT3 Point = XMFLOAT3(rayData.start.x + rayData.dir.x, rayData.start.y + rayData.dir.y, rayData.start.z + rayData.dir.z);

	//?BrayData.startに?@をかける
	XMVECTOR vStart = XMLoadFloat3(&rayData.start);
	vStart = XMVector3TransformCoord(vStart, matInv);

	//?C通過点(?A)に?@をかける
	XMVECTOR vPoint = XMVector3TransformCoord(XMLoadFloat3(&Point), matInv);

	//?DrayData.dirを?Bから?Cに向かうベクトルにする
	XMVECTOR vDir = vPoint - vStart;

	XMStoreFloat3(&rayData.start, vStart);
	XMStoreFloat3(&rayData.dir, vDir);

	modelList_[hModel]->pFbx->SegmentRayCast(rayData);
}

void Model::AllRelease()
{
	for (int i = 0; i < modelList_.size(); i++)
	{
		if (modelList_[i] != nullptr)
		{
			Release();
		}
	}
	modelList_.clear();
}

//透明度の取得
void Model::SetAlpha(int hModel_, int alpha)
{
	modelList_[hModel_]->alpha_ = (float)alpha / 255;
}

//色の取得
void Model::SetColor(int hModel_, int red, int green, int blue)
{
	modelList_[hModel_]->color_ = XMFLOAT3((float)red / 255, (float)green / 255, (float)blue / 255);
}

void Model::SetTransform(int hModel_, Transform transform_)
{
	modelList_[hModel_]->TransformModel = transform_;
}