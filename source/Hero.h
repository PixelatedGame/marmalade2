#if !defined(__HERO_H__)
#define __HERO_H__

#include "Iw2DSceneGraph.h"
#include "Entity.h"

using namespace Iw2DSceneGraph;

/*
This is a singleton class that mannage the hero character.
*/  
class Hero
{
	int lives;
	static Hero* Single_instance;
	//Hero();
	Hero(float initial, float low, float up);
	float surf, duck, jump;
	enum type { BIGGER, SMALLER, EQUALITY };
	enum state { SURF, TODUCK, DUCK, JUMP, FALL, DRIFT };
	state current_state;
	Entity *dodo;
	long unsigned counter;

public:
	static Hero *instance(float initial, float low, float up);
	float time;
	bool need_update;
	float new_y;
	Entity* getHero();
	~Hero();
	float get_y();
	float get_time();
	bool reset();   //return true to indicate that sucssefuly reset
	void touch();   //return true is Hero had changes and need an update otherwise false
	void untouch(); //return true is Hero had changes and need an update otherwise false
	bool gettopoint(float target, type cases=EQUALITY); //return true if hero get to the point
	void update(float initial, float low, float up);

};


#endif //__HERO_H__
