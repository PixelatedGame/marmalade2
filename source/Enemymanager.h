#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H


#include <vector>
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "Enemy.h"

/*
Guy hod, ze lo tov,
Amar Lanu Ha shcriber,
Lo Mitkampel Li
*/

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace IwTween;

class EnemyManager{
private:
	
	Enemy *tempEnemy;
	CNode *enemyChildrens;
	std::vector<Enemy*> enemy_vector;
	static EnemyManager* instance;
	

	EnemyManager();
public:
	
	static EnemyManager *getInstance();
	void addEnemy(Enemy *new_enemy);
	void update(float time);
};


#endif /__ENEMYMANAGER_H