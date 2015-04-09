#ifndef SCORE_H
#define SCORE_H

class Score
{
private:
	int score = 0;
	static Score * s_instance;
	Score(int amount = 0)
	{
		score = amount;
	}
public:
	static Score *instance()
	{
		if (!s_instance)
			s_instance = new Score;
		return s_instance;
	}
	
	void add_score(int);
	void dec_score(int);
	int get_score();
	int reset_score();
};

#endif // !SCORE_H
