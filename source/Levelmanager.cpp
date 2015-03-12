#include "Levelmanager.h"

LevelMaager *LevelMaager::instance = NULL;

LevelMaager::LevelMaager(){

}

LevelMaager *LevelMaager::getInstance(){
	if (instance == NULL)
		instance = new LevelMaager;
	return instance;
}

