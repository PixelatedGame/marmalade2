#include "Enemy.h"


Enemy::Enemy(){
	enemyinstance = new CSprite();

}


CSprite* Enemy::getEnemy(){
	return enemyinstance;
	//enemyinstance->SetImage();

}

float Enemy::get_x(){
	return 0;
}

float Enemy::get_y(){
	return 0;
}
/*
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

void Enemy::removenemies(){

	for (auto & enemy : enemies){

		if (enemy->m_X > 0){

			enemy->RemoveChild(enemy); //need to verify this one
			delete(enemy);
			enemies.erase(&enemy);
			
		}

	}

}
*/
