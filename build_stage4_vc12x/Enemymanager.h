#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H


#include <vector>
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "Enemy.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace IwTween;

class EnemyManager{
private:
	
	Enemy *tempEnemy;
	CNode *enemyChildrens;
	vector<Enemy>  enemiesList;
	static EnemyManager* instance;
	EnemyManager(float height, float width);

public:
	static EnemyManager* getInstance(float height, float width);
	void addEnemy(Enemy *newenemy = new Enemy);
	CNode *getCNode();
	void update(float time);
};


#endif /__ENEMYMANAGER_H