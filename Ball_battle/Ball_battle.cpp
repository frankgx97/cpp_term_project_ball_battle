// Ball_battle.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ball.h"
#include "enemy.h"

#define ENEMY_NUM 2
#define SLEEP_TIME 10
#define JUDGE 1.5

/*����ṹ����*/
struct enemies
{
	enemy *enemy_balls;
	struct enemies *next;
};

/*������������*/
int get_key();
struct enemies *init(struct enemies *head);
int enemy_move(struct enemies *head);
int chk_atk(struct enemies *&head, ball *self, int &score);
int get_alive_num(struct enemies *);
void display_1s_text();
void display_win_text();
void show_high_score();
int you_die(int);
void pause_menu();
void show_score(int score);
struct enemies *rm(struct enemies *head, int rm_id);

void main()
{
	
	srand( (unsigned)time(NULL) );//��ʼ���������
	initgraph(GRAPH_W,GRAPH_H,SHOWCONSOLE);//��ʼ������
	setbkcolor(WHITE);//���û���������ɫΪ��
	cleardevice();//���±���ɫ�����Ļ

	ball *self;
	self = new ball;

	struct enemies *head = NULL;//����ͷ
	head = init(head);//��ʼ������
	int score = self -> get_r();
	while(1)//��Ϸ��ѭ��
	{
		self -> get_direction(get_key());
		Sleep(SLEEP_TIME + (ENEMY_NUM - get_alive_num(head))*5);
		self -> draw();
		enemy_move(head);
		if (chk_atk(head,self,score))
			return ;
		cout << endl << "reached\n";
		show_score(score);
		if (!get_alive_num(head))//��Ϸ�ɹ�
		{
			display_win_text();
			ofstream fout("highscore.txt",ios_base::out|ios_base::app);
			fout << score <<endl;
			fout.close();
			while (1)
			{
				if (get_key() == LEFT)
					show_high_score();
				if (get_key() == RIGHT)
					main();
			}
			system("pause");
		}
	}

	system("pause");
	closegraph();
	
}


struct enemies *init(struct enemies *head)//��ʼ��20������
{
	struct enemies *current;
	struct enemies *prev;

	head = NULL;
	prev = NULL;

	for (int i=1;i<=ENEMY_NUM;i++)
	{
		current = (struct enemies *)malloc(sizeof(struct enemies));//Ϊ�½ڵ����ռ�
		if (head == NULL)//���ͷָ��Ϊ����ǰΪ��һ���ڵ㣬��head��ֵΪcurrent��ָ��ǰ�ڵ��ָ�롣 
			head = current;
		else
			prev->next = current;//������ָ����һ���ڵ��nextָ��ָ��ǰ�ڵ�
		current->next = NULL;//��nextָ�������ʾ�������һ���ڵ�
		/*���м��ǽڵ����Ϣ*/
		current -> enemy_balls = new enemy(1);
		//current -> alive = TRUE;
		Sleep(SLEEP_TIME);
		/*----����-----*/
		prev = current;//ʹ��ǰ�ڵ��Ϊ��һ����
	}
	system("pause");
	return head;
}

int enemy_move(struct enemies *head)
{
	struct enemies *current;
	struct enemies *prev;

	current = head;
	prev = NULL;

	for (int i=1;i<=ENEMY_NUM;i++)
	{
		current -> enemy_balls -> move();
		Sleep(SLEEP_TIME);
		current -> enemy_balls -> draw();
		if (current -> next == NULL)
			break;
		else
			current = current -> next;
	}
	return 0;
}



int get_key()//������Ϣ
{
	int key;
	key=NULL;
	if(GetAsyncKeyState(65) & 0x8000) 
	{
		key=LEFT;
		cout << "left";
	}
	if(GetAsyncKeyState(68) & 0x8000) 
	{
		key=RIGHT;
		cout << "right";
	}
	if(GetAsyncKeyState(87) & 0x8000) 
	{
		key=UP;
		cout << "up";
	}
	if(GetAsyncKeyState(83) & 0x8000) 
	{
		key=DOWN;
		cout << "down";
	}
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		key=VK_SPACE;
		cout << "space";
	}
	if(GetAsyncKeyState(80) & 0x8000) 
	{
		pause_menu();
	}
	
	return key;

}

int chk_atk(struct enemies *&head, ball *self, int &score)
{
	struct enemies *current;
	struct enemies *prev;
	struct enemies *rm = NULL;

	current = head;
	prev = NULL;

	for (int i=1;i<=ENEMY_NUM;i++)
	{
		//if (current -> alive > 0)
		//{
		double a = (abs(self -> get_x() - current -> enemy_balls -> get_x()))^2 ;
		double b = (abs(self -> get_y() - current -> enemy_balls -> get_y()))^2 ;
		int d_r =  (abs(self -> get_r() - current -> enemy_balls -> get_r()))^2 ;
		if (a + b <= d_r*JUDGE && self -> get_r() > current -> enemy_balls -> get_r())
		{
			self -> chg_r((current -> enemy_balls -> get_r())*0.5);//�����Լ������
			score += current -> enemy_balls -> get_r();
			//======ɾ���ڵ�
			if (current == head)
				head = current ->next;
			else
				prev -> next = current -> next;

			thread t1(display_1s_text);//����һ�����߳�
			t1.detach();//�����̴߳����̷߳���
		}
		else if (a + b <= d_r * 1.2 &&self -> get_r() < current -> enemy_balls -> get_r())
		{
			if (you_die(score))
				return 1;
			cout << "died";
		}
		Sleep(SLEEP_TIME);
		if (current -> next == NULL)
			break;
		else
		{
			prev = current;
			current = current -> next;
			if (rm)
				delete rm;
		}
	}
	return 0;
}


