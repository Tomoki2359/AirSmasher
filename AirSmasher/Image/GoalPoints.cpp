#include "GoalPoints.h"

void GoalPoints::GoalPlayer()
{
	playerPoints_++;
}

void GoalPoints::GoalEnemy()
{
	enemyPoints_++;
}

int GoalPoints::GetPlayerPoints()
{
	return playerPoints_;
}

int GoalPoints::GetEnemyPoints()
{
	return enemyPoints_;
}
