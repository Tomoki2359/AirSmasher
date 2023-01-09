#include "QuadrangleHit.h"


QuadrangleHit::QuadrangleHit()
{
	square_.LUPos_.x = 0;
	square_.LUPos_.y = 0;

	square_.LDPos_.x = 0;
	square_.LDPos_.y = 0;

	square_.RDPos_.x = 0;
	square_.RDPos_.y = 0;

	square_.RUPos_.x = 0;
	square_.RUPos_.y = 0;
}

void QuadrangleHit::CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2, float radius, XMFLOAT3 dir)
{
	//í∑ï˚å`ÇçÏÇÈÇΩÇﬂÇ…å¸Ç©Ç§ï˚å¸Ç…ëŒÇµÇƒÇÃíºäpïîï™ÇÃîºåaÇãÅÇﬂÇÈ
	XMVECTOR vDir1 = XMLoadFloat3(&dir);
	XMFLOAT3 dir2 = XMFLOAT3{ 0,1,0 };
	XMVECTOR vDir2 = XMLoadFloat3(&dir2);
	//äOêœ
	XMVECTOR c = XMVector3Cross(vDir1, vDir2);
	//ê≥ãKâªÇµÇƒîºåaÇ…Ç∑ÇÈ
	c = XMVector3Normalize(c);
	c = c * radius;
	XMStoreFloat3(&dir2, c);
	if (dir.x == 0 && dir.z == 0)
	{
		square_.LUPos_.x = f1.x - radius;
		square_.LUPos_.y = f1.z;

		square_.LDPos_.x = f1.x;
		square_.LDPos_.y = f1.z - radius;

		square_.RDPos_.x = f2.x + radius;
		square_.RDPos_.y = f2.z;

		square_.RUPos_.x = f2.x;
		square_.RUPos_.y = f2.z + radius;
	}
	else if (f1.x < f2.x && f1.z < f2.z || f1.x > f2.x && f1.z > f2.z)
	{
		square_.LUPos_.x = f1.x - dir2.x;
		square_.LUPos_.y = f1.z + dir2.z;

		square_.LDPos_.x = f1.x + dir2.x;
		square_.LDPos_.y = f1.z - dir2.z;

		square_.RDPos_.x = f2.x + dir2.x;
		square_.RDPos_.y = f2.z - dir2.z;

		square_.RUPos_.x = f2.x - dir2.x;
		square_.RUPos_.y = f2.z + dir2.z;
	}
	else
	{
		square_.LUPos_.x = f1.x - dir2.x;
		square_.LUPos_.y = f1.z + dir2.z;

		square_.LDPos_.x = f1.x + dir2.x;
		square_.LDPos_.y = f1.z - dir2.z;

		square_.RDPos_.x = f2.x - dir2.x;
		square_.RDPos_.y = f2.z + dir2.z;

		square_.RUPos_.x = f2.x + dir2.x;
		square_.RUPos_.y = f2.z - dir2.z;
	}

}

bool QuadrangleHit::HitTest(SquareBox square)
{
	if (IsHitLine(square_.LUPos_, square_.LDPos_, square.LUPos_, square.LDPos_) ||
		IsHitLine(square_.LUPos_, square_.LDPos_, square.LUPos_, square.RUPos_) ||
		IsHitLine(square_.LUPos_, square_.LDPos_, square.RUPos_, square.RDPos_) ||
		IsHitLine(square_.LUPos_, square_.LDPos_, square.LDPos_, square.RDPos_) ||

		IsHitLine(square_.LUPos_, square_.RUPos_, square.LUPos_, square.LDPos_) ||
		IsHitLine(square_.LUPos_, square_.RUPos_, square.LUPos_, square.RUPos_) ||
		IsHitLine(square_.LUPos_, square_.RUPos_, square.RUPos_, square.RDPos_) ||
		IsHitLine(square_.LUPos_, square_.RUPos_, square.LDPos_, square.RDPos_) ||

		IsHitLine(square_.RDPos_, square_.LDPos_, square.LUPos_, square.LDPos_) ||
		IsHitLine(square_.RDPos_, square_.LDPos_, square.LUPos_, square.RUPos_) ||
		IsHitLine(square_.RDPos_, square_.LDPos_, square.RUPos_, square.RDPos_) ||
		IsHitLine(square_.RDPos_, square_.LDPos_, square.LDPos_, square.RDPos_) ||

		IsHitLine(square_.RDPos_, square_.RUPos_, square.LUPos_, square.LDPos_) ||
		IsHitLine(square_.RDPos_, square_.RUPos_, square.LUPos_, square.RUPos_) ||
		IsHitLine(square_.RDPos_, square_.RUPos_, square.RUPos_, square.RDPos_) ||
		IsHitLine(square_.RDPos_, square_.RUPos_, square.LDPos_, square.RDPos_))
	{
		return true;
	}
	return false;
}

bool QuadrangleHit::IsHitLine(XMFLOAT2 l1, XMFLOAT2 l2, XMFLOAT2 l3, XMFLOAT2 l4)
{
	//íºê¸Ç∆ê¸ï™ÇÃìñÇΩÇËîªíË
	float i1 = (l1.x - l2.x) * (l3.y - l1.y) + (l1.y - l2.y) * (l1.x - l3.x);
	float i2 = (l1.x - l2.x) * (l4.y - l1.y) + (l1.y - l2.y) * (l1.x - l4.x);

	float i3 = (l3.x - l4.x) * (l1.y - l3.y) + (l3.y - l4.y) * (l3.x - l1.x);
	float i4 = (l3.x - l4.x) * (l2.y - l3.y) + (l3.y - l4.y) * (l3.x - l2.x);
	if (i1 * i2 <= 0 && i3 * i4 <= 0)
	{
		return true;
	}
	return false;
}