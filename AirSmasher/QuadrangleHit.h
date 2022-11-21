#pragma once
#include "Engine/Transform.h"

struct SquareBox		//当たっているか確認用四角形
{
	//x 左上;y 左下;z 右上;w 右下
	XMFLOAT4 xPos_;		//前回と今の位置の通り道(x軸点)
	//x 左上;y 左下;z 右上;w 右下
	XMFLOAT4 zPos_;		//前回と今の位置の通り道(z軸点)
};

namespace QuadrangleHit
{
	//四角形を作る処理
	//第一引数	位置;第二引数	位置;	第三引数	四角形;	第四引数	半径; 第五引数	向き
	void CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2,SquareBox* pSquar,float radius,XMFLOAT3 dir);

	bool HitTest(SquareBox s1, SquareBox s2);
};

