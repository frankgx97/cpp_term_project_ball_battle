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

#define GRAPH_W 640 //������
#define GRAPH_H 480 //������

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define S 4 //���ʱ�ĸ����ٶ���ֵ

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
	//int direction;//����
	struct direction
	{
		int x,y;
	}direct;

	int spt_flg;//����Ƿ��̵�flag�����ھ��������һ֡ʱ�Ķ�λ

	COLORREF color;

	int up();//�ĸ�������ƶ�����ͬ
	int down();
	int left();
	int right();

	

public:
	ball();//��ʼ��һ����
	ball(int ene);//�������˵Ĺ��캯��
	void draw();//�ڻ����ϻ���һ����
	virtual void clear_prev();//���ǰһ֡��Բͼ��//��private

	int get_direction(int);//�����̲�������
	virtual int move(int add = 0);//û�в���ʱĬ���ƶ�//��private
	//int eat(enemy);//����
	//int spt();//���
	
	int get_x();
	int get_y();
	int get_r();
	
	int bounce();//ײǽʱ����
	int chg_r(int);//�ı����
	//int chk_atk(struct enemies *head);//����Ƿ���Թ���
};

