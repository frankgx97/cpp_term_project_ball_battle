#include "stdafx.h"
#include "enemy.h"


enemy::enemy(int ene):ball (ene)//��ʼ��һ��������ȫ���//�Ӳ�����Ϊ�˱������ball��Ĺ��캯��
{
	//����뾶��λ��
	r = rand()%40 + 3;//����뾶3-40֮��
	pos_x = rand()%(GRAPH_W - r) + r;//����������ڻ����ϵ�λ��
	pos_y = rand()%(GRAPH_H - r) + r;
	DREC.x = rand()%(30) - 25;//������ɳ�ʼ���˶�״̬
	DREC.y = rand()%(30) - 25;
	//�����ɫ
	color = RGB((rand()%254 + 1), (rand()%254 + 1), (rand()%254 + 1));
	draw();//����
	cout << "x " << pos_x << "y " << pos_y << "r " << r <<endl;
	return;
}

int enemy::move(int add)
{
	//int flag = rand()%1000 + 1;

	/*if (flag <= 2)//��1/500�ĸ������������˶�״̬
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

	//���ڷ���
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