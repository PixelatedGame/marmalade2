#ifndef SPRITE_H
#define SPRITE_H


#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <string>
#include "Iw2D.h"


class Sprite{
private:

	char* img_path;
	CIw2DImage *temp_img;
protected:

	int current_clip = 0;
	int number_of_clip_lines = 1;
	int number_of_clip_rows = 1;

	CIwFVec2 clips[16];
	
	std::vector<CIw2DImage *> texture_vector;


public:
	CIwFVec2 rect;

	Sprite(std::string sprite_file = "spritez.png", CIwFVec2 rect = { 200, 200 });
	void render();


	
};

#endif // !SPRITE_H
