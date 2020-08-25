#pragma  once
#include <iostream>
#include "wall.h"
#include "food.h"
using namespace std;

class Snake
{
public:
	Snake(Wall & tempWall, Food & food );

	enum { UP = 'w', DOWN = 's', LEFT = 'a' , RIGHT = 'd'};

	//�ڵ�
	struct Point
	{
		//������
		int x;
		int y;
		//ָ����
		Point * next;
	};

	//��ʼ����
	void initSnake();

	// ���ٽڵ�
	void destroyPoint();

	// ��ӽڵ�
	void addPoint(int x,int y);


	// ɾ���ڵ�
	void delPoint();

	//�ƶ��߲���
	//����ֵ���� �ƶ��Ƿ�ɹ�
	bool move(char key);
	int getSleepTime();
	int countList();
	int getScore();

	Point * pHead;

	Wall & wall;

	Food & food;

	bool isRool; //�ж�ѭ����ʾ
	int score;
	int size;
};


