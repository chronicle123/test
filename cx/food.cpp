#include "food.h"

Food::Food(Wall & tempWall) : wall(tempWall)
{

}

void Food::setFood()
{
	while (true)
	{
		foodX = rand() % (Wall::ROW - 2) + 1;
		foodY = rand() % (Wall::COL - 2) + 1;

		//如果随机的位置是蛇头或蛇身 就重新生成随机数
		if (wall.getWall(foodX, foodY) == ' ')
		{
			
			wall.setWall(foodX, foodY, '#');
			break;
		}
	}
}
