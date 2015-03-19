#include "Enemymanager.h"
/*
Guy hod, ze lo tov,
Amar Lanu Ha shcriber,
Yesh Dvarim Tovim.
*/
EnemyManager *EnemyManager::instance = NULL;

EnemyManager *EnemyManager::getInstance(){
	if (instance == NULL)
		instance = new EnemyManager();
	return instance;
}

EnemyManager::EnemyManager(){
	currentScene = g_pSceneManager->GetCurrent();
}

void EnemyManager::addEnemy(Enemy *new_enemy){
	
	enemy_vector.push_back(new_enemy);
}



void EnemyManager::update(float time){


}