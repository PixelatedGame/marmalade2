#include "Hero.h"


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
	my_hero->killtween();
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


void HeroStateSurf::Update(Hero*const& my_hero){
}
//-----------------------Hero State To Duck ----------------------------------------

HeroStateToDuck::HeroStateToDuck(float high, float low) : HeroState(high, low) {};


void HeroStateToDuck::touch(Hero*const& my_hero)
{

}

void HeroStateToDuck::release(Hero*const& my_hero)
{
	my_hero->killtween();
	my_hero->changeState(my_hero->state_jump);
}

void HeroStateToDuck::start(Hero*const& my_hero){
	my_hero->changelocation(get_low_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}


void HeroStateToDuck::Update(Hero*const& my_hero){
	if (is_below_low_boundry(my_hero)){
		my_hero->changeState(my_hero->state_duck);
	}
}

//----------------------Hero State Duck------------------------------------------------
HeroStateDuck::HeroStateDuck(float high, float low) : HeroState(high, low) {};


void HeroStateDuck::touch(Hero*const& my_hero)
{
	//nothing here
}

void HeroStateDuck::release(Hero*const& my_hero)
{
	//no need to kill tween -> no tween here
	my_hero->changeState(my_hero->state_jump);
}

void HeroStateDuck::start(Hero*const& my_hero){
	//nothing here
	//if will be a jump-meter then it will be reset here
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

void HeroStateDuck::Update(Hero*const& my_hero){

}
//----------------------Hero State Jump------------------------------------------------
HeroStateJump::HeroStateJump(float high, float low) : HeroState(high, low) {};


void HeroStateJump::touch(Hero*const& my_hero)
{
	my_hero->killtween();
	my_hero->changeState(my_hero->state_dive);
}

void HeroStateJump::release(Hero*const& my_hero)
{
}

void HeroStateJump::start(Hero*const& my_hero){
	my_hero->changelocation(get_high_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

void HeroStateJump::Update(Hero*const& my_hero){
	if (is_above_high_boundry(my_hero)){
		my_hero->changeState(my_hero->state_fall);
	}
}
//----------------------Hero State Fall------------------------------------------------
HeroStateFall::HeroStateFall(float high, float low) : HeroState(high, low) {};


void HeroStateFall::touch(Hero*const& my_hero)
{
	my_hero->killtween();
	my_hero->changeState(my_hero->state_dive);
}

void HeroStateFall::release(Hero*const& my_hero)
{
}

void HeroStateFall::start(Hero*const& my_hero){
	my_hero->changelocation(get_low_boundry(), 0.5f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

void HeroStateFall::Update(Hero*const& my_hero){
	if (is_below_low_boundry(my_hero)){
		my_hero->changeState(my_hero->state_surf);
	}
}

//----------------------Hero State Dive------------------------------------------------
HeroStateDive::HeroStateDive(float high, float low) : HeroState(high, low) {};


void HeroStateDive::touch(Hero*const& my_hero)
{

}

void HeroStateDive::release(Hero*const& my_hero)
{

}

void HeroStateDive::start(Hero*const& my_hero){
	//fixme: need to change in future for taking in account the m_Y
	my_hero->changelocation(get_low_boundry(), 0.2f);
	my_hero->SetAnimDuration(2);
	my_hero->SetAtlas(state_atlas);
}

void HeroStateDive::Update(Hero*const& my_hero){
	if (is_below_low_boundry(my_hero)){
		my_hero->changeState(my_hero->state_surf);
	}
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

void Hero::Update(float deltaTime, float alphaMul){
	Entity::Update(deltaTime, alphaMul);
	current_state->Update(this);

}

void Hero::changelocation(float next_Y, float change_time = 0.5f){

	hero_tween = g_pSceneManager->GetCurrent()->GetTweener().Tween(change_time,
		FLOAT, &this->m_Y, next_Y,
		EASING, Ease::sineIn,
		END);	
}

void Hero::killtween(){
	if (hero_tween!=0){
		if (hero_tween->IsAnimating()){
//			hero_tween->Pause();
//			hero_tween->Cancel();
//			hero_tween = 0;
		}
	}
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