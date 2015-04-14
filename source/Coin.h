#if !defined(__COIN_H__)
#define __COIN_H__

#include "Item.h"
#include "IwGx.h"


class Coin : public Item
{
public:
	Coin(CIw2DImage * image, float x, float y)
		: Item(image, x, y) {

	};
	void Update();
	void picked_up();
};

#endif  // __COIN_H__