#include "Layer.h"
#include "Item.h"

bool Layer::check_collision(Entity * sprite)
{
	for (auto child : m_Children) {
		bool a = child->m_X < sprite->m_X + (sprite->m_W * sprite->m_ScaleX);
		bool b = child->m_X + (child->m_W * child->m_ScaleX) > sprite->m_X;
		bool c = child->m_Y < sprite->m_Y + (sprite->m_H * sprite->m_ScaleY);
		bool d = child->m_Y + (child->m_H * child->m_ScaleY)  > sprite->m_Y;
		if (a && b && c && d){
			return true;
		}
	}
	return false;
}
