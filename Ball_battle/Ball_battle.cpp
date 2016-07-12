// Ball_battle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ball.h"
#include "enemy.h"

#define ENEMY_NUM 2
#define SLEEP_TIME 10
#define JUDGE 1.5

/*链表结构声明*/
struct enemies
{
	enemy *enemy_balls;
	struct enemies *next;
};

/*主程序函数声明*/
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
	
	srand( (unsigned)time(NULL) );//初始化随机函数
	initgraph(GRAPH_W,GRAPH_H,SHOWCONSOLE);//初始化画布
	setbkcolor(WHITE);//设置画布背景颜色为白
	cleardevice();//用新背景色清空屏幕

	ball *self;
	self = new ball;

	struct enemies *head = NULL;//链表头
	head = init(head);//初始化敌人
	int score = self -> get_r();
	while(1)//游戏主循环
	{
		self -> get_direction(get_key());
		Sleep(SLEEP_TIME + (ENEMY_NUM - get_alive_num(head))*5);
		self -> draw();
		enemy_move(head);
		if (chk_atk(head,self,score))
			return ;
		cout << endl << "reached\n";
		show_score(score);
		if (!get_alive_num(head))//游戏成功
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


struct enemies *init(struct enemies *head)//初始化20个敌人
{
	struct enemies *current;
	struct enemies *prev;

	head = NULL;
	prev = NULL;

	for (int i=1;i<=ENEMY_NUM;i++)
	{
		current = (struct enemies *)malloc(sizeof(struct enemies));//为新节点分配空间
		if (head == NULL)//如果头指针为空则当前为第一个节点，将head赋值为current，指向当前节点的指针。 
			head = current;
		else
			prev->next = current;//不是则指将上一个节点的next指针指向当前节点
		current->next = NULL;//将next指向空来表示这是最后一个节点
		/*这中间是节点的信息*/
		current -> enemy_balls = new enemy(1);
		//current -> alive = TRUE;
		Sleep(SLEEP_TIME);
		/*----结束-----*/
		prev = current;//使当前节点成为上一个。
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



int get_key()//键盘消息
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
			self -> chg_r((current -> enemy_balls -> get_r())*0.5);//增加自己的面积
			score += current -> enemy_balls -> get_r();
			//======删除节点
			if (current == head)
				head = current ->next;
			else
				prev -> next = current -> next;

			thread t1(display_1s_text);//创建一个新线程
			t1.detach();//将新线程从主线程分离
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
	TCHAR out_text[] = _T("设计制作：hyriamb/i@nyan.im.");
	outtextxy(5 ,10 + 10,out_text);
	TCHAR out_text1[] = _T("操作：");
	outtextxy(5 ,10 + 30,out_text1);
	TCHAR out_text2[] = _T("WASD 移动");
	outtextxy(5 ,10 + 50,out_text2);
	TCHAR out_text3[] = _T("空格 冲刺");
	outtextxy(5 ,10 + 70,out_text3);
	TCHAR out_text4[] = _T("按任意键继续.");
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