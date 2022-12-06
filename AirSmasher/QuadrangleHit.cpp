#include "QuadrangleHit.h"

namespace QuadrangleHit
{
	bool isHit;

	void QuadrangleHit::CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2, SquareBox* pSquar, float radius, XMFLOAT3 dir)
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
			pSquar->LUPos_.x = f1.x - radius;
			pSquar->LUPos_.y = f1.z;

			pSquar->LDPos_.x = f1.x;
			pSquar->LDPos_.y = f1.z - radius;

			pSquar->RDPos_.x = f2.x + radius;
			pSquar->RDPos_.y = f2.z;

			pSquar->RUPos_.x = f2.x;
			pSquar->RUPos_.y = f2.z + radius;
		}
		else if (f1.x < f2.x && f1.z < f2.z || f1.x > f2.x && f1.z > f2.z)
		{
			pSquar->LUPos_.x = f1.x - dir2.x;
			pSquar->LUPos_.y = f1.z + dir2.z;

			pSquar->LDPos_.x = f1.x + dir2.x;
			pSquar->LDPos_.y = f1.z - dir2.z;

			pSquar->RDPos_.x = f2.x + dir2.x;
			pSquar->RDPos_.y = f2.z - dir2.z;

			pSquar->RUPos_.x = f2.x - dir2.x;
			pSquar->RUPos_.y = f2.z + dir2.z;
		}
		else
		{
			pSquar->LUPos_.x = f1.x - dir2.x;
			pSquar->LUPos_.y = f1.z + dir2.z;

			pSquar->LDPos_.x = f1.x + dir2.x;
			pSquar->LDPos_.y = f1.z - dir2.z;

			pSquar->RDPos_.x = f2.x - dir2.x;
			pSquar->RDPos_.y = f2.z + dir2.z;

			pSquar->RUPos_.x = f2.x + dir2.x;
			pSquar->RUPos_.y = f2.z - dir2.z;
		}

	}

	bool HitTest(SquareBox s1, SquareBox s2)
	{
		isHit = false;
		IsHitLine(s1.LUPos_, s1.LDPos_, s2.LUPos_, s2.LDPos_);
		IsHitLine(s1.LUPos_, s1.LDPos_, s2.LUPos_, s2.RUPos_);
		IsHitLine(s1.LUPos_, s1.LDPos_, s2.RUPos_, s2.RDPos_);
		IsHitLine(s1.LUPos_, s1.LDPos_, s2.LDPos_, s2.RDPos_);

		IsHitLine(s1.LUPos_, s1.RUPos_, s2.LUPos_, s2.LDPos_);
		IsHitLine(s1.LUPos_, s1.RUPos_, s2.LUPos_, s2.RUPos_);
		IsHitLine(s1.LUPos_, s1.RUPos_, s2.RUPos_, s2.RDPos_);
		IsHitLine(s1.LUPos_, s1.RUPos_, s2.LDPos_, s2.RDPos_);
	
		IsHitLine(s1.RDPos_, s1.LDPos_, s2.LUPos_, s2.LDPos_);
		IsHitLine(s1.RDPos_, s1.LDPos_, s2.LUPos_, s2.RUPos_);
		IsHitLine(s1.RDPos_, s1.LDPos_, s2.RUPos_, s2.RDPos_);
		IsHitLine(s1.RDPos_, s1.LDPos_, s2.LDPos_, s2.RDPos_);

		IsHitLine(s1.RDPos_, s1.RUPos_, s2.LUPos_, s2.LDPos_);
		IsHitLine(s1.RDPos_, s1.RUPos_, s2.LUPos_, s2.RUPos_);
		IsHitLine(s1.RDPos_, s1.RUPos_, s2.RUPos_, s2.RDPos_);
		IsHitLine(s1.RDPos_, s1.RUPos_, s2.LDPos_, s2.RDPos_);
		return isHit;
	}

	void IsHitLine(XMFLOAT2 l1, XMFLOAT2 l2, XMFLOAT2 l3, XMFLOAT2 l4)
	{
		//íºê¸Ç∆ê¸ï™ÇÃìñÇΩÇËîªíË
		float i1 = (l1.x - l2.x) * (l3.y - l1.y) + (l1.y - l2.y) * (l1.x - l3.x);
		float i2 = (l1.x - l2.x) * (l4.y - l1.y) + (l1.y - l2.y) * (l1.x - l4.x);

		float i3 = (l3.x - l4.x) * (l1.y - l3.y) + (l3.y - l4.y) * (l3.x - l1.x);
		float i4 = (l3.x - l4.x) * (l2.y - l3.y) + (l3.y - l4.y) * (l3.x - l2.x);
		if (i1 * i2 <= 0 && i3 * i4 <= 0)
		{
			isHit = true;
		}
	}
}