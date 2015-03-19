#ifndef BackgroundEntity_H
#define BackgroundEntity_H

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "resources.h"



class BackgroundEntity : public CSprite
{
private:
	float speed = 0;
	
	
	

public:
	
	virtual ~BackgroundEntity();
	BackgroundEntity(CIw2DImage * BackgroundEntity_image, float x=0, float y=0);
	
	
	

};

extern float g_graphicsScaleWidth;
extern float g_graphicsScaleHeight;
extern Resources * g_pResources;

#endif // !BackgroundEntity_H
