#include "BackgroundEntity.h"
#include "IwGx.h"

BackgroundEntity::BackgroundEntity(CIw2DImage * background_entity_image, float x, float y) : CSprite()
{

	SetImage(background_entity_image);
	m_X = x * (float)IwGxGetScreenWidth();
	m_Y = y * (float)IwGxGetScreenHeight();
	m_W = GetImage()->GetWidth();
	m_H = GetImage()->GetHeight();

	m_ScaleX = g_graphicsScaleWidth;
	m_ScaleY = g_graphicsScaleHeight;
}

BackgroundEntity::~BackgroundEntity()
{

}
