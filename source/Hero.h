#if !defined(__HERO_H__)
#define __HERO_H__

#include "Iw2DSceneGraph.h"
#include "Entity.h"

using namespace Iw2DSceneGraph;


//forawrd declaration needed for state pattern
class Hero;
class HeroState;
class HeroStateSurf;
class HeroStateToDuck;
class HeroStateDuck;
class HeroStateJump;
class HeroStateFall;
class HeroStateDive;



class HeroState
{
	float high_boundry, low_boundry;
	float velocity;
	virtual void touch(Hero*const&) = 0;
	virtual void release(Hero*const&) = 0;

public:
	CAtlas *state_atlas; //should be protected
	bool is_above_high_boundry(Hero*const&);
	bool is_below_low_boundry(Hero*const&);
	void handleInput(Hero*const&, bool);
	HeroState(float high, float low);
	float get_low_boundry();
	float get_high_boundry();
	virtual void start(Hero*const&) = 0;
	void SetAtlas(CIw2DImage* pImage, int x_frames = 2, int y_frames = 2);
	virtual void Update(Hero*const&) = 0;
};

class HeroStateSurf : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateSurf(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};

class HeroStateToDuck : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateToDuck(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};

class HeroStateDuck : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateDuck(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};

class HeroStateJump : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateJump(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};
class HeroStateFall : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateFall(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};
class HeroStateDive : public HeroState {
	void touch(Hero*const&);
	void release(Hero*const&);
public:
	HeroStateDive(float high, float low);
	void start(Hero*const&);
	void Update(Hero*const&);
};


//Hero is a signalton class that implement state pattern for hero behavior
class Hero : public Entity
{
	friend HeroStateSurf;
	friend HeroStateToDuck;
	friend HeroStateDuck;
	friend HeroStateJump;
	friend HeroStateFall;
	friend HeroStateDive;

	float high_boundry, middle_boundry, low_boundry;
	int jump_power;
	HeroState *current_state;
	HeroStateSurf * state_surf;
	HeroStateToDuck * state_toduck;
	HeroStateDuck * state_duck;
	HeroStateJump * state_jump;
	HeroStateFall * state_fall;
	HeroStateDive * state_dive;

	static Hero* Single_instance;
	int tween_id;
	Hero();
public:
	static Hero *get_instance();
	void Update(float, float);
	void touch();
	void release();
	void hurt();
	void changeState(HeroState * next_state);
	void changelocation(float, float);
	void killtween();
	void start();
	void setatlassurf(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);
	void setatlastoduck(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);
	void setatlasduck(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);
	void setatlasjump(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);
	void setatlasdive(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);
	void setatlasfall(CIw2DImage* pImage, int x_frames = 1, int y_frames = 1);

};

extern float g_graphicsScaleWidth;
extern float g_graphicsScaleHeight;
extern Resources * g_pResources;
extern SceneManager * g_pSceneManager;

#endif //__HERO_H__
