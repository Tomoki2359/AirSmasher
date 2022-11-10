#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class Texture;

struct RayCastData
{
	XMFLOAT3 start;	//スタート地点
	XMFLOAT3 dir;	//向いている方向
	BOOL hit;		//当たってるかどうか
	XMFLOAT3 side1;	//三角形の辺その1
	XMFLOAT3 side2;	//三角形の辺その2
	XMFLOAT3 pos;	//ぶつかった場所
	float dist;		//距離
};

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};
	//Simple3Dに送るやつ
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;
		int			isTexture;
		float		red_;
		float		green_;
		float		blue_;
		float		alpha_;
	};

	//Simple3Dに送るやつ
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	VERTEX* pVertices_;
	int** ppIndex_;

	

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;

	int* indexCount_;

public:
	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform, float alpha, XMFLOAT3 color);
	void    Release();

	void RayCast(RayCastData& reyData);

	void SegmentRayCast(RayCastData& reyData);

private:
	void InitVertex(fbxsdk::FbxMesh* pMesh);
	void InitIndex(fbxsdk::FbxMesh* pMesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
};