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

			int c = 0;
			/*pSquar->xPos_.x = f1.x - radius;
			pSquar->xPos_.y = f1.x;
			pSquar->xPos_.z = f2.x + radius;
			pSquar->xPos_.w = f2.x;

			pSquar->zPos_.x = f1.z;
			pSquar->zPos_.y = f1.z - radius;
			pSquar->zPos_.z = f2.z;
			pSquar->zPos_.w = f2.z + radius;*/
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

			//pSquar->xPos_.x = f1.x - dir2.x;
			//pSquar->xPos_.y = f1.x + dir2.x;
			//pSquar->xPos_.z = f2.x + dir2.x;
			//pSquar->xPos_.w = f2.x - dir2.x;

			//pSquar->zPos_.x = f1.z + dir2.z;
			//pSquar->zPos_.y = f1.z - dir2.z;
			//pSquar->zPos_.z = f2.z - dir2.z;
			//pSquar->zPos_.w = f2.z + dir2.z;
			int a = 0;
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

			int b = 0;
		/*	pSquar->xPos_.x = f1.x - dir2.x;
			pSquar->xPos_.y = f1.x + dir2.x;
			pSquar->xPos_.z = f2.x - dir2.x;
			pSquar->xPos_.w = f2.x + dir2.x;

			pSquar->zPos_.x = f1.z - dir2.z;
			pSquar->zPos_.y = f1.z + dir2.z;
			pSquar->zPos_.z = f2.z + dir2.z;
			pSquar->zPos_.w = f2.z - dir2.z;*/
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
		////åXÇ´
		//XMFLOAT4 slope;	
		//slope.x = (s1.zPos_.y - s1.zPos_.x) / (s1.xPos_.y - s1.xPos_.x);	//åXÇ´1
		//slope.y = (s1.zPos_.z - s1.zPos_.y) / (s1.xPos_.z - s1.xPos_.y);	//åXÇ´2
		//slope.z = (s2.zPos_.y - s2.zPos_.x) / (s2.xPos_.y - s2.xPos_.x);	//åXÇ´3
		//slope.w = (s2.zPos_.z - s2.zPos_.y) / (s2.xPos_.z - s2.xPos_.y);	//åXÇ´4

		////êÿï–ÇãÅÇﬂÇÈ
		//XMFLOAT4 intercept1;
		//XMFLOAT4 intercept2;

		////éläpå`ÇP
		//intercept1.x = s1.zPos_.x - (slope.x * s1.xPos_.x);
		//intercept1.y = s1.zPos_.z - (slope.x * s1.xPos_.z);
		//intercept1.z = s1.zPos_.x - (slope.y * s1.xPos_.x);
		//intercept1.w = s1.zPos_.y - (slope.y * s1.xPos_.y);

		////éläpå`ÇQ
		//intercept2.x = s2.zPos_.x - (slope.z * s2.xPos_.x);
		//intercept2.y = s2.zPos_.z - (slope.z * s2.xPos_.z);
		//intercept2.z = s2.zPos_.x - (slope.w * s2.xPos_.x);
		//intercept2.w = s2.zPos_.y - (slope.w * s2.xPos_.y);

		////åì_ÇãÅÇﬂÇÈ
		//XMFLOAT4 intersectionPoint1;
		//XMFLOAT4 intersectionPoint2;
		//XMFLOAT4 intersectionPoint3;
		//XMFLOAT4 intersectionPoint4;
		//XMFLOAT4 intersectionPoint5;
		//XMFLOAT4 intersectionPoint6;
		//XMFLOAT4 intersectionPoint7;
		//XMFLOAT4 intersectionPoint8;

		//intersectionPoint1.x = ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.x)) / ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.x));
		//intersectionPoint1.y = ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.x)) / ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.x));
		//intersectionPoint1.z = ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.x)) / ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.x));
		//intersectionPoint1.w = ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.x)) / ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.x));

		//intersectionPoint2.x = ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.x)) / ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.x));
		//intersectionPoint2.y = ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.x)) / ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.x));
		//intersectionPoint2.z = ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.x)) / ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.x));
		//intersectionPoint2.w = ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.x)) / ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.x));
		//
		//intersectionPoint3.x = ((s1.zPos_.z * intercept2.x) - (s2.zPos_.x * intercept1.y)) / ((s1.xPos_.z * intercept2.x) - (s2.xPos_.x * intercept1.y));
		//intersectionPoint3.y = ((s1.xPos_.z * intercept2.x) - (s2.xPos_.x * intercept1.y)) / ((s1.zPos_.z * intercept2.x) - (s2.zPos_.x * intercept1.y));
		//intersectionPoint3.z = ((s1.zPos_.z * intercept2.y) - (s2.zPos_.z * intercept1.y)) / ((s1.xPos_.z * intercept2.y) - (s2.xPos_.z * intercept1.y));
		//intersectionPoint3.w = ((s1.xPos_.z * intercept2.y) - (s2.xPos_.z * intercept1.y)) / ((s1.zPos_.z * intercept2.y) - (s2.zPos_.z * intercept1.y));

		//intersectionPoint4.x = ((s1.zPos_.z * intercept2.z) - (s2.zPos_.x * intercept1.y)) / ((s1.xPos_.z * intercept2.z) - (s2.xPos_.x * intercept1.y));
		//intersectionPoint4.y = ((s1.xPos_.z * intercept2.z) - (s2.xPos_.x * intercept1.y)) / ((s1.zPos_.z * intercept2.z) - (s2.zPos_.x * intercept1.y));
		//intersectionPoint4.z = ((s1.zPos_.z * intercept2.w) - (s2.zPos_.y * intercept1.y)) / ((s1.xPos_.z * intercept2.w) - (s2.xPos_.y * intercept1.y));
		//intersectionPoint4.w = ((s1.xPos_.z * intercept2.w) - (s2.xPos_.y * intercept1.y)) / ((s1.zPos_.z * intercept2.w) - (s2.zPos_.y * intercept1.y));

		//intersectionPoint5.x = ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.z)) / ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.z));
		//intersectionPoint5.y = ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.z)) / ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.z));
		//intersectionPoint5.z = ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.z)) / ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.z));
		//intersectionPoint5.w = ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.z)) / ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.z));

		//intersectionPoint6.x = ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.z)) / ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.z));
		//intersectionPoint6.y = ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.z)) / ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.z));
		//intersectionPoint6.z = ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.z)) / ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.z));
		//intersectionPoint6.w = ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.z)) / ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.z));

		//intersectionPoint7.x = ((s1.zPos_.y * intercept2.x) - (s2.zPos_.x * intercept1.w)) / ((s1.xPos_.y * intercept2.x) - (s2.xPos_.x * intercept1.w));
		//intersectionPoint7.y = ((s1.xPos_.y * intercept2.x) - (s2.xPos_.x * intercept1.w)) / ((s1.zPos_.y * intercept2.x) - (s2.zPos_.x * intercept1.w));
		//intersectionPoint7.z = ((s1.zPos_.y * intercept2.y) - (s2.zPos_.z * intercept1.w)) / ((s1.xPos_.y * intercept2.y) - (s2.xPos_.z * intercept1.w));
		//intersectionPoint7.w = ((s1.xPos_.y * intercept2.y) - (s2.xPos_.z * intercept1.w)) / ((s1.zPos_.y * intercept2.y) - (s2.zPos_.z * intercept1.w));

		//intersectionPoint8.x = ((s1.zPos_.y * intercept2.z) - (s2.zPos_.x * intercept1.w)) / ((s1.xPos_.y * intercept2.z) - (s2.xPos_.x * intercept1.w));
		//intersectionPoint8.y = ((s1.xPos_.y * intercept2.z) - (s2.xPos_.x * intercept1.w)) / ((s1.zPos_.y * intercept2.z) - (s2.zPos_.x * intercept1.w));
		//intersectionPoint8.z = ((s1.zPos_.y * intercept2.w) - (s2.zPos_.y * intercept1.w)) / ((s1.xPos_.y * intercept2.w) - (s2.xPos_.y * intercept1.w));
		//intersectionPoint8.w = ((s1.xPos_.y * intercept2.w) - (s2.xPos_.y * intercept1.w)) / ((s1.zPos_.y * intercept2.w) - (s2.zPos_.y * intercept1.w));

		//if (intersectionPoint1.x <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint1.y <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
		//	intersectionPoint1.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint1.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
		//	intersectionPoint1.z <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint1.w <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
		//	intersectionPoint1.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint1.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

		//	intersectionPoint2.x <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint2.y <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
		//	intersectionPoint2.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint2.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
		//	intersectionPoint2.z <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint2.w <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
		//	intersectionPoint2.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint2.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

		//	intersectionPoint3.x <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint3.y <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
		//	intersectionPoint3.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint3.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
		//	intersectionPoint3.z <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint3.w <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
		//	intersectionPoint3.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint3.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

		//	intersectionPoint4.x <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint4.y <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
		//	intersectionPoint4.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint4.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
		//	intersectionPoint4.z <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint4.w <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
		//	intersectionPoint4.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint4.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

		//	//
		//	intersectionPoint5.x <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint5.y <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
		//	intersectionPoint5.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint5.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
		//	intersectionPoint5.z <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint5.w <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
		//	intersectionPoint5.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint5.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

		//	intersectionPoint6.x <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint6.y <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
		//	intersectionPoint6.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint6.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
		//	intersectionPoint6.z <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint6.w <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
		//	intersectionPoint6.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint6.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

		//	intersectionPoint7.x <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint7.y <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
		//	intersectionPoint7.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint7.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
		//	intersectionPoint7.z <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint7.w <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
		//	intersectionPoint7.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint7.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

		//	intersectionPoint8.x <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint8.y <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
		//	intersectionPoint8.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint8.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
		//	intersectionPoint8.z <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint8.w <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
		//	intersectionPoint8.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint8.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y))
		//	);
		//{
		//	int a = 0;
		//	return true;
		//}

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