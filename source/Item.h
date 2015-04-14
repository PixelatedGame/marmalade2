#if !defined(__ITEM_H__)
#define __ITEM_H__

#include "Entity.h"
#include "IwGx.h"


class Item : public Entity
{
public:
	Item(CIw2DImage * image, float x, float y)
		: Entity(image, x, y) {

	};
	void Update();
	virtual void picked_up(){};
};

#endif  // __ITEM_H__