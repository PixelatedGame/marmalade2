#include "Hero.h"

/*

void Hero::update(float initial, float low, float up){
	
	surf = initial;
	duck = low;
	jump = up;
	
	new_y = surf;
	need_update = false;
}

Entity* Hero::getHero(){
	return dodo;
}

Hero *Hero::Single_instance = NULL;

Hero *Hero::instance(float initial, float low, float up){
	if (Single_instance == NULL)
		Single_instance = new Hero(initial, low, up);
	return Single_instance;
}
Hero::Hero(float initial, float low, float up)
{

	new_y = surf;
	need_update = false;
	current_state = SURF;
	surf = initial;
	duck = low;
	jump = up;
	dodo = new Entity();
	counter = 0;
}


bool Hero::reset(){
	current_state = SURF;
	counter = 0;
	return true;
}

void Hero::touch(){
	need_update = false;


	switch (current_state){
	case SURF:
		current_state = TODUCK;
		need_update = true;
		new_y =  duck;
		time = 0.1f;
		
		break;
	case TODUCK:
		
		if (gettopoint(duck))
			current_state = DUCK;
		break;
	case DUCK:
		//counter++;
		break;
	case JUMP:
		current_state = FALL;
		need_update = true;
		new_y = surf;
		time = 0.1f;
		break;
	case DRIFT:
		current_state = FALL;
		break;

	case FALL:
		if (gettopoint(surf)){
			current_state = SURF;
		}
		break;
	}

}

void Hero::untouch(){
	need_update = false;
	switch (current_state){
	case SURF:
		break;

	case TODUCK:
		current_state = SURF;
		need_update = true;
		new_y = surf;
		time = 0.1f;
		break;

	case DUCK:
		current_state = JUMP;
		need_update = true;
		new_y = jump;
		time = 0.3f;
		break;

	case JUMP:
		if (gettopoint(jump,BIGGER)){
			current_state = DRIFT;
			need_update = true;
			new_y = surf;
			time = 0.3f;
		}

		break;
	case FALL:
		current_state = DRIFT;
		need_update = true;
		new_y = surf;
		time = 0.5f;
		break;
	case DRIFT:
		if (gettopoint(surf)){
			current_state = SURF;
		}
		break;
	}

}

float Hero::get_time(){
	return time;
}

float Hero::get_y(){
	return new_y;
}


bool Hero::gettopoint(float target, type cases){
	bool test;
	switch (cases)
	{
	default:
	case(EQUALITY) :
		//test = ((dodo->m_Y < (target+1.0f)) || (dodo->m_Y > (target-1.0f)));
		test = dodo->m_Y == target;
		break;
	case(SMALLER) :
		test = dodo->m_Y >= (target-0.1f);
		break;
	case(BIGGER) :
		test = dodo->m_Y < (target+0.1f);
		break;
	}
	if (test)
		return true;
	else
		return false;
}
*/

#define HIGH_BOUNDRY 27
#define MIDDLE_BOUNDRY 384
#define LOW_BOUNDRY 416
#define INITIAL_X_POSITION 185

HeroState::HeroState(float high, float low) : high_boundry(high), low_boundry(low) {};
HeroStateSurf::HeroStateSurf(float high, float low) : HeroState(high, low) {};

void HeroStateSurf::handleInput(Hero*const&, bool)
{

}


void HeroStateSurf::touch(Hero*const&)
{

}

void HeroStateSurf::release(Hero*const&)
{

}

Hero * Hero::Single_instance = NULL;


Hero * Hero::get_instance()
{
	if (Single_instance == NULL)
		Single_instance = new Hero();
	return Single_instance;
}

Hero::Hero() : Entity(), low_boundry(g_graphicsScaleHeight * LOW_BOUNDRY), \
middle_boundry(g_graphicsScaleHeight * MIDDLE_BOUNDRY), \
high_boundry(g_graphicsScaleHeight * HIGH_BOUNDRY){
	state_surf = new HeroStateSurf(middle_boundry, middle_boundry);
	
	current_state = state_surf;
	
	m_X = g_graphicsScaleWidth * INITIAL_X_POSITION;
	m_Y = g_graphicsScaleHeight * MIDDLE_BOUNDRY;
};

void Hero::touch()
{
//	current_state->handleInput(this, true);
}
void Hero::release()
{
//	current_state->handleInput(this, false);
}
void Hero::hurt()
{

}
