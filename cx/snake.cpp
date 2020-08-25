#include "snake.h"


Snake::Snake(Wall & tempWall, Food & tmpFood) : wall(tempWall), food(tmpFood)
{
	pHead = NULL;
	isRool = false;
}


void Snake::initSnake()
{
	destroyPoint();

	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

//�������нڵ�
void Snake::destroyPoint()
{   //变量一定义就有一个不确定的值，使用不确定的值会引发编译器错误，所以变量需要初始化
	Point * pCur = pHead;//指向Phead节点

	while (pHead != NULL)
	{
		pCur = pHead->next;//指向Phead节点指向的节点
		delete pHead;//释放内存

		pHead = pCur;//转移指针，指向源节点指向的节点
	}
}

void Snake::addPoint(int x, int y)
{
	//�����½ڵ�
	Point * newPoint = new Point;//使用动态内存创建
	newPoint->x = x;//用下一步的坐标来初始化新的节点坐标  
	newPoint->y = y;
	newPoint->next = NULL;

	//���ԭ��ͷ��Ϊ�� ��Ϊ ����
//首节点保存蛇的首坐标，蛇的结构是由首节点及其他节点保存的坐标再进行二维数组构建，形成的，不是由节点形成的
	if (pHead != NULL)//首节点不为空，如果想要加长蛇的长度，首先需要把蛇头变为蛇身，在把新添加的点作为蛇头
	{
		wall.setWall(pHead->x, pHead->y, '=');
	}
//首节点为空，则直接把新加入的点设为蛇头
	newPoint->next = pHead;//交换位置，让新节点指针指向首节点，形成联系，下一步把首节点指针移动到新节点，则构成新的链表

	pHead = newPoint; //����ͷ��

	wall.setWall(pHead->x, pHead->y, '@');//取新晋级的首节点坐标，改为蛇头


}

//ɾ���ڵ�//删除节点，每次删除一个，被删除的是尾节点
void Snake::delPoint()
{
	
	//�����ڵ����� ��ȥ��ɾ������
	if (pHead == NULL || pHead->next == NULL)//首节点为空或链表中只有一个节点则返回，即需要两个节点以上才继续进行删除操作
	{
		return;
	}

	Point * pCur = pHead->next;//定义一个指针指向次节点
	Point * pPre = pHead;//定义一个指针指向首节点

	while (pCur->next !=NULL)//次节点不是尾节点时，把两个节点往后移
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//ɾ��β�ڵ�

	wall.setWall(pCur->x, pCur->y, ' ');//把蛇尾清空

	delete pCur;
	pCur = NULL;
	pPre->next = NULL;//删除尾节点，再把倒数第二个节点设为尾节点

}

bool Snake::move(char key)
{	//获取蛇头坐标
	int x = pHead->x;
	int y = pHead->y; 

	switch (key)//如果有按键操作，则获取蛇头的下一个行动坐标
	{
	case UP:
		x--;
		break;
	case DOWN :
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	//�ж� �������һ����������β�ͣ���Ӧ������
	//获取指向次节点和首节点的指针
	Point * pCur = pHead->next;
	Point * pPre = pHead;

	while (pCur->next != NULL)//次节点不是尾节点时，移动指针，直到获取到-1节点和-2节点
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y)//下一步碰到的是尾巴，则不应该死亡，因为蛇头和蛇身是同时移动的，头部的下一步为尾部，
	//尾部的下一步则已离开原来位置，这两者的移动是同时进行的，所以不能判fail
	{
		//����β�� ѭ��
		isRool = true;
	}
	else
	{
		//�ж��û�����λ���Ƿ�ɹ�
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')//下一步为墙或者撞到身上，则游戏结束
		{
			addPoint(x, y);//把撞到的部分设为蛇头
			delPoint();//清除尾节点，与上一步结合则形成蛇挂掉之后的状态
			system("cls");
			wall.drawWall();
			int k=getScore();
			//cout<<"your score is:"<<k<<endl;
			cout << "GAME OVER!!!" << endl;
			cout<<"your score is:"<<k<<endl;
			return false;
		}
	}



	//�ƶ��ɹ� ������  
	//�Ե�ʳ��  δ�Ե�ʳ��
	if (wall.getWall(x,y) == '#')//如果下一步吃到食物,则加长蛇身
	{
		addPoint(x, y);//加长蛇身，

		//��������ʳ��
		food.setFood();//重新设置食物位置
	}
	else
	{
		addPoint(x, y); //没有吃到食物，下一步把下一个坐标设为蛇头，原来的尾坐标清空，即可保持原来的长度不变
		delPoint();
		if (isRool == true)//要清空的位置与要设为蛇头的位置为同一个位置，则上述操作会把蛇头清空，需要重新设置蛇头
		{
			wall.setWall(x, y, '@');
		}
		
	}

	return true;
}

//设置蛇的速度，由蛇的长度来决定行进的速度
int Snake::getSleepTime()

{

	int sleepTime = 0;



	int size = countList();

	if ( size < 5)

	{

		sleepTime = 300;

	}

	else if (size >=5 && size <=8)

	{

		sleepTime = 200;

	}

	else

	{

		sleepTime = 100;

	}

	return sleepTime;

}


//计算节点数量，即可获得蛇的尺寸
int Snake::countList()

{

	size = 0;

	Point * curPoint = pHead;

	while (curPoint != NULL)

	{

		size++;



		curPoint = curPoint->next;

	}

	return size;

}

//获取分数，每吃一个食物得100分

int Snake::getScore()

{

	int size = countList();




	score = (size -3) * 100;



	return score;

}

