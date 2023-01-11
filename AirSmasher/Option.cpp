#include "Option.h"
namespace
{
	int playerPoint = 0;
	int enemyPoint = 0;
}

void Option::SetPlayerPoint(int p)
{
	playerPoint = p;
}

int Option::GetPlayerPoint()
{
	return playerPoint;
}

void Option::SetEnemyPoint(int p)
{
	enemyPoint = p;
}

int Option::GetEnemyPoint()
{
	return enemyPoint;
}
