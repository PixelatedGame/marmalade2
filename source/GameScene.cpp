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

#include "IwGx.h"

#include "IwHashString.h"

#include "GameScene.h"
#include "input.h"
#include "audio.h"
#include "pauseMenu.h"
#include "resources.h"
#include "Shark.h"

GameScene::~GameScene()
{
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

    // Reset gem position
	gemSprite->getHero()->m_X = (float)IwGxGetScreenWidth() * 4 / 30;
	gemSprite->getHero()->m_Y = (float)IwGxGetScreenHeight() * 0.46f;
}

void GameScene::Update(float deltaTime, float alphaMul)
{
	
    if (!m_IsActive)
        return;

    // Update base scene
    Scene::Update(deltaTime, alphaMul);


	//test for enemy
	if (gemSprite->getHero()->m_Y > (float)IwGxGetScreenHeight() * 0.46f){
	//	enemies->addEnemy();
	}


	//interaction: screen touch
	if (m_IsInputActive && g_pInput->m_Touched)
	{
		gemSprite->touch();
	}

	//interaction: untouch screen
	if (m_IsInputActive && !g_pInput->m_Touched)
	{
		gemSprite->untouch();
	}
	
	//update enemies
//	enemies->update(0.1f);


	//update dodo
	if (gemSprite->need_update){
		//gemSprite create new values -> update twin
		m_Tweener.Tween(gemSprite->time,
			FLOAT, &gemSprite->getHero()->m_Y, gemSprite->new_y,
			EASING, Ease::sineIn,
			END);
	}
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
}

void GameScene::Render()
{
    Scene::Render();
}

void GameScene::addToLayer(CNode * layer, CDrawable * drawable)
{
	layer->AddChild(drawable);
}


// Initialise the games user interface
void GameScene::initUI()
{
    // Create background
    CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getGameBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    
	addToLayer(backgroundLayer, background);
//	current_state = SURF;

	oceanSprite = new CSprite();
	oceanSprite->m_X = 0;
	oceanSprite->m_Y = 0;
	oceanSprite->SetImage(g_pResources->getOcean());
	oceanSprite->m_W = oceanSprite->GetImage()->GetWidth();
	oceanSprite->m_H = oceanSprite->GetImage()->GetHeight();
	oceanSprite->m_ScaleX = graphicsScale;
	oceanSprite->m_ScaleY = graphicsScale;

	//oceanSprite->m_ScaleX = (float)IwGxGetScreenWidth() / oceanSprite->GetImage()->GetWidth();
	//oceanSprite->m_ScaleY = (float)IwGxGetScreenHeight() / oceanSprite->GetImage()->GetHeight();
	
	addToLayer(backgroundLayer, oceanSprite);


	islandSprite = new CSprite();
	islandSprite->SetImage(g_pResources->getIsland());
	islandSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	islandSprite->m_Y = 0;
	islandSprite->m_W = islandSprite->GetImage()->GetWidth();
	islandSprite->m_H = islandSprite->GetImage()->GetHeight();
	islandSprite->m_AnchorX = 0.5;
	islandSprite->m_ScaleX = graphicsScale;
	islandSprite->m_ScaleY = graphicsScale;
	
	addToLayer(backgroundLayer, islandSprite);


    // Create score label text
    CLabel* scoreLabelText = new CLabel();
    scoreLabelText->m_X = 10;
    scoreLabelText->m_Y = 0;
    scoreLabelText->m_W = (float)IwGxGetScreenWidth();
    scoreLabelText->m_H = 30;
    scoreLabelText->m_Text = "Score:";
    scoreLabelText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabelText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabelText->m_Font = g_pResources->getFont();
    scoreLabelText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
	addToLayer(uiLayer, scoreLabelText);

    // Create score label (displays actual score)
    scoreLabel = new CLabel();
    scoreLabel->m_X = 80;
    scoreLabel->m_Y = 0;
    scoreLabel->m_W = (float)IwGxGetScreenWidth();
    scoreLabel->m_H = 30;
    scoreLabel->m_Text = "0";
    scoreLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    scoreLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
    scoreLabel->m_Font = g_pResources->getFont();
    scoreLabelText->m_Color = CColor(0xff, 0xff, 0xff, 0xff);
    
	addToLayer(uiLayer, scoreLabel);

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
	addToLayer(uiLayer, pauseSprite);


}

void GameScene::InitLayers()
{
	backgroundLayer = new CNode();
	AddChild(backgroundLayer);
	enemyLayer = new CNode();
	AddChild(enemyLayer);
	heroLayer = new CNode();
	AddChild(heroLayer);
	foregroundLayer = new CNode();
	AddChild(foregroundLayer);
	uiLayer = new CNode();
	AddChild(uiLayer);
}

void GameScene::Init()
{
    Scene::Init();
	InitLayers();
	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
    currentRoundScore = 0;	

    // Initialise UI
    initUI();

	
    // Create a gem
	gemSprite = Hero::instance(((float)IwGxGetScreenHeight()*0.46f), ((float)IwGxGetScreenHeight()*0.77f), ((float)IwGxGetScreenHeight()*0.14f));
    gemSprite->getHero()->m_X = (float)IwGxGetScreenWidth() / 2;
    gemSprite->getHero()->m_Y = (float)IwGxGetScreenHeight() / 2;
	gemSprite->getHero()->SetImage(g_pResources->getGem());
	gemSprite->getHero()->m_W = (float)gemSprite->getHero()->GetImage()->GetWidth();
	gemSprite->getHero()->m_H = (float)gemSprite->getHero()->GetImage()->GetHeight();
	gemSprite->getHero()->m_ScaleX = graphicsScale/2;
	gemSprite->getHero()->m_ScaleY = graphicsScale/2;
	gemSprite->getHero()->m_AnchorX = 0.5f;
    //gemSprite->SetAnimDuration(2);
	addToLayer(heroLayer, gemSprite->getHero());
	//AddChild(gemSprite->getHero());

	Shark * sharky = new Shark();
	addToLayer(enemyLayer, sharky);

	m_Tweener.Tween(15.0f,
		FLOAT, &sharky->m_X, 0.0f,
		EASING, Ease::sineIn,
		END);

	
}

