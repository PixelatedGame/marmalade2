#include "Layer.h"

bool Layer::check_collision(CSprite * sprite)
{
	for (auto child : m_Children) {
		bool a = child->m_X < sprite->m_X + sprite->m_W;
		bool b = child->m_X + child->m_W > sprite->m_X;
		bool c = child->m_Y < sprite->m_Y + sprite->m_H;
		bool d = child->m_Y + child->m_H > sprite->m_Y;
		if (a && b && c && d){
			return true;
		}
		/*
		if ((child->m_X < sprite->m_X + sprite->m_W) &&
			(child->m_X + child->m_W > sprite->m_X) &&
			(child->m_Y < sprite->m_Y + sprite->m_H) &&
			(child->m_Y + child->m_H > sprite->m_Y)) {
			return true;
		}
		*/

		/*
		if (child->m_X <= (sprite->m_X + sprite->m_W) &&
			(child->m_X >= sprite->m_X) &&
			(child->m_Y <= (sprite->m_Y + sprite->m_H)) &&
			(child->m_Y >= sprite->m_Y)){
			return true;
		}*/
	}
	return false;
}
