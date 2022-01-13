#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
//ʵ���ϲ���Ҫ�궨�壬���Ƕ����˿������бƸ�
#define MAPX 60
#define MAPY 16
#define SNAKESIZE 50

//hello world
using namespace std;

/////////////////////////////////////////////
//                 ʳ��
struct
{
	int x;
	int y;
}food;

//////////////////////////////////////////////
//              ����׼��������������̫��������  ��������ʮ�ߵ�һ��
//��
struct
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;
	int speed;
}snake;

///////////////////////////////////////////////
//                ȫ�ֱ���
int key = 52;            //��ʼ���ƶ�����
int changeflag = 0;
int Count = 1;
int Number = 1;
int num = 1;
int step = 0;
int speed;
int rightkey;

///////////////////////////////////////////////
//                 ȫ����������
//��ͼ 
void DrawMap();
//����ʳ�� 
void CreateFood();
//�������̲��� 
void KeyDown();
//����״̬���ж���Ϸ���� 
void SnakeStatue();
//��������������ƶ� ע�����
void gotoxy(int x, int y);

void SnakeSpeed();

//////////////////////////////////////////////////////////////////// 
//     main����            
int main()
{
	DrawMap();
	while (1)
	{
		SnakeSpeed();
		KeyDown();
		CreateFood();


		gotoxy(0, MAPY + 1);
		cout << "�ƶ����룺" << num;
		num++;

		gotoxy(15, MAPY + 1);
		cout << "����������" << step;

		gotoxy(30, MAPY + 1);
		cout << "�ٶȵȼ���" << speed;

		gotoxy(45, MAPY + 1);
		cout << "��Ϸ������" << snake.len - 4;

		SnakeStatue();
		if (Count == 0)
		{
			gotoxy(MAPX / 2, MAPY / 2);
			cout << "Gameover!" << endl;
			break;
		}

		//		gotoxy(0,MAPY+1);

		if (snake.len == SNAKESIZE)
		{
			gotoxy(MAPX / 2 - 4, MAPY / 2);
			cout << "����ţ��!";
			break;
			gotoxy(1, MAPY + 3);
		}
	}

	system("pause");
	return 0;
}
/////////////////////////////////////////// ///////////////////// 
//            ��ͼ 
void DrawMap()
{
	//"+��ͷ������ 
	srand((unsigned int)time(NULL));
	//���ұ߿�
	for (int i = 0; i <= MAPY; i++)
	{
		gotoxy(0, i);
		cout << "*" << endl;
		gotoxy(MAPX, i);

		cout << "*" << endl;
	}
	//���±߿� 
	for (int j = 0; j <= MAPX; j++)
	{
		gotoxy(j, 0);
		cout << "*" << endl;
		gotoxy(j, MAPY);
		cout << "*" << endl;
	}
	//������� 
	snake.len = 4;
	snake.speed = 350;
	//��ʼ��ͷ��λ��
	snake.x[0] = MAPX / 2;
	snake.y[0] = MAPY / 2;
	//ͷ
	gotoxy(snake.x[0], snake.y[0]);
	cout << "*" << endl;
	//forѭ������,�ú�һ��ʼ�ո���ǰһ��������gotoxy׷����ʾ 
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 1;      //sanke[1]=snake[0]+1 
		snake.y[k] = snake.y[k - 1];        //y����Ҫ*1����Ϊ���ǳ�ʼ���������� 
		gotoxy(snake.x[k], snake.y[k]);
		cout << "*" << endl;
	}
	//������һ���������赥���ú������� 
	food.x = rand() % (MAPX - 2) + 1;
	food.y = rand() % (MAPY - 2) + 1;
	gotoxy(food.x, food.y);
	cout << "!" << endl;
	//�ѹ������
	gotoxy(0, MAPY + 1);

}

