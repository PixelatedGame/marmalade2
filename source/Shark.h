#if !defined(__SHARK_H__)
#define __SHARK_H__

#include "Entity.h"
#include "IwGx.h"


class Shark : public Entity
{
public:
	Shark()
		: Entity(g_pResources->getShark(), (float)IwGxGetScreenWidth(), (float)IwGxGetScreenHeight() * 0.60f) {

	};
	void Update();
};

#endif  // __SHARK_H__