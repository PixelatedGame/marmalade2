#include "Enemy.h"


Enemy::Enemy(CIw2DImage * enemy_image, float x, float y) : CSprite()
{
	
	SetImage(enemy_image);
	m_X = x;
	m_Y = y;
	m_W = GetImage()->GetWidth();
	m_H = GetImage()->GetHeight();

	m_ScaleX = g_graphicsScaleWidth;
	m_ScaleY = g_graphicsScaleHeight;
}

Enemy::~Enemy()
{

}
