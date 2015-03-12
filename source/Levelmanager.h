#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include "Level.h"

using namespace std;

class LevelMaager{
private:
	static LevelMaager* instance;
	LevelMaager();
	vector<Level> LevelsList;

public:
	static LevelMaager* getInstance();
};

#endif //__LEVELMANAGER_H