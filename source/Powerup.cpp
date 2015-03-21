#include "Powerup.h"


Powerup::Powerup(CIw2DImage * powerup_image, float x, float y) : CSprite()
{

	SetImage(powerup_image);
	m_X = x;
	m_Y = y;
	m_W = GetImage()->GetWidth();
	m_H = GetImage()->GetHeight();

	m_ScaleX = g_graphicsScaleWidth;
	m_ScaleY = g_graphicsScaleHeight;
}

Powerup::Powerup() : CSprite()
{
}

Powerup::~Powerup()
{

}
