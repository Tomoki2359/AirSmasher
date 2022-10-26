#pragma once
#include <d3d11.h>
#include "string"

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	XMMATRIX size_;
public:
	Texture();
	~Texture();
	HRESULT Load(LPCWSTR fileName);
	void Release();

	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
	XMMATRIX GetSize() { return size_; }	//‰æ‘œƒTƒCƒY
};