#include "QuadrangleHit.h"

namespace QuadrangleHit
{
	void QuadrangleHit::CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2, SquareBox* pSquar,float radius, XMFLOAT3 dir)
	{
		//�����`����邽�߂Ɍ����������ɑ΂��Ă̒��p�����̔��a�����߂�
		XMVECTOR vDir1 = XMLoadFloat3(&dir);
		XMFLOAT3 dir2 = XMFLOAT3{ 0,1,0 };
		XMVECTOR vDir2 = XMLoadFloat3(&dir2);
		//�O��
		XMVECTOR c = XMVector3Cross(vDir1, vDir2);
		//���K�����Ĕ��a�ɂ���
		c = XMVector3Normalize(c);
		c = c * radius;
		XMStoreFloat3(&dir2, c);
		if (f1.x < f2.x)
		{
			pSquar->xPos_.x = f1.x - dir2.x;
			pSquar->xPos_.y = f1.x + dir2.x;
			pSquar->xPos_.z = f2.x - dir2.x;
			pSquar->xPos_.w = f2.x + dir2.x;
		}
		else
		{
			pSquar->xPos_.x = f2.x - dir2.x;
			pSquar->xPos_.y = f2.x + dir2.x;
			pSquar->xPos_.z = f1.x - dir2.x;
			pSquar->xPos_.w = f1.x + dir2.x;
		}

		if (f1.z < f2.z)
		{
			pSquar->zPos_.x = f2.z - dir2.z;
			pSquar->zPos_.y = f2.z + dir2.z;
			pSquar->zPos_.z = f1.z - dir2.z;
			pSquar->zPos_.w = f1.z + dir2.z;
		}
		else
		{
			pSquar->zPos_.x = f1.z - dir2.z;
			pSquar->zPos_.y = f1.z + dir2.z;
			pSquar->zPos_.z = f2.z - dir2.z;
			pSquar->zPos_.w = f2.z + dir2.z;
		}
	}

	bool HitTest(SquareBox s1, SquareBox s2)
	{
		//�X��
		XMFLOAT4 slope;	
		slope.x = (s1.zPos_.y - s1.zPos_.x) / (s1.xPos_.y - s1.xPos_.x);	//�X��1
		slope.y = (s1.zPos_.z - s1.zPos_.y) / (s1.xPos_.z - s1.xPos_.y);	//�X��2
		slope.z = (s2.zPos_.y - s2.zPos_.x) / (s2.xPos_.y - s2.xPos_.x);	//�X��3
		slope.w = (s2.zPos_.z - s2.zPos_.y) / (s2.xPos_.z - s2.xPos_.y);	//�X��4

		//�ؕЂ����߂�
		XMFLOAT4 intercept1;
		XMFLOAT4 intercept2;

		//�l�p�`�P
		intercept1.x = s1.zPos_.x - (slope.x * s1.xPos_.x);
		intercept1.y = s1.zPos_.z - (slope.x * s1.xPos_.z);
		intercept1.z = s1.zPos_.x - (slope.y * s1.xPos_.x);
		intercept1.w = s1.zPos_.y - (slope.y * s1.xPos_.y);

		//�l�p�`�Q
		intercept2.x = s2.zPos_.x - (slope.z * s2.xPos_.x);
		intercept2.y = s2.zPos_.z - (slope.z * s2.xPos_.z);
		intercept2.z = s2.zPos_.x - (slope.w * s2.xPos_.x);
		intercept2.w = s2.zPos_.y - (slope.w * s2.xPos_.y);

		//��_�����߂�
		XMFLOAT4 intersectionPoint1;
		XMFLOAT4 intersectionPoint2;
		XMFLOAT4 intersectionPoint3;
		XMFLOAT4 intersectionPoint4;
		XMFLOAT4 intersectionPoint5;
		XMFLOAT4 intersectionPoint6;
		XMFLOAT4 intersectionPoint7;
		XMFLOAT4 intersectionPoint8;

		intersectionPoint1.x = ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.x)) / ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.x));
		intersectionPoint1.y = ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.x)) / ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.x));
		intersectionPoint1.z = ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.x)) / ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.x));
		intersectionPoint1.w = ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.x)) / ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.x));

		intersectionPoint2.x = ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.x)) / ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.x));
		intersectionPoint2.y = ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.x)) / ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.x));
		intersectionPoint2.z = ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.x)) / ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.x));
		intersectionPoint2.w = ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.x)) / ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.x));
		
		intersectionPoint3.x = ((s1.zPos_.z * intercept2.x) - (s2.zPos_.x * intercept1.y)) / ((s1.xPos_.z * intercept2.x) - (s2.xPos_.x * intercept1.y));
		intersectionPoint3.y = ((s1.xPos_.z * intercept2.x) - (s2.xPos_.x * intercept1.y)) / ((s1.zPos_.z * intercept2.x) - (s2.zPos_.x * intercept1.y));
		intersectionPoint3.z = ((s1.zPos_.z * intercept2.y) - (s2.zPos_.z * intercept1.y)) / ((s1.xPos_.z * intercept2.y) - (s2.xPos_.z * intercept1.y));
		intersectionPoint3.w = ((s1.xPos_.z * intercept2.y) - (s2.xPos_.z * intercept1.y)) / ((s1.zPos_.z * intercept2.y) - (s2.zPos_.z * intercept1.y));

		intersectionPoint4.x = ((s1.zPos_.z * intercept2.z) - (s2.zPos_.x * intercept1.y)) / ((s1.xPos_.z * intercept2.z) - (s2.xPos_.x * intercept1.y));
		intersectionPoint4.y = ((s1.xPos_.z * intercept2.z) - (s2.xPos_.x * intercept1.y)) / ((s1.zPos_.z * intercept2.z) - (s2.zPos_.x * intercept1.y));
		intersectionPoint4.z = ((s1.zPos_.z * intercept2.w) - (s2.zPos_.y * intercept1.y)) / ((s1.xPos_.z * intercept2.w) - (s2.xPos_.y * intercept1.y));
		intersectionPoint4.w = ((s1.xPos_.z * intercept2.w) - (s2.xPos_.y * intercept1.y)) / ((s1.zPos_.z * intercept2.w) - (s2.zPos_.y * intercept1.y));

		intersectionPoint5.x = ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.z)) / ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.z));
		intersectionPoint5.y = ((s1.xPos_.x * intercept2.x) - (s2.xPos_.x * intercept1.z)) / ((s1.zPos_.x * intercept2.x) - (s2.zPos_.x * intercept1.z));
		intersectionPoint5.z = ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.z)) / ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.z));
		intersectionPoint5.w = ((s1.xPos_.x * intercept2.y) - (s2.xPos_.z * intercept1.z)) / ((s1.zPos_.x * intercept2.y) - (s2.zPos_.z * intercept1.z));

		intersectionPoint6.x = ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.z)) / ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.z));
		intersectionPoint6.y = ((s1.xPos_.x * intercept2.z) - (s2.xPos_.x * intercept1.z)) / ((s1.zPos_.x * intercept2.z) - (s2.zPos_.x * intercept1.z));
		intersectionPoint6.z = ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.z)) / ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.z));
		intersectionPoint6.w = ((s1.xPos_.x * intercept2.w) - (s2.xPos_.y * intercept1.z)) / ((s1.zPos_.x * intercept2.w) - (s2.zPos_.y * intercept1.z));

		intersectionPoint7.x = ((s1.zPos_.y * intercept2.x) - (s2.zPos_.x * intercept1.w)) / ((s1.xPos_.y * intercept2.x) - (s2.xPos_.x * intercept1.w));
		intersectionPoint7.y = ((s1.xPos_.y * intercept2.x) - (s2.xPos_.x * intercept1.w)) / ((s1.zPos_.y * intercept2.x) - (s2.zPos_.x * intercept1.w));
		intersectionPoint7.z = ((s1.zPos_.y * intercept2.y) - (s2.zPos_.z * intercept1.w)) / ((s1.xPos_.y * intercept2.y) - (s2.xPos_.z * intercept1.w));
		intersectionPoint7.w = ((s1.xPos_.y * intercept2.y) - (s2.xPos_.z * intercept1.w)) / ((s1.zPos_.y * intercept2.y) - (s2.zPos_.z * intercept1.w));

		intersectionPoint8.x = ((s1.zPos_.y * intercept2.z) - (s2.zPos_.x * intercept1.w)) / ((s1.xPos_.y * intercept2.z) - (s2.xPos_.x * intercept1.w));
		intersectionPoint8.y = ((s1.xPos_.y * intercept2.z) - (s2.xPos_.x * intercept1.w)) / ((s1.zPos_.y * intercept2.z) - (s2.zPos_.x * intercept1.w));
		intersectionPoint8.z = ((s1.zPos_.y * intercept2.w) - (s2.zPos_.y * intercept1.w)) / ((s1.xPos_.y * intercept2.w) - (s2.xPos_.y * intercept1.w));
		intersectionPoint8.w = ((s1.xPos_.y * intercept2.w) - (s2.xPos_.y * intercept1.w)) / ((s1.zPos_.y * intercept2.w) - (s2.zPos_.y * intercept1.w));

		if (intersectionPoint1.x <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint1.y <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
			intersectionPoint1.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint1.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
			intersectionPoint1.z <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint1.w <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
			intersectionPoint1.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint1.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

			intersectionPoint2.x <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint2.y <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
			intersectionPoint2.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint2.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
			intersectionPoint2.z <= (s1.xPos_.x + (s1.xPos_.y - s1.xPos_.x)) && intersectionPoint2.w <= (s1.zPos_.x + (s1.zPos_.y - s1.zPos_.x)) &&
			intersectionPoint2.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint2.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

			intersectionPoint3.x <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint3.y <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
			intersectionPoint3.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint3.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
			intersectionPoint3.z <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint3.w <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
			intersectionPoint3.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint3.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

			intersectionPoint4.x <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint4.y <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
			intersectionPoint4.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint4.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
			intersectionPoint4.z <= (s1.xPos_.z + (s1.xPos_.w - s1.xPos_.z)) && intersectionPoint4.w <= (s1.zPos_.z + (s1.zPos_.w - s1.zPos_.z)) &&
			intersectionPoint4.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint4.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

			//
			intersectionPoint5.x <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint5.y <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
			intersectionPoint5.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint5.y <= (s2.zPos_.x + (s2.zPos_.y - s2.zPos_.x)) ||
			intersectionPoint5.z <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint5.w <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
			intersectionPoint5.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint5.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z)) ||

			intersectionPoint6.x <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint6.y <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
			intersectionPoint6.x <= (s2.xPos_.x + (s2.xPos_.w - s2.xPos_.x)) && intersectionPoint6.y <= (s2.zPos_.x + (s2.zPos_.w - s2.zPos_.x)) ||
			intersectionPoint6.z <= (s1.xPos_.x + (s1.xPos_.w - s1.xPos_.x)) && intersectionPoint6.w <= (s1.zPos_.x + (s1.zPos_.w - s1.zPos_.x)) &&
			intersectionPoint6.z <= (s2.xPos_.y + (s2.xPos_.z - s2.xPos_.y)) && intersectionPoint6.w <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||

			intersectionPoint7.x <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint7.y <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
			intersectionPoint7.x <= (s2.xPos_.x + (s2.xPos_.y - s2.xPos_.x)) && intersectionPoint7.y <= (s2.zPos_.y + (s2.zPos_.z - s2.zPos_.y)) ||
			intersectionPoint7.z <= (s1.xPos_.y + (s1.xPos_.z - s1.xPos_.y)) && intersectionPoint7.w <= (s1.zPos_.y + (s1.zPos_.z - s1.zPos_.y)) &&
			intersectionPoint7.z <= (s2.xPos_.z + (s2.xPos_.w - s2.xPos_.z)) && intersectionPoint7.w <= (s2.zPos_.z + (s2.zPos_.w - s2.zPos_.z))
			);
		{

		}

		return false;
	}
}