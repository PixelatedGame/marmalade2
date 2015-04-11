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


//-----------Hero State------------------------------------
HeroState::HeroState(float high, float low) : high_boundry(high), low_boundry(low) {};


void HeroState::handleInput(Hero*const& my_hero, bool is_touch)
{
	if (is_touch)
		touch(my_hero);
	else
		release(my_hero);
}

bool HeroState::is_below_low_boundry(Hero*const& my_hero){
	if (my_hero->m_Y == low_boundry)
		return true;
	else
		return false; 
}

bool HeroState::is_above_high_boundry(Hero*const& my_hero){
	if (my_hero->m_Y == high_boundry)
		return true;
	else
		return false;
}
float HeroState::get_low_boundry(){
	return low_boundry;
}
float HeroState::get_high_boundry(){
	return high_boundry;
}


void HeroState::SetAtlas(CIw2DImage* pImage, int x_frames, int y_frames){
	int frame_w = (int)(pImage->GetWidth() / x_frames);
	int frame_h = (int)(pImage->GetHeight() / y_frames);
	int frame_num = x_frames * y_frames;
	state_atlas = new CAtlas(frame_w, frame_h, frame_num, pImage);
}

//----------------------Hero State Surf------------------------------------------------
HeroStateSurf::HeroStateSurf(float high, float low) : HeroState(high, low) {};


void HeroStateSurf::touch(Hero*const& my_hero)
{
	my_hero->changeState(my_hero->state_toduck);
}

void HeroStateSurf::release(Hero*const& my_hero)
{
	//nothing here
}

void HeroStateSurf::start(Hero*const& my_hero){
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}
//-----------------------Hero State To Duck ----------------------------------------

HeroStateToDuck::HeroStateToDuck(float high, float low) : HeroState(high, low) {};


void HeroStateToDuck::touch(Hero*const& my_hero)
{
	if (is_below_low_boundry(my_hero))

		my_hero->changeState(my_hero->state_duck);
}

void HeroStateToDuck::release(Hero*const& my_hero)
{
	my_hero->changeState(my_hero->state_jump);
}

void HeroStateToDuck::start(Hero*const& my_hero){
	my_hero->changelocation(get_low_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

//----------------------Hero State Duck------------------------------------------------
HeroStateDuck::HeroStateDuck(float high, float low) : HeroState(high, low) {};


void HeroStateDuck::touch(Hero*const& my_hero)
{
	//nothing here
}

void HeroStateDuck::release(Hero*const& my_hero)
{
	my_hero->changeState(my_hero->state_jump);
}

void HeroStateDuck::start(Hero*const& my_hero){
	//nothing here
	//if will be a jump-meter then it will be reset here
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

//----------------------Hero State Jump------------------------------------------------
HeroStateJump::HeroStateJump(float high, float low) : HeroState(high, low) {};


void HeroStateJump::touch(Hero*const& my_hero)
{
	my_hero->changeState(my_hero->state_dive);
}

void HeroStateJump::release(Hero*const& my_hero)
{
	if (is_above_high_boundry(my_hero))
		my_hero->changeState(my_hero->state_fall);
}

void HeroStateJump::start(Hero*const& my_hero){
	my_hero->changelocation(get_high_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

//----------------------Hero State Fall------------------------------------------------
HeroStateFall::HeroStateFall(float high, float low) : HeroState(high, low) {};


void HeroStateFall::touch(Hero*const& my_hero)
{
	my_hero->changeState(my_hero->state_dive);
}

void HeroStateFall::release(Hero*const& my_hero)
{
	if (is_below_low_boundry(my_hero))
		my_hero->changeState(my_hero->state_surf);
}

void HeroStateFall::start(Hero*const& my_hero){
	my_hero->changelocation(get_low_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

//----------------------Hero State Dive------------------------------------------------
HeroStateDive::HeroStateDive(float high, float low) : HeroState(high, low) {};


void HeroStateDive::touch(Hero*const& my_hero)
{
	if (is_below_low_boundry(my_hero))
		my_hero->changeState(my_hero->state_toduck);
}

void HeroStateDive::release(Hero*const& my_hero)
{
	if (is_below_low_boundry(my_hero))
		my_hero->changeState(my_hero->state_surf);
}

void HeroStateDive::start(Hero*const& my_hero){
	//fixme: need to change in future for taking in account the m_Y
	my_hero->changelocation(get_low_boundry(), 0.2f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}


//-------------------------Hero-------------------------------------------
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
	state_toduck = new HeroStateToDuck(high_boundry, low_boundry);
	state_duck = new HeroStateDuck(low_boundry, low_boundry);
	state_jump = new HeroStateJump(high_boundry, low_boundry);
	state_fall = new HeroStateFall(high_boundry, middle_boundry);
	state_dive = new HeroStateDive(high_boundry, middle_boundry);

	
	current_state = state_surf;
	
	m_X = g_graphicsScaleWidth * INITIAL_X_POSITION;
	m_Y = g_graphicsScaleHeight * MIDDLE_BOUNDRY;


};

void Hero::changelocation(float next_Y, float change_time = 0.5f){
	if (tween) {
		//tween->Cancel();
		//tween->Restart();

	}
	tween = g_pSceneManager->GetCurrent()->GetTweener().Tween(change_time,
		FLOAT, &this->m_Y, next_Y,
		EASING, Ease::sineIn,
		END);

	
}

void Hero::changeState(HeroState * next_state){
	current_state = next_state;
	current_state->start(this);
}

void Hero::touch()
{


	current_state->handleInput(this, true);
}
void Hero::release()
{
	current_state->handleInput(this, false);
}
void Hero::hurt()
{

}
/*
void Hero::SetImage(CIw2DImage* pImage, int x_frames, int y_frames){
	int frame_w = (int)(pImage->GetWidth() / x_frames);
	int frame_h = (int)(pImage->GetHeight() / y_frames);
	int frame_num = x_frames * y_frames;
	hero_atlas = new CAtlas(frame_w, frame_h, frame_num, pImage);
	SetAnimDuration(2);
	SetAtlas(hero_atlas);
}
*/

void Hero::start(){
	current_state->start(this);
}

//Set animation for surf staet
void Hero::setatlassurf(CIw2DImage* pImage, int x_frames, int y_frames){
	state_surf->SetAtlas(pImage, x_frames, y_frames);
}

//set animation for to duck state
void Hero::setatlastoduck(CIw2DImage* pImage, int x_frames, int y_frames){
	state_toduck->SetAtlas(pImage, x_frames, y_frames);
}

//set animation for duck state
void Hero::setatlasduck(CIw2DImage* pImage, int x_frames, int y_frames){
	state_duck->SetAtlas(pImage, x_frames, y_frames);
}

//set animation for jump state
void Hero::setatlasjump(CIw2DImage* pImage, int x_frames, int y_frames){
	state_jump->SetAtlas(pImage, x_frames, y_frames);
}

//set animation for dive state
void Hero::setatlasdive(CIw2DImage* pImage, int x_frames, int y_frames){
	state_dive->SetAtlas(pImage, x_frames, y_frames);
}

//set animation for fall state
void Hero::setatlasfall(CIw2DImage* pImage, int x_frames, int y_frames){
	state_fall->SetAtlas(pImage, x_frames, y_frames);
}