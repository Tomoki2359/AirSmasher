#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Math.h"

Fbx::Fbx() :
	vertexCount_(0), polygonCount_(0), materialCount_(0),
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
	indexCount_(nullptr), pMaterialList_(nullptr),pVertices_(nullptr),ppIndex_(nullptr)
{
}

Fbx::~Fbx()
{
	Release();
}

HRESULT Fbx::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();


	//メッシュ情報を取得
	FbxNode* pRootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = pRootNode->GetChild(0);
	FbxMesh* pMesh = pNode->GetMesh();

	//現在のカレントディレクトリを覚えておく
	WCHAR defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//引数のfileNameからディレクトリ部分を取得
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());
	WCHAR dir[MAX_PATH];
	_wsplitpath_s(wtext, nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);

	//カレントディレクトリ変更
	SetCurrentDirectory(dir);


	//各情報の個数を取得
	vertexCount_ = pMesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = pMesh->GetPolygonCount();		//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();		//マテリアルの数

	InitVertex(pMesh);		//頂点バッファ準備
	InitIndex(pMesh);		//インデックスバッファ準備
	IntConstantBuffer();	//コンスタントバッファ準備
	InitMaterial(pNode);

	//終わったら戻す
	SetCurrentDirectory(defaultCurrentDir);

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

//頂点バッファ準備
void Fbx::InitVertex(fbxsdk::FbxMesh* pMesh)
{
	//頂点情報を入れる配列
	pVertices_ = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = pMesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = pMesh->GetControlPointAt(index);
			pVertices_[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//頂点のUV
			FbxLayerElementUV* pUV = pMesh->GetLayer(0)->GetUVs();
			int uvIndex = pMesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			pVertices_[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//頂点の法線
			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(poly, vertex, Normal);	//ｉ番目のポリゴンの、ｊ番目の頂点の法線をゲット
			pVertices_[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);

		}
	}


	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = pVertices_;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		//return hr;
	}
}

//インデックスバッファ準備
void Fbx::InitIndex(fbxsdk::FbxMesh* pMesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	indexCount_ = new int[materialCount_];

	ppIndex_ = new int*[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		ppIndex_[i] = new int[polygonCount_ * 3];

		int count = 0;

		//全ポリゴン
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = pMesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{

				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					ppIndex_[i][count] = pMesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;

		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = ppIndex_[i];
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		HRESULT hr;
		hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
			//return hr;
		}
	}
}

void Fbx::IntConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
	}
}


void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];


	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount != 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//ファイル名+拡張だけにする
			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			sprintf_s(name, "%s%s", name, ext);


			//ファイルからテクスチャ作成
			pMaterialList_[i].pTexture = new Texture;
			wchar_t wtext[FILENAME_MAX];
			size_t ret;
			mbstowcs_s(&ret, wtext, name, strlen(textureFilePath));

			pMaterialList_[i].pTexture->Load(wtext);
		}

		//テクスチャ無し
		else
		{
			pMaterialList_[i].pTexture = nullptr;

			//マテリアルの色
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}
	}
}


void Fbx::Draw(Transform& transform, float alpha)
{
	Direct3D::SetShader(SHADER_3D);

	transform.Calclation();



	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < materialCount_; i++)
		{
			CONSTANT_BUFFER cb;
			cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix(j) * Camera::GetProjectionMatrix(j));
			cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
			cb.diffuseColor = pMaterialList_[i].diffuse;
			cb.isTexture = pMaterialList_[i].pTexture != nullptr;
			cb.alpha_ = alpha;

			D3D11_MAPPED_SUBRESOURCE pdata;
			Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る


			if (pMaterialList_[i].pTexture)
			{
				ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
				Direct3D::pContext->PSSetSamplers(0, j, &pSampler);

				ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
				Direct3D::pContext->PSSetShaderResources(0, j, &pSRV);
			}

			Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

			//頂点バッファ
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			Direct3D::pContext->IASetVertexBuffers(0, j, &pVertexBuffer_, &stride, &offset);

			// インデックスバッファーをセット
			stride = sizeof(int);
			offset = 0;
			Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

			//コンスタントバッファ
			Direct3D::pContext->VSSetConstantBuffers(0, j, &pConstantBuffer_);	//頂点シェーダー用	
			Direct3D::pContext->PSSetConstantBuffers(0, j, &pConstantBuffer_);	//ピクセルシェーダー用

				//描画
			Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
		}
	}
}

void Fbx::Release()
{
	SAFE_RELEASE(pConstantBuffer_);

	SAFE_RELEASE(pVertexBuffer_);

	SAFE_DELETE_ARRAY(pVertices_);

	SAFE_DELETE_ARRAY(pIndexBuffer_);

	SAFE_DELETE_ARRAY(pMaterialList_);

	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_DELETE_ARRAY(ppIndex_[i]);
	}
	SAFE_DELETE_ARRAY(ppIndex_);
}

void Fbx::RayCast(RayCastData& reyData)
{
	XMVECTOR vNormal = XMLoadFloat3(&reyData.dir);
	vNormal = XMVector3Normalize(vNormal);
	XMStoreFloat3(&reyData.dir, vNormal);
	//reyData.dist = 9999;
	XMFLOAT3 side_1 = XMFLOAT3{0,0,0};
	XMFLOAT3 side_2; XMFLOAT3{ 0,0,0 };
	//三角形の指定
	for (int material = 0; material < materialCount_; material++)
	{
		//三角形の頂点の指定
		for (int poly = 0; poly < indexCount_[material] / 3; poly++)
		{
			//三角形の一つの頂点を指定
			XMFLOAT3 v0;
			//三角形のもう一つの頂点を指定
			XMFLOAT3 v1;
			//最後の三角形の頂点を指定
			XMFLOAT3 v2;
			XMStoreFloat3(&v0, pVertices_[ppIndex_[material][poly * 3 + 0]].position);
			XMStoreFloat3(&v1, pVertices_[ppIndex_[material][poly * 3 + 1]].position);
			XMStoreFloat3(&v2, pVertices_[ppIndex_[material][poly * 3 + 2]].position);

			float minDist = 0.0f;
			BOOL  hit = FALSE;
			hit = Math::Intersect(reyData.start,reyData.dir,v0,v1,v2,&side_1, &side_2, &minDist);
			if (hit && minDist < reyData.dist)
			{
				reyData.side1 = side_1;
				reyData.side2 = side_2;
				reyData.dist = minDist;
				reyData.hit = TRUE;
			}
		}
	}
	return;
}