///////////////////////////////////////////////////////////////////////////////
//          ����gotoxy����,ʹ��win32 API
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}
///////////////////////////////////////////////////////////////////////////////
//        ��ؼ��̵Ĳ���
void KeyDown()
{
	fflush(stdin);

	if (changeflag == 0)    //���get���ˣ��򳤶�+1����ԭ��β���Ĳ�����ͷ��һ��û�Ե���ͷ��һ��β��һ 
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		cout << " ";
	}

	for (int i = snake.len - 1; i > 0; i--)      //����λ�õ����������һ�� 
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}


	if (Number != 1)
	{
		key = rightkey;
	}


	//��ؼ��̣���������룬��ִ����������� 
	if (_kbhit())
	{
		Number++;
		step++;
		switch (key)  //�жϸ�ִ�е������ʱ���˶��ķ��� 
		{

		case 56:  //���Ĭ����56/8 
			fflush(stdin);   //��ջ����� 
			key = _getch();     //��8��ASCIIֵ��key

			if (key == 52 || key == 54 || key == 56)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "����Ƿ���";
			}

			switch (rightkey)         //����key����ֵ 
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;



		case 50:
			fflush(stdin);
			key = _getch();
			if (key == 52 || key == 54 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "����Ƿ���";
			}

			switch (rightkey)
			{
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;


		case 52:
			//����	
//          gotoxy(MAPX+1,2);
//			cout<<key;

			fflush(stdin);
			key = _getch();
			if (key == 52 || key == 56 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX+1, MAPY + 1);
				cout << "����Ƿ���";
			}
			//���� 
//			gotoxy(MAPX+1,8);
	//		cout<<key;
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				//			        gotoxy(MAPX+1,MAPY+1);
				//			        cout<<"FUCK! you";
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				//			        gotoxy(MAPX+1,MAPY+1);
				//			        cout<<"FUCK! you";
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			}
			break;

		case 54:
			fflush(stdin);
			key = _getch();
			if (key == 54 || key == 56 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "����Ƿ���";
			}
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;
		}
		//Ĭ��Ϊ8����������2����ͬ 

	}

	//		key=getch();
	//		cout<<"here";
	//		switch(key)
	//	    {
	//	    	
	//		    case '8':
	//			    snake.y[0]=snake.y[0]-1;
	//			    break;
	//		    case '2':
	//			    snake.y[0]=snake.y[0]+1;
	//			    break;
	//		    case '4':
	//			    snake.x[0]=snake.x[0]-1;
	//			    break;
	//		    case '6':
	//			    snake.x[0]=snake.x[0]+1;
	//			    break;
	//		}				

	////////////////////////////////////////////////////////////////////////
	//    Sleep(snake.speed);
	////////////////////////////////////////////////////////////////////////

	else
	{
		if (Number == 1)
		{
			switch (key)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
		}
		else
		{
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
		}

	}

	gotoxy(snake.x[0], snake.y[0]);
	cout << "*";
	//	Sleep(200);
}
/////////////////////////////////////////////////////////////////
//          ʳ��
void CreateFood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{

		//���� 
//		gotoxy(0,MAPY+5);
//		cout<<"here";

		int flag = 1;
		food.x = rand() % (MAPX - 2) + 1;
		food.y = rand() % (MAPY - 2) + 1;

		srand((unsigned int)time(NULL));
		while (1)
		{

			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == food.x && snake.y[k] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				gotoxy(food.x, food.y);
				cout << "!";
				break;
			}
		}
		snake.len = snake.len + 1;;
		changeflag = 1;
	}
	else
	{
		changeflag = 0;
	}
}
//////////////////////////////////////////////////////////////////////
//       �����״̬

void SnakeStatue()
{
	//����ͷ����ײ���Լ����Ͱ�count��ֵ0
	if (snake.x[0] == 0 || snake.x[0] == MAPX - 1 || snake.y[0] == 0 || snake.y[0] == MAPY - 1)
	{
		Count = 0;
	}

	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[0] == snake.y[k])
		{
			gotoxy(10, MAPY + 1);
			cout << "here!";
			Count = 0;
		}
	}

}
/////////////////////////////////////////////////////////////////////
//           �ƶ��ٶ�
void SnakeSpeed()
{
	if (snake.len < 10)
	{
		Sleep(snake.speed - 50);
		speed = 1;
	}
	if (snake.len >= 10 && snake.len < 20)
	{
		Sleep(snake.speed - 100);
		speed = 2;
	}
	if (snake.len >= 20 && snake.len < 30)
	{
		Sleep(snake.speed - 150);
		speed = 3;
	}
	if (snake.len >= 30 && snake.len < 40)
	{
		Sleep(snake.speed - 200);
		speed = 4;
	}
	if (snake.len >= 40 && snake.len < 50)
	{
		Sleep(snake.speed - 250);
		speed = 5;
	}
	if (snake.len > 50)
	{
		Sleep(snake.speed - 300);
		speed = 6;
	}
}