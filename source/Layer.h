#ifndef LAYER_H
#define LAYER_H

#include "Iw2DSceneGraphCore.h"
#include "Iw2DSceneGraph.h"
#include "Entity.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Layer : public CNode
{
private:
public:
	bool check_collision(Entity *);
};

#endif // !LAYER_H
