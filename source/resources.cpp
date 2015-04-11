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

#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
    // Load images
	DodoSurf = Iw2DCreateImage("textures/dodo-atlas.png");
	DodoToDuck = Iw2DCreateImage("textures/dodo-jump-4.png");
	DodoDuck = Iw2DCreateImage("textures/dodo-jump-2.png");
	DodoJump = Iw2DCreateImage("textures/dodo-jump-1.png");
	DodoDive = Iw2DCreateImage("textures/dodo-jump-6.png");
	DodoFall = Iw2DCreateImage("textures/dodo-jump-6.png");
    MenuBG = Iw2DCreateImage("textures/menu_bkg.jpg");
    GameBG = Iw2DCreateImage("textures/layers_0011_background.png");
    MenuButton = Iw2DCreateImage("textures/button_bg.png");
    Placard = Iw2DCreateImage("textures/placard.png");
    PauseIcon = Iw2DCreateImage("textures/pause_icon.png");
    PlayButton = Iw2DCreateImage("textures/play.png");

	Shark = Iw2DCreateImage("textures/layers_0005_shark.png");
	Sky = Iw2DCreateImage("textures/layers_0010_sky.png");
	Island = Iw2DCreateImage("textures/layers_0005_island_and_sun.png");
	wave = Iw2DCreateImage("textures/layers_0009_wave.png");
	splash_back = Iw2DCreateImage("textures/layers_0008_splah_behind_dodo.png");
	splash_front= Iw2DCreateImage("textures/layers_0006_splah_in_front_of_dodo.png");
	DodoJump1 = Iw2DCreateImage("textures/dodo-jump-1.png");
	DodoJump2 = Iw2DCreateImage("textures/dodo-jump-2.png");
	DodoJump3 = Iw2DCreateImage("textures/dodo-jump-3.png");
	DodoJump4 = Iw2DCreateImage("textures/dodo-jump-4.png");
	DodoJump5 = Iw2DCreateImage("textures/dodo-jump-5.png");
	DodoJump6 = Iw2DCreateImage("textures/dodo-jump-6.png");
	DodoHead = Iw2DCreateImage("textures/dodo-head.png");

    // Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");

    // Create gem atlas
    // int frame_w = (int)(Gem->GetWidth() / 5);
    // int frame_h = (int)(Gem->GetHeight() / 3);
    // GemAtlas = new CAtlas(frame_w, frame_h, 15, Gem);
}

Resources::~Resources()
{
	delete DodoSurf;
	delete DodoToDuck;
	delete DodoDuck;
	delete DodoJump;
	delete DodoDive;
	delete DodoFall;
    delete GemAtlas;
    delete MenuBG;
    delete GameBG;
    delete MenuButton;
    delete PauseIcon;
    delete Placard;
    delete PlayButton;
    delete Font;
}

// Global resources
Resources* g_pResources = 0;



