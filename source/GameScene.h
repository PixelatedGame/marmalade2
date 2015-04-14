/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#if !defined(__GAME_H__)
#define __GAME_H__

#include <string>
#include <vector>
#include <map>
#include "Layer.h"
#include "scene.h"
#include "hero.h"
#include "Life.h"
#include "Score.h"


#define FONT_HEIGHT             15
#define FONT_DESIGN_WIDTH       320
#define GRAPHIC_DESIGN_WIDTH    1136
#define GRAPHIC_DESIGN_HEIGHT   640

class GameScene : public Scene
{
protected:
    int             currentRoundScore;              // Current round score
//	long unsigned counter=0;
//	enum state {SURF, TODUCK, DUCK, JUMP, FALL, DRIFT};
//	state current_state = SURF;
    // UI components
    CLabel*           scoreLabel;
    CSprite*          pauseSprite;
	Life*			  lifeMeter;
    Hero*             gemSprite;
	



	float               fontScale;                      // Font is correct size on 320 wide screen so we scale to match native screen size
	float               actualFontHeight;               // The actual pixel height of the font
	float               graphicsScale;                  // Graphics are designed for 768 wide screen so we scale to native screen size

private:
	
	void addToLayer(std::string layerName, CDrawable * drawable);
	Layer * backgroundLayer;
	Layer * enemyLayer;
	Layer * itemLayer;
	Layer * heroLayer;
	Layer * foregroundLayer;
	Layer * uiLayer;
	std::map<std::string, Layer *> layerMap;
	

	void            initUI();
	void InitLayers();
	//	void			addenemy();
public:

    GameScene() {}
    ~GameScene();

    // initialise the game
    void            Init();

	void initHero();

	void initEnemies();
	void initItems();

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the game
    void            Render();

    void            switchToScene(const char* scene_name);
    void            addToRoundScore(int score);
    void            pauseGame();
    void            resumeGame();
    void            newGame();
};


#endif  // __GAME_H__


