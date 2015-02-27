#include "Sprite.h"
//#include "globals.h"


using namespace std;

Sprite::Sprite(std::string sprite_file, CIwFVec2 rect)
{
	this->rect = rect;

	//std::vector<SDL_Texture*> texture_vector;

	std::stringstream ss(sprite_file);

	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		img_path = "textures/";
		strcat(img_path, substr.c_str());
		texture_vector.push_back(Iw2DCreateImage(img_path));
//		temp_img = Iw2DCreateImage(img_path);
	}
	this->texture_vector = texture_vector;
}

void Sprite::render() {
	//renderTexture(texture_vector[current_clip], renderer, rect);
	Iw2DDrawImage(texture_vector[current_clip], CIwFVec2::g_Zero);

}