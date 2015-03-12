#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "Iw2DSceneGraph.h"
#include "Iw2DSceneGraphCore.h"

using namespace std;
using namespace Iw2DSceneGraph;
using namespace Iw2DSceneGraphCore;
//a signleton class that mannage enemies.
class Enemy
{
private:
	float height=0, width=0;
	enum enemy_type {SHARK};
	enum enemy_rate {PEICE_OF_CAKE, EASY, NORMAL, HARD, NIGHTMARE};

	Enemy();
	Enemy(float height, float width);
	static Enemy* single_instance;

	CSprite* encounter;
	vector<CSprite*>	enemies;

public:

	static Enemy *getInstance(float height, float width);
	CSprite* addEnemy(CIw2DImage* image);
	void update(); //will remove enemies that reach the end of the screen
	void clean(); 
	void removenemies(); //remove all enemies
	CSprite* getEnemy();

};

#endif // !ENEMY_H
