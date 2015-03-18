#if !defined(__SHARK_H__)
#define __SHARK_H__

#include "enemy.h"
#include "IwGx.h"


class Shark : public Enemy
{
public:
	Shark()
		: Enemy(g_pResources->getShark(), IwGxGetScreenHeight() * 0.46, IwGxGetScreenWidth() * 0.5) {

	};
	void Update();
};

#endif  // __SHARK_H__