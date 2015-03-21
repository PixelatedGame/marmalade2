#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H


#include <vector>
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "scene.h"
#include "Entity.h"

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
	
	Entity *tempEnemy;
	CNode *enemyChildrens;
	std::vector<Entity*> enemy_vector;
	static EnemyManager* instance;
	Scene *currentScene;

	EnemyManager();
public:
	
	static EnemyManager *getInstance();
	void addEnemy(Entity *new_enemy);
	void update(float time);
};


#endif /__ENEMYMANAGER_H