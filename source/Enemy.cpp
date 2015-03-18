#include "Enemy.h"


Enemy::Enemy(CIw2DImage * enemy_image, float x, float y) : CSprite()
{
	
	SetImage(enemy_image);
	m_X = x;
	m_Y = y;
	m_W = GetImage()->GetWidth();
	m_H = GetImage()->GetHeight();
	m_AnchorX = 0.5;
	m_ScaleX = g_graphicsScale;
	m_ScaleY = g_graphicsScale;
}

Enemy::~Enemy()
{

}
