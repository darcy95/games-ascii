/**
 * # JHSnake Ver, 1.0
 *
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 * 
 * Legal Disclaimer
 *
 * Game titles and content in this collection are trademarked by other companies.
 * This code is written only for the educational purpose and will not be used
 * commercially. Thus, you must take the entire liability for any damage caused by
 * using this code.
 *
 */

#include "snake.h"

JHSnake::JHSnake()
{
	OnInit();
}

JHSnake::~JHSnake()
{

}

void JHSnake::OnInit()
{
	m_nFoods = 0;
	m_nScore = 0;
	m_nSpecial = 0;
	m_nTickCount = 0;
	initSnakeField();
	setMaze();
	setSpeed();
	setBegin(false);
	setGotFood(false);
}

void JHSnake::OnExit()
{
	setBegin(false);
}

void JHSnake::OnStart()
{
	initSnake();
	setFood();
	setBegin(true);
}

void JHSnake::OnUpdate()
{
	if (getBegin())
	{
		if (m_nTickCount < m_nSpeed)
		{
			m_nTickCount++;
		}
		else
		{
			m_nTickCount = 0;

			if (getSpecial())
			{
				if (chkCollisionSpecial())
				{
					m_nScore = m_nScore + 10;
					setSpecial(false);
				}
				else
				{
					if (getRemainOfSpecial() > 0)
					{
						m_nSpecial--;
					}
					else
					{
						setSpecial(false);
					}
				}
			}

			addHead();

			if (!getGotFood())
			{
				delTail();				
			}
			else
			{
				setGotFood(false);
				setFood();

				if (getTurnOfSpecial())
				{
					setSpecial(true);
					m_nSpecial = REMAIN_OF_SPECIAL;
				}
			}

			if (chkCollisionFood())
			{
				m_nFoods++;
				m_nScore++;
				setGotFood(true);
			}

			if (chkCollision() != COLL_NONE)
			{
				setBegin(false);
			}

			initSnakeField();
			cpySnakeToField();
		}
	}
}

void JHSnake::initSnake()
{
	SNAKE_POINT sp;

	sp.x = SNAKE_START_X;
	sp.y = SNAKE_START_Y;
	m_vSnakeBody.insert(m_vSnakeBody.begin(), sp);

	for (int i = 1 ; i <= SNAKE_START_BODY ; i++)
	{
		sp.x = SNAKE_START_X - i;
		sp.y = SNAKE_START_Y;
		m_vSnakeBody.push_back(sp);
	}

	m_nDir = DIR_R;
}

void JHSnake::initSnakeField()
{
	for (int i  = 0 ; i < FIELD_SIZE_Y ; i++)
	{
		for (int j  = 0 ; j < FIELD_SIZE_X ; j++)
		{
			m_nSnakeOnField[i][j] = BLOCK_PATH;
		}
	}
}

void JHSnake::cpySnakeToField()
{
	SNAKE_POINT	spTemp;
	std::vector<SNAKE_POINT> vTempSnakeBody;
	vTempSnakeBody = m_vSnakeBody;

	while (!vTempSnakeBody.empty())
	{
		spTemp = vTempSnakeBody.back();
		m_nSnakeOnField[spTemp.y][spTemp.x] = SNAKE_BODY;
		vTempSnakeBody.pop_back();
	}

	spTemp = m_vSnakeBody.front();
	m_nSnakeOnField[spTemp.y][spTemp.x] = SNAKE_HEAD;
}

void JHSnake::setFood()
{
	srand(time(NULL));

	int nX;
	int nY;

	SNAKE_POINT spSnake = getHead();

	do
	{
		nX = rand() % FIELD_SIZE_X;
		nY = rand() % FIELD_SIZE_Y;
	}
	while ((g_nMaze[getMaze()][nY][nX] == BLOCK_WALL) || ((nX == spSnake.x) && (nY == spSnake.y)));

	m_spFood.x = nX;
	m_spFood.y = nY;
}

SNAKE_POINT JHSnake::getFood()
{
	return m_spFood;
}

int JHSnake::getFoods()
{
	return m_nFoods;
}

void JHSnake::setBegin(bool bBegin)
{
	m_bGameBegin = bBegin;
}

bool JHSnake::getBegin()
{
	return m_bGameBegin;
}

void JHSnake::setGotFood(bool bGotFood)
{
	m_bGotFood = bGotFood;
}

bool JHSnake::getGotFood()
{
	return m_bGotFood;
}

void JHSnake::setMaze(int nType)
{
	m_nMaze = nType;
}

int JHSnake::getMaze()
{
	return m_nMaze;
}

void JHSnake::setSpeed(int nSpeed)
{
	m_nSpeed = nSpeed;
}

int JHSnake::getSpeed()
{
	return m_nSpeed;
}

