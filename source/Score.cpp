#include "Score.h"

void Score::add_score(int amount)
{	
	score += amount;
}

void Score::dec_score(int amount)
{
	score -= amount;
}

int Score::reset_score()
{
	score = 0;
	return score;
}

int Score::get_score()
{
	return score;
}

Score *Score::s_instance = 0;