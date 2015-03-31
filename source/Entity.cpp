#include "Entity.h"


Entity::Entity(CIw2DImage * entity_image, float x, float y) : CSprite()
{

	SetImage(entity_image);
	m_X = x;
	m_Y = y;
	m_W = GetImage()->GetWidth();
	m_H = GetImage()->GetHeight();

	m_ScaleX = g_graphicsScaleWidth;
	m_ScaleY = g_graphicsScaleHeight;
}

void Entity::_resetHurt()
{
	
	m_Angle = 0;

}
void Entity::Hurt()
{
	if (!being_hurt) {
		being_hurt = true;
		g_pSceneManager->GetCurrent()->GetTweener().Tween(0.5f,
			FLOAT, &this->m_Angle, -15.0f,
			FLOAT, &this->m_Alpha, 0.0f,
			BOOL, &this->being_hurt, false,
			EASING, Ease::sineIn,
			END);

	}
	
}

void Entity::Update(float deltaTime, float alphaMul)
{
	CSprite::Update(deltaTime, alphaMul);
	if (!being_hurt && m_Angle) {
		m_Angle = 0;
		m_Alpha = 1;
	}
	
	


}

Entity::Entity() : CSprite()
{
}

Entity::~Entity()
{

}
