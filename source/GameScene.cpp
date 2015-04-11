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

#include <sstream>
#include <string>

#include "IwGx.h"

#include "IwHashString.h"

#include "GameScene.h"
#include "input.h"
#include "audio.h"
#include "pauseMenu.h"
#include "resources.h"
#include "Shark.h"
#include "BackgroundEntity.h"

GameScene::~GameScene()
{
	/*
	delete scoreLabel;
	delete pauseSprite;
	delete lifeMeter;
	delete gemSprite;
	delete backgroundLayer;
	delete enemyLayer;
	delete heroLayer;
	delete foregroundLayer;
	delete uiLayer;
	*/
}

void GameScene::addToRoundScore(int score)
{
    // Add to score
    currentRoundScore += score;

    // Update score label text to show new score
    char str[16];
    snprintf(str, 16, "%d", currentRoundScore);
    scoreLabel->m_Text = str;
}

void GameScene::pauseGame()
{
    // Switch to pause menu scene
    g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));
}

void GameScene::resumeGame()
{
}

void GameScene::newGame()
{
    // Reset score
    currentRoundScore = 0;

	
	lifeMeter->reset_life();

	for (auto dodoHead : lifeMeter->life_meter) {
		addToLayer("uiLayer", dodoHead);
	}

	


	//fixme : Should remove the gemSprite reset position
    // Reset gem position
	//gemSprite->m_X = (float)IwGxGetScreenWidth() * 4 / 30;
	//gemSprite->m_Y = (float)IwGxGetScreenHeight() * 0.46f;
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	
    if (!m_IsActive)
        return;

    // Update base scene
    Scene::Update(deltaTime, alphaMul);


	//interaction: screen touch
	if (m_IsInputActive && g_pInput->m_Touched)
	{
		gemSprite->touch();
	}

	//interaction: untouch screen
	if (m_IsInputActive && !g_pInput->m_Touched)
	{
		gemSprite->release();
	}
	
	//update enemies
//	enemies->update(0.1f);

	/*
	stavi gay;
	//update dodo
	if (gemSprite->need_update){
		//gemSprite create new values -> update twin
		m_Tweener.Tween(gemSprite->time,
			FLOAT, &gemSprite->getHero()->m_Y, gemSprite->new_y,
			EASING, Ease::sineIn,
			END);
	}

	*/
	///end of update dodo

	//update enemy
	

	



	// Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        g_pInput->Reset();
        if (pauseSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
        {
            // Enter pause menu
            pauseGame();
        }
        else
        {
			
            // Move image to touched position
            m_Tweener.Tween(2.0f,
//                            FLOAT, &gemSprite->m_X, (float)g_pInput->m_X,
//                            FLOAT, &gemSprite->m_Y, (float)g_pInput->m_Y,
                            EASING, Ease::sineIn,
                            END);

            // Increase score
            //addToRoundScore(10);

            // Play a sound effect
            g_pAudio->PlaySound("audio/gem_destroyed.wav");
        }
    }

	Score::instance()->add_score(5);

	// Check collision with enemies
	Entity * hero_sprite = gemSprite;
	if (enemyLayer->check_collision(hero_sprite)){
		if ((lifeMeter->get_life() > 0) && (!hero_sprite->is_hurt())) {
			layerMap["uiLayer"]->RemoveChild(lifeMeter->get_last());
			lifeMeter->dec_life();
			if (lifeMeter->get_life() == 0) {
				// Dead :(
				g_pSceneManager->GameOver();
			}
			hero_sprite->Hurt();
			Score::instance()->reset_score();
		} 
	};

	std::stringstream str;
	str << Score::instance()->get_score();
	scoreLabel->SetText(str.str());
	
}

void GameScene::Render()
{
    Scene::Render();
}

void GameScene::addToLayer(std::string layerName, CDrawable * drawable)
{
	layerMap[layerName]->AddChild(drawable);
	//layer->AddChild(drawable);
}


