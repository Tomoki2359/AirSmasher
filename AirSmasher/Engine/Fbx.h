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
	XMFLOAT3 start;	//�X�^�[�g�n�_
	XMFLOAT3 dir;	//�����Ă������
	BOOL hit;		//�������Ă邩�ǂ���
	XMFLOAT3 side1;	//�O�p�`�̕ӂ���1
	XMFLOAT3 side2;	//�O�p�`�̕ӂ���2
	XMFLOAT3 pos;	//�Ԃ������ꏊ
	float dist;		//����
};

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};
	//Simple3D�ɑ�����
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

	//Simple3D�ɑ�����
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	VERTEX* pVertices_;
	int** ppIndex_;

	

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

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