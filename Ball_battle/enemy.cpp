#include "stdafx.h"
#include "enemy.h"


enemy::enemy(int ene):ball (ene)//初始化一个敌人球，全随机//加参数是为了避免调用ball类的构造函数
{
	//随机半径及位置
	r = rand()%40 + 3;//如果半径3-40之间
	pos_x = rand()%(GRAPH_W - r) + r;//随机生成其在画布上的位置
	pos_y = rand()%(GRAPH_H - r) + r;
	DREC.x = rand()%(30) - 25;//随机生成初始的运动状态
	DREC.y = rand()%(30) - 25;
	//随机颜色
	color = RGB((rand()%254 + 1), (rand()%254 + 1), (rand()%254 + 1));
	draw();//绘制
	cout << "x " << pos_x << "y " << pos_y << "r " << r <<endl;
	return;
}

int enemy::move(int add)
{
	//int flag = rand()%1000 + 1;

	/*if (flag <= 2)//有1/500的概率重新生成运动状态
	{
		DREC.x = rand()%((20 - get_r())*3) - (20 - get_r())*2;
		DREC.y = rand()%((20 - get_r())*3) - (20 - get_r())*2;
	}*/

	pos_x_prev = pos_x;
	pos_y_prev = pos_y;

	pos_x += DREC.x;
	pos_y += DREC.y;

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


void enemy::clear_prev()
{
	clearcircle(pos_x_prev,pos_y_prev,r);
	return;
}