#pragma once
#include "Transform.h"

struct SquareBox		//当たっているか確認用四角形
{
	//四角形の頂点
	XMFLOAT2 LUPos_;	//左上のポジション
	XMFLOAT2 LDPos_;	//左下のポジション
	XMFLOAT2 RDPos_;	//右下のポジション
	XMFLOAT2 RUPos_;	//右上のポジション
};

class QuadrangleHit
{
	SquareBox square_;
public:
	QuadrangleHit();
	//四角形を作る処理
	//第一引数	位置;第二引数	位置;	第三引数	四角形;	第四引数	半径; 第五引数	向き
	void CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2,float radius,XMFLOAT3 dir);

	bool HitTest(SquareBox square);

	bool IsHitLine(XMFLOAT2 l1, XMFLOAT2 l2, XMFLOAT2 l3, XMFLOAT2 l4);

	SquareBox GetSquareBox() { return square_; };
};

