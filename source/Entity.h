#ifndef ENEMY_H
#define ENEMY_H

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "resources.h"
#include "scene.h"

using namespace IwTween;

class Entity : public CSprite
{
private:
	float speed = 0;
	bool being_hurt = false;
	void _resetHurt();
	
	

public:
	
	virtual ~Entity();
	Entity(CIw2DImage * enemy_image, float x, float y);
	
	
	

	Entity();
	
	void Hurt();
	void Update(float deltaTime, float alphaMul);
};

extern float g_graphicsScaleWidth;
extern float g_graphicsScaleHeight;
extern Resources * g_pResources;
extern SceneManager * g_pSceneManager;

#endif // !ENEMY_H
