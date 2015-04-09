#ifndef LIFE_H
#define LIFE_H

#include <vector>
#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
//#include "IwTween.h"
#include "resources.h"
#include "scene.h"

//using namespace IwTween;

class Life
{
private:
	int init_num_of_lives = 3;
	int current_x = 10;
	int current_y = 10;
public:
	virtual ~Life();
	Life();
	std::vector<CSprite *> life_meter;
	bool reset_life(int num_of_lives = 3);
	bool add_life();
	bool dec_life();
	int get_life();
	CSprite * get_last();
};

extern float g_graphicsScaleWidth;
extern float g_graphicsScaleHeight;
extern Resources * g_pResources;
extern SceneManager * g_pSceneManager;


#endif // !LIFE_H
