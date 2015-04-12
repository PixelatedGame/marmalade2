#include "BackgroundEntity.h"
#include "IwGx.h"

//BackgroundEntity::BackgroundEntity(CIw2DImage * background_entity_image, float x, float y) : CSprite()
BackgroundEntity::BackgroundEntity(CIw2DImage * background_entity_image, float x, float y, int x_frames, int y_frames) : CSprite()
{
	int frame_w = (int)(background_entity_image->GetWidth() / x_frames);
	int frame_h = (int)(background_entity_image->GetHeight() / y_frames);
	int frame_num = x_frames * y_frames;

//	SetImage(background_entity_image);
	m_X = x * (float)IwGxGetScreenWidth();
	m_Y = y * (float)IwGxGetScreenHeight();
//	m_W = GetImage()->GetWidth();
//	m_H = GetImage()->GetHeight();

	m_ScaleX = g_graphicsScaleWidth;
	m_ScaleY = g_graphicsScaleHeight;


	atlas = new CAtlas(frame_w, frame_h, frame_num, background_entity_image);


	SetAnimDuration(2);
	SetAtlas(atlas);

}





BackgroundEntity::~BackgroundEntity()
{

}