int get_alive_num(struct enemies *head)
{
	int num = 1;
	struct enemies *current;

	current = head;

	if (head == NULL)
		return 0;

	while (1)
	{
		if (current -> next == NULL)
			break;
		else
		{
			current = current -> next;
			num ++;
		}
	}
	return num;
}

void display_1s_text()
{
	TCHAR out_text[] = _T("+1s");
	COLORREF color = BLACK;
	for (int i=1;i<1000;i++)
	{
		settextcolor(color);
		outtextxy(640/2,480/2,out_text);
		color += 100;
		Sleep(1);
	}
	settextcolor(WHITE);
	outtextxy(640/2,480/2,out_text);
	return;
}

void display_win_text()
{
	TCHAR out_text[] = _T("YOU WIN!");
	settextcolor(RED);
	outtextxy(640/2 - 50,480/2 - 100,out_text);
	TCHAR out_text_1[] = _T("Press A to show high score, D to restart.");
	outtextxy(640/2 - 200,480/2 - 50,out_text_1);
	return;
}


void show_high_score()
{
	vector <int> scores;
	ifstream fin("highscore.txt",ios_base::in);
	string curr_score;
	int n;
	vector <int> h_scores;
	while(!fin.eof())
	{
		getline(fin,curr_score);
		n = atoi(curr_score.c_str());
		scores.push_back(n);
	}

	for (int i=0;i<=4;i++)
		h_scores.push_back(0);
	
	for (int i=0;i<scores.size();i++)
		if (scores[i] >= h_scores[0])
			h_scores[0] = scores[i];
	for (int i=0;i<scores.size();i++)
		if (scores[i] >= h_scores[1]&&scores[i] < h_scores[0])
			h_scores[1] = scores[i];
	for (int i=0;i<scores.size();i++)
		if (scores[i] >= h_scores[2]&&scores[i] < h_scores[1])
			h_scores[2] = scores[i];
	for (int i=0;i<scores.size();i++)
		if (scores[i] >= h_scores[3]&&scores[i] < h_scores[2])
			h_scores[3] = scores[i];
	for (int i=0;i<scores.size();i++)
		if (scores[i] >= h_scores[4]&&scores[i] < h_scores[3])
			h_scores[4] = scores[i];

	for (int i=0;i<=4;i++)
		cout << h_scores[i] << endl;

	TCHAR s[5];
	TCHAR s_t[] = _T("High Scores:");
	settextcolor(RED);
	clearrectangle(5,10,200,120);
	outtextxy(10, 10, s_t);
	for (int i=0;i<=4;i++)
	{
		_stprintf_s(s, _T("%d"), h_scores[i]);  
		outtextxy(50, 30 + 20*i, s);
	}
	return;
}


void pause_menu()
{
	clearrectangle(5,10,300,120);
	settextcolor(RED);
	TCHAR out_text[] = _T("���������hyriamb/i@nyan.im.");
	outtextxy(5 ,10 + 10,out_text);
	TCHAR out_text1[] = _T("������");
	outtextxy(5 ,10 + 30,out_text1);
	TCHAR out_text2[] = _T("WASD �ƶ�");
	outtextxy(5 ,10 + 50,out_text2);
	TCHAR out_text3[] = _T("�ո� ���");
	outtextxy(5 ,10 + 70,out_text3);
	TCHAR out_text4[] = _T("�����������.");
	outtextxy(5 ,10 + 90,out_text4);
	system ("pause");
	clearrectangle(5,20,300,120);
	return;
}

int you_die(int score)
{
	TCHAR out_text[] = _T("YOU DIED!");
	settextcolor(RED);
	outtextxy(640/2 - 50,480/2 - 100,out_text);
	TCHAR out_text_1[] = _T("Press A to show high score, D to restart.");
	outtextxy(640/2 - 100,480/2 - 50,out_text_1);
	ofstream fout("highscore.txt",ios_base::out|ios_base::app);
	fout << score <<endl;
	fout.close();
	while (1)
	{
		if (get_key() == LEFT)
			show_high_score();
		if (get_key() == RIGHT)
			main();
	}
	return 0;
}


void show_score(int score)
{
	settextcolor(RED);
	TCHAR s[5];
	_stprintf_s(s, _T("%d"), score);  
	outtextxy(50, 10, s);
	TCHAR s1[] = _T("Score:");
	outtextxy(10, 10, s1);
	TCHAR s2[] = _T("Press P to pause.");
	outtextxy(10, 30, s2);
	return;
}


struct enemies *rm(struct enemies *head, int rm_id)
{
	struct enemies *current;
	struct enemies *prev;
	struct enemies *rm;
	prev = NULL;
	current = head;

	for (int i=1;i<rm_id;i++)
	{
		prev = current;
		current = current->next;
		if (current == NULL)
		{
			printf("err\n");
			system("pause");
			return head;
		}
	}
	if(current == head)
	{
		rm = head;
		head = head->next;
		delete rm;
	}
	else
	{
		rm = prev->next;
		prev->next=prev->next->next;
		delete rm;
	}
	return head;
}