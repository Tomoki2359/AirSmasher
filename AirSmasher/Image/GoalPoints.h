#pragma once
#include "../Engine/GameObject.h"

class GoalPoints :public GameObject
{
	int playerPoints_;
	int enemyPoints_;
public:
	void GoalPlayer();
	void GoalEnemy();
	int GetPlayerPoints();
	int GetEnemyPoints();
};