int JHSnake::getScore()
{
	return m_nScore;
}

SNAKE_POINT JHSnake::getNextPos()
{
	SNAKE_POINT	sp;
	sp = getHead();

	switch (m_nDir)
	{
		case DIR_U:
		{
			if (sp.y == 0)
			{
				sp.y = FIELD_SIZE_Y - 1;
			}
			else
			{
				sp.y--;
			}
		}
		break;

		case DIR_R:
		{
			if (sp.x == (FIELD_SIZE_X - 1))
			{
				sp.x = 0;
			}
			else
			{
				sp.x++;
			}
		}
		break;

		case DIR_D:
		{
			if (sp.y == (FIELD_SIZE_Y - 1))
			{
				sp.y = 0;
			}
			else
			{
				sp.y++;
			}
		}
		break;

		case DIR_L:
		{
			if (sp.x == 0)
			{
				sp.x = (FIELD_SIZE_X - 1);
			}
			else
			{
				sp.x--;
			}
		}
		break;
	}

	return sp;
}

void JHSnake::addHead()
{
	m_vSnakeBody.insert(m_vSnakeBody.begin(), getNextPos());
}

SNAKE_POINT JHSnake::getHead()
{
	return m_vSnakeBody.front();
}

void JHSnake::delTail()
{
	m_vSnakeBody.pop_back();
}

SNAKE_POINT JHSnake::getTail()
{
	return m_vSnakeBody.back();
}

void JHSnake::setSpecial(bool bSpecial)
{
	if (bSpecial)
	{
		setSpecialPos();
	}

	m_bSpecial = bSpecial;
}

bool JHSnake::getSpecial()
{
	return m_bSpecial;
}

void JHSnake::setSpecialPos()
{
	srand(time(NULL));

	int		nX;
	int		nY;
	bool	bSet = false;

	SNAKE_POINT spSnake = getHead();

	do
	{
		nX = rand() % FIELD_SIZE_X;
		nY = rand() % FIELD_SIZE_Y;

		bSet = false;

		if ((g_nMaze[getMaze()][nY][nX] == BLOCK_WALL)	||
			((nX == spSnake.x) && (nY == spSnake.y))	||
			((nX == m_spFood.x) && (nY == m_spFood.y)))
		{
			bSet = true;
		}
	}
	while (bSet);

	m_spSpecial.x = nX;
	m_spSpecial.y = nY;
}

SNAKE_POINT JHSnake::getSpecialPos()
{
	return m_spSpecial;
}

bool JHSnake::getTurnOfSpecial()
{
	if ((m_nFoods % CHANCE_OF_SPECIAL) == 0)
	{
		return true;
	}

	return false;
}

int JHSnake::getRemainOfSpecial()
{
	return m_nSpecial;
}

void JHSnake::turnLeft()
{
	if (m_nDir == DIR_U)
	{
		m_nDir = DIR_L;
	}
	else if (m_nDir > DIR_U)
	{
		m_nDir--;
	}
}

void JHSnake::turnRight()
{
	if (m_nDir == DIR_L)
	{
		m_nDir = DIR_U;
	}
	else if (m_nDir < DIR_L)
	{
		m_nDir++;
	}
}

int JHSnake::chkCollision()
{
	if (chkCollisionWall())
	{
		return COLL_WALL;
	}
	else if (chkCollisionBody())
	{
		return COLL_BODY;
	}

	return COLL_NONE;
}

bool JHSnake::chkCollisionWall()
{
	SNAKE_POINT	sp;
	sp = getHead();

	if (g_nMaze[getMaze()][sp.y][sp.x] == BLOCK_WALL)
	{
		return true;
	}

	return false;
}

bool JHSnake::chkCollisionBody()
{
	SNAKE_POINT	spHead;
	SNAKE_POINT	spBody;

	std::vector<SNAKE_POINT> vTempSnakeBody;
	vTempSnakeBody = m_vSnakeBody;

	spHead = vTempSnakeBody.front();
	vTempSnakeBody.erase(vTempSnakeBody.begin());

	while (!vTempSnakeBody.empty())
	{
		spBody = vTempSnakeBody.back();

		if ((spHead.x == spBody.x) && (spHead.y == spBody.y))
		{
			return true;
		}

		vTempSnakeBody.pop_back();
	}

	return false;
}

bool JHSnake::chkCollisionFood()
{
	SNAKE_POINT spSnakeHead = getHead();

	if ((m_spFood.x == spSnakeHead.x) && (m_spFood.y == spSnakeHead.y))
	{
		return true;
	}

	return false;
}

bool JHSnake::chkCollisionSpecial()
{
	SNAKE_POINT spSnakeHead = getHead();

	if ((m_spSpecial.x == spSnakeHead.x) && (m_spSpecial.y == spSnakeHead.y))
	{
		return true;
	}

	return false;
}

