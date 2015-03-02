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

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
    CIw2DImage*     Gem;
    CIw2DImage*     MenuBG;
    CIw2DImage*     GameBG;
    CIw2DImage*     MenuButton;
    CIw2DImage*     Placard;
    CIw2DImage*     PauseIcon;
    CIw2DImage*     PlayButton;
    CIw2DFont*      Font;
    CAtlas*         GemAtlas;

	CIw2DImage* Sky;
	CIw2DImage* Island;
	CIw2DImage* DodoJump1;
	CIw2DImage* DodoJump2;
	CIw2DImage* DodoJump3;
	CIw2DImage* DodoJump4;
	CIw2DImage* DodoJump5;
	CIw2DImage* DodoJump6;
public:
    CIw2DImage*     getGem()                    { return Gem; }
    CIw2DImage*     getMenuBG()                 { return MenuBG; }
    CIw2DImage*     getGameBG()                 { return GameBG; }
    CIw2DImage*     getMenuButton()             { return MenuButton; }
    CIw2DImage*     getPlacard()                { return Placard; }
    CIw2DImage*     getPlayButton()             { return PlayButton; }
    CIw2DImage*     getPauseIcon()              { return PauseIcon; }
	CIw2DImage*     getOcean()              { return Sky; }
	CIw2DImage*     getIsland()              { return Island; }
	CIw2DImage*     getDodoJump1()              { return DodoJump1; }
	CIw2DImage*     getDodoJump2()              { return DodoJump2; }
	CIw2DImage*     getDodoJump3()              { return DodoJump3; }
	CIw2DImage*     getDodoJump4()              { return DodoJump4; }
	CIw2DImage*     getDodoJump5()              { return DodoJump5; }
	CIw2DImage*     getDodoJump6()              { return DodoJump6; }
    CIw2DFont*      getFont()                   { return Font; }
    CAtlas*         getGemAtlas()               { return GemAtlas; }


public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


