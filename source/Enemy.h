#ifndef ENEMY_H
#define ENEMY_H

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "resources.h"



class Enemy : public CSprite
{
private:
	float speed = 0;
	
	
	

public:
	
	virtual ~Enemy();
	Enemy(CIw2DImage * enemy_image, float x, float y);
	
	
	

};

extern float g_graphicsScale;
extern Resources * g_pResources;

#endif // !ENEMY_H
