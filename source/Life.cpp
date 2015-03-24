#include "Life.h"

int Life::get_life() {
	return (int)life_meter.size();
}

bool Life::add_life() {
	CSprite * life_sprite = new CSprite();

	life_sprite->SetImage(g_pResources->getDodoHead());
	life_sprite->m_X = current_x;
	life_sprite->m_Y = current_y;
	life_sprite->m_W = life_sprite->GetImage()->GetWidth();
	life_sprite->m_H = life_sprite->GetImage()->GetHeight();
	life_sprite->m_ScaleX = g_graphicsScaleWidth / 3;
	life_sprite->m_ScaleY = g_graphicsScaleWidth / 3;
	life_meter.push_back(life_sprite);
	current_x = current_x + (life_sprite->m_W * life_sprite->m_ScaleX) + 5;
	
	return true;
}

bool Life::dec_life() {
	if (!life_meter.empty()) {
		life_meter.pop_back();
		return true;
	}
	return false;
}

CSprite * Life::get_last() {
	if (!life_meter.empty()) {
		return life_meter.back();
	}
	return false;
}

Life::Life()
{
	for (int i = 0; i < init_num_of_lives; ++i) {
		add_life();
	}
}

Life::~Life()
{

}
