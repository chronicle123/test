#ifndef _WALL_HEAD
#define _WALL_HEAD
//#pragma  once

#include <iostream>
#include<windows.h>
using namespace std;

class Wall
{
public:
	enum {
		ROW = 26,
		COL = 26
	};
	
	//��ʼ��ǽ��
	void initWall();

	//����ǽ��
	void drawWall();

	//������������ ��ά�����������
	void setWall(int x, int y, char c);

	//����������ȡ��ǰλ�õķ���
	char getWall(int x, int y);

private:
	char gameArray[ROW][COL];
};

#endif