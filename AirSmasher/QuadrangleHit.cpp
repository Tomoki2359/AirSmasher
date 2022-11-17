#include "QuadrangleHit.h"

namespace QuadrangleHit
{
	void QuadrangleHit::CreateSquar(XMFLOAT3 f1, XMFLOAT3 f2, SquareBox* pSquar,float radius)
	{
		if (f1.x < f2.x)
		{
			pSquar->xPos_.x = f1.x - radius;
			pSquar->xPos_.y = f1.x - radius;
			pSquar->xPos_.z = f2.x + radius;
			pSquar->xPos_.w = f2.x + radius;
		}
		else
		{
			pSquar->xPos_.x = f2.x - radius;
			pSquar->xPos_.y = f2.x - radius;
			pSquar->xPos_.z = f1.x + radius;
			pSquar->xPos_.w = f1.x + radius;
		}

		if (f1.z < f2.z)
		{
			pSquar->zPos_.x = f2.z + radius;
			pSquar->zPos_.y = f2.z - radius;
			pSquar->zPos_.z = f1.z + radius;
			pSquar->zPos_.w = f1.z - radius;
		}
		else
		{
			pSquar->zPos_.x = f1.z + radius;
			pSquar->zPos_.y = f1.z - radius;
			pSquar->zPos_.z = f2.z + radius;
			pSquar->zPos_.w = f2.z - radius;
		}
	}
}