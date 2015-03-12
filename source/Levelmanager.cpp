#include "Levelmanager.h"

LevelMaager *LevelMaager::instance = nullptr;

LevelMaager::LevelMaager(){

}

LevelMaager *LevelMaager::getInstance(){
	if (instance == nullptr)
		instance = new LevelMaager;
	return instance;
}

