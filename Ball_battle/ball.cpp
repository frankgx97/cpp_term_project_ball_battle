#include "stdafx.h"
#include "ball.h"
#include "enemy.h"


ball::ball()//初始化一个球
{
	r = 25;//如果参数没有指定则球半径为20,
	pos_x = rand()%(GRAPH_W - r) + r;//随机生成其在画布上的位置
	pos_y = rand()%(GRAPH_H - r) + r;
	DREC.x = 0;
	DREC.y = 0;
	color = RED;
	draw();//绘制
}

ball::ball(int ene)
{
}

void ball::draw()
{
	BeginBatchDraw();
	clear_prev();
	EndBatchDraw();
	setfillcolor(color);
	fillcircle(pos_x,pos_y,r);//绘制一个球
	
}

int ball::up()
{
	DREC.y -= 2;
	move();
	return 0;
}

int ball::down()
{
	DREC.y += 2;
	move();
	return 0;
}

int ball::left()
{
	DREC.x -= 2;
	move();
	return 0;
}

int ball::right()
{
	DREC.x += 2;
	move();
	return 0;
}

int ball::move(int add)
{
	if (add)
	{
		spt_flg = S;
		prev_r = r;
		chg_r(- r*0.08);
	}
	else
	{
		spt_flg = 1;
		prev_r = r;
	}

	pos_x_prev = pos_x;
	pos_y_prev = pos_y;
	

	pos_x += DREC.x * spt_flg;
	pos_y += DREC.y * spt_flg;

	if (DREC.x > 30)
		DREC.x = 30;
	if (DREC.y > 30)
		DREC.y = 30;

	//碰壁反弹
	if (pos_x + r >= GRAPH_W ||pos_x - r <= 0)
		DREC.x = - DREC.x;
	if (pos_y + r >= GRAPH_H ||pos_y - r <= 0)
		DREC.y = - DREC.y;

	return 0;
}

int ball::get_direction(int direct_key)
{
	switch (direct_key)
	{
	case LEFT:
		left();
		break;
	case RIGHT:
		right();
		break;
	case DOWN:
		down();
		break;
	case UP:
		up();
		break;
	case NULL:
		move();
		break;
	case VK_SPACE:
		move(S);
		break;
	}
	return 0;
}

void ball::clear_prev()
{
	clearcircle(pos_x_prev,pos_y_prev,prev_r);
	spt_flg = FALSE;
	return;
}


int ball::get_x()
{
	return pos_x;
}

int ball::get_y()
{
	return pos_y;
}

int ball::get_r()
{
	return r;
}

int ball::chg_r(int delta_r)
{
	r += delta_r;
	return r;
}