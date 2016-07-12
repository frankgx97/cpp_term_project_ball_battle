#pragma once
#include <time.h>
#include <cstdlib>
#include <easyx.h>
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <string>
#include <fstream>
#include <vector>

//#include "enemy.h"

#define GRAPH_W 640 //画布宽
#define GRAPH_H 480 //画布高

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define S 4 //冲刺时的附加速度数值

#define TRUE 1
#define FALSE 0

#define ENE 1
#define DREC direct



using namespace std;


class ball
{
	friend class enemy;
private:
	int pos_x,pos_y;
	int pos_x_prev,pos_y_prev;
	int prev_r;
	int r;
	//int direction;//方向
	struct direction
	{
		int x,y;
	}direct;

	int spt_flg;//标记是否冲刺的flag，用于决定清除上一帧时的定位

	COLORREF color;

	int up();//四个方向的移动，下同
	int down();
	int left();
	int right();

	

public:
	ball();//初始化一个球
	ball(int ene);//用作敌人的构造函数
	void draw();//在画布上绘制一个球
	virtual void clear_prev();//清除前一帧的圆图像//可private

	int get_direction(int);//将键盘操作传入
	virtual int move(int add = 0);//没有操作时默认移动//可private
	//int eat(enemy);//攻击
	//int spt();//冲刺
	
	int get_x();
	int get_y();
	int get_r();
	
	int bounce();//撞墙时反弹
	int chg_r(int);//改变体积
	//int chk_atk(struct enemies *head);//检测是否可以攻击
};

