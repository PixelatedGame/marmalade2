#include "Coin.h"
#include "Score.h"

void Coin::Update() {
}

void Coin::picked_up()
{
	Score::instance()->add_score(1000);
}
