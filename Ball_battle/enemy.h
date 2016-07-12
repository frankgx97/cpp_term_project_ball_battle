#pragma once
#include "ball.h"
class enemy : public ball
{
private:
	int id;
public:
	enemy(int ene);
	void change_color();
	int move(int add = 0);
	void clear_prev();
};

