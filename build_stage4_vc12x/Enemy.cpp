#include "Enemy.h"

Enemy *Enemy::single_instance = NULL;

Enemy *Enemy::getInstance(float height, float width){
	if (single_instance == NULL)
		single_instance = new Enemy(height,width);
	return single_instance;
}

Enemy::Enemy(float height, float width){
	this->height = height;
	this->width = width;
}
Enemy::Enemy(){


}


CSprite *Enemy::addEnemy(CIw2DImage* image){
	CSprite * newenemy = new CSprite();
	newenemy->SetImage(image);
	newenemy->m_X = width/2;
	newenemy->m_Y = 0;
	newenemy->m_H = image->GetHeight();
	newenemy->m_Y = image->GetWidth();
	enemies.insert(enemies.begin(),newenemy);
	return newenemy;
}

void Enemy::update(){
	removenemies();
}

void Enemy::removenemies(){

	for (auto & enemy : enemies){

		if (enemy->m_X <= 0){

			enemy->RemoveChild(enemy); //need to verify this one
			delete(enemy);
			enemies.erase(&enemy);
			
		}

	}

}

CSprite* Enemy::getEnemy(){
	return encounter;
}