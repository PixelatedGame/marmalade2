#if !defined(__SHARK_H__)
#define __SHARK_H__

#include "enemy.h"
#include "IwGx.h"


class Shark : public Enemy
{
public:
	Shark()
		: Enemy(g_pResources->getShark(), (float)IwGxGetScreenWidth(), (float)IwGxGetScreenHeight() * 0.56f) {

	};
	void Update();
};

#endif  // __SHARK_H__