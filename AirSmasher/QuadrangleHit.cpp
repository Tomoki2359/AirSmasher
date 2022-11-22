#include "QuadrangleHit.h"

namespace QuadrangleHit
{
	void QuadrangleHit::CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2, SquareBox* pSquar,float radius, XMFLOAT3 dir)
	{
		//’·•ûŒ`‚ğì‚é‚½‚ß‚ÉŒü‚©‚¤•ûŒü‚É‘Î‚µ‚Ä‚Ì’¼Šp•”•ª‚Ì”¼Œa‚ğ‹‚ß‚é
		XMVECTOR vDir1 = XMLoadFloat3(&dir);
		XMFLOAT3 dir2 = XMFLOAT3{ 0,1,0 };
		XMVECTOR vDir2 = XMLoadFloat3(&dir2);
		//ŠOÏ
		XMVECTOR c = XMVector3Cross(vDir1, vDir2);
		//³‹K‰»‚µ‚Ä”¼Œa‚É‚·‚é
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
		if(s1.xPos_.x )
		return false;
	}
}