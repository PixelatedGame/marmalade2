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
	float height = 0, width = 0;
	float speed = 0;
	CSprite* enemyinstance = NULL;


public:
	Enemy();
	void update(); //will remove enemies that reach the end of the screen
	void clean(); 
	void removenemies(); //remove all enemies
	virtual CSprite* getEnemy();
	virtual float get_x();
	virtual float get_y();

};

#endif // !ENEMY_H