// Initialise the games user interface
void GameScene::initUI()
{
	
	BackgroundEntity* wallpaperSprite = new BackgroundEntity(g_pResources->getGameBG());
	addToLayer("backgroundLayer", wallpaperSprite);

	BackgroundEntity* oceanSprite = new BackgroundEntity(g_pResources->getSky());
	addToLayer("backgroundLayer", oceanSprite);

	BackgroundEntity* islandSprite = new BackgroundEntity(g_pResources->getIsland(), 0.3f);
	addToLayer("backgroundLayer", islandSprite);

	BackgroundEntity* waveSprite = new BackgroundEntity(g_pResources->getWave(),0, 0.78f);
	addToLayer("foregroundLayer", waveSprite);


    // Create score label text
    CLabel* scoreLabelText = new CLabel();
    scoreLabelText->m_X = 10;
    scoreLabelText->m_Y = 5;
    scoreLabelText->m_W = (float)IwGxGetScreenWidth();
    scoreLabelText->m_H = 300;
    scoreLabelText->m_Text = "Score:";
    scoreLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabelText->m_Font = g_pResources->getFont();
    scoreLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
	
	addToLayer("uiLayer", scoreLabelText);

    // Create score label (displays actual score)
    scoreLabel = new CLabel();
    scoreLabel->m_X = 80;
    scoreLabel->m_Y = 5;
    scoreLabel->m_W = (float)IwGxGetScreenWidth();
    scoreLabel->m_H = 30;
    scoreLabel->m_Text = "0";
    scoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabel->m_Font = g_pResources->getFont();
    scoreLabelText->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
    
	addToLayer("uiLayer", scoreLabel);

    // Create pause menu sprite (docked to top of screen)
    pauseSprite = new CSprite();
    pauseSprite->SetImage(g_pResources->getPauseIcon());
    pauseSprite->m_X =  (float)IwGxGetScreenWidth() * 0.8f;
    pauseSprite->m_Y = 0;
    pauseSprite->m_W = pauseSprite->GetImage()->GetWidth();
    pauseSprite->m_H = pauseSprite->GetImage()->GetHeight();
    pauseSprite->m_AnchorX = 0.5;
	pauseSprite->m_ScaleX = graphicsScale;
	pauseSprite->m_ScaleY = graphicsScale;
	addToLayer("uiLayer", pauseSprite);

	lifeMeter = new Life();
	


}

void GameScene::InitLayers()
{
	backgroundLayer = new Layer();
	AddChild(backgroundLayer);
	enemyLayer = new Layer();
	AddChild(enemyLayer);

	foregroundLayer = new Layer();
	AddChild(foregroundLayer);
	heroLayer = new Layer();
	AddChild(heroLayer);
	uiLayer = new Layer();
	AddChild(uiLayer);

	layerMap["backgroundLayer"] = backgroundLayer;
	layerMap["enemyLayer"] = enemyLayer;
	layerMap["heroLayer"] = heroLayer;
	layerMap["foregroundLayer"] = foregroundLayer;
	layerMap["uiLayer"] = uiLayer;

	
}

void GameScene::Init()
{
    Scene::Init();
	InitLayers();
	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
    currentRoundScore = 0;	

    // Initialise UI
    initUI();
	newGame();
	initEnemies();

	initHero();

	Shark * sharky = new Shark();
	addToLayer("enemyLayer", sharky);
	
	IwTween::CTween * tween = m_Tweener.Tween(1.0f,
		FLOAT, &sharky->m_X, 0.0f - sharky->m_W,
		REPEAT,
		EASING, Ease::sineIn,
		END);
	//tween->Cancel();
	


	
}

void GameScene::initHero()
{
	// Create a gem
	gemSprite = Hero::get_instance();
//	gemSprite->m_X = (float)IwGxGetScreenWidth() / 2;
//	gemSprite->m_Y = (float)IwGxGetScreenHeight() / 2;
	gemSprite->SetImage(g_pResources->getGem());
	gemSprite->setatlassurf(g_pResources->getDodoSurf());
	gemSprite->setatlastoduck(g_pResources->getDodoToDuck(),1,1);
	gemSprite->setatlasduck(g_pResources->getDodoDuck(),1,1);
	gemSprite->setatlasjump(g_pResources->getDodoJump(),1,1);
	gemSprite->setatlasdive(g_pResources->getDodoDive(),1,1);
	gemSprite->setatlasfall(g_pResources->getDodoFall(),1,1);
	gemSprite->m_W = (float)gemSprite->GetImage()->GetWidth();
	gemSprite->m_H = (float)gemSprite->GetImage()->GetHeight();
	gemSprite->m_ScaleX = graphicsScale / 3;
	gemSprite->m_ScaleY = graphicsScale / 3;
	
	addToLayer("heroLayer", gemSprite);

}

void GameScene::initEnemies()
{
	
}
