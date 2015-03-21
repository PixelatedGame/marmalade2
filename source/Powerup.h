#ifndef POWERUP_H
#define POWERUP_H

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "resources.h"
#include "scene.h"

using namespace IwTween;

class Powerup : public CSprite
{
private:
public:
	virtual ~Powerup();
	Powerup();
	Powerup(CIw2DImage * enemy_image, float x, float y);
};

extern float g_graphicsScaleWidth;
extern float g_graphicsScaleHeight;
extern Resources * g_pResources;
extern SceneManager * g_pSceneManager;


#endif // !POWERUP_H
