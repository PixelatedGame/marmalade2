#include "Enemymanager.h"

EnemyManager *EnemyManager::instance = nullptr;

EnemyManager *EnemyManager::getInstance(float height, float width){
	if (instance == nullptr)
		instance = new EnemyManager(height, width);
	return instance;
}

EnemyManager::EnemyManager(float height, float width){
	enemyChildrens = new CNode();
}

void EnemyManager::addEnemy(Enemy *newenemy){
	tempEnemy = newenemy;
	enemiesList.insert(tempEnemy);
	enemyChildrens->AddChild(tempEnemy->getEnemy());
}

CNode *EnemyManager::getCNode(){
	return enemyChildrens;
}

void EnemyManager::update(float time){
	/*
	MarMaleDE!!!!!!
	*/

}