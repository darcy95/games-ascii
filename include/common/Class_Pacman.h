/**
 * # JHPacman Ver, 1.0
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

#ifndef _JHPACMAN_C_
#define _JHPACMAN_C_

//--------------------------------------------------------------------------------------//

#define PACMAN_MAZE_HEIGHT		21		
#define PACMAN_MAZE_WIDTH		23		

#define PACMAN_INIT_LIFE		3		
#define PACMAN_INIT_POSX		11		
#define PACMAN_INIT_POSY		15		
#define PACMAN_INIT_MOVE		1		
#define PACMAN_INIT_SUPER		50		

#define PACMAN_BONUS_POSX		11		
#define PACMAN_BONUS_POSY		11		
#define PACMAN_BONUS_STAY		50		
#define PACMAN_BONUS_APPEAR		500		

#define PACMAN_GHOST_NUM		4		
#define PACMAN_GHOST_PATH		100		
#define PACMAN_GHOST_AIRESET	100		
#define PACMAN_GHOST_POSX		9		
#define PACMAN_GHOST_POSY		9		
#define PACMAN_GHOST_MOVE		1		

#define PACMAN_DIR_NORTH		0		
#define PACMAN_DIR_EAST			1		
#define PACMAN_DIR_SOUTH		2		
#define PACMAN_DIR_WEST			3		

#define PACMAN_BLOCK_FREE		0		
#define PACMAN_BLOCK_WALL		1		
#define PACMAN_BLOCK_DOOR		2		
#define PACMAN_BLOCK_FOOD		3		
#define PACMAN_BLOCK_SUPER		4		
#define PACMAN_BLOCK_FRUIT		5	

static const unsigned short int g_iPacmanMaze[PACMAN_MAZE_HEIGHT][PACMAN_MAZE_WIDTH] =
{
//						 1 1 1 1 1 1 1 1 1 1 2 2 2
//	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	//	 0
	{1,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,1},	//	 1
	{1,4,1,1,1,3,1,1,1,1,3,1,3,1,1,1,1,3,1,1,1,4,1},	//	 2
	{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},	//	 3
	{1,3,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,3,1,1,1,3,1},	//	 4
	{1,3,3,3,3,3,1,3,3,3,3,1,3,3,3,3,1,3,3,3,3,3,1},	//	 5
	{1,1,1,1,1,3,1,1,1,1,0,1,0,1,1,1,1,3,1,1,1,1,1},	//	 6
	{0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0},	//	 7
	{1,1,1,1,1,3,1,0,1,1,2,2,2,1,1,0,1,3,1,1,1,1,1},	//	 8
	{0,0,0,0,0,3,0,0,1,0,0,0,0,0,1,0,0,3,0,0,0,0,0},	//	 9
	{1,1,1,1,1,3,1,0,1,1,1,1,1,1,1,0,1,3,1,1,1,1,1},	//	10
	{0,0,0,0,1,3,1,0,0,0,0,0,0,0,0,0,1,3,1,0,0,0,0},	//	11
	{1,1,1,1,1,3,1,0,1,1,1,1,1,1,1,0,1,3,1,1,1,1,1},	//	12
	{1,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,1},	//	13
	{1,3,1,1,1,3,1,1,1,1,3,1,3,1,1,1,1,3,1,1,1,3,1},	//	14
	{1,4,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,4,1},	//	15
	{1,1,1,3,1,3,1,3,1,1,1,1,1,1,1,3,1,3,1,3,1,1,1},	//	16
	{1,3,3,3,3,3,1,3,3,3,3,1,3,3,3,3,1,3,3,3,3,3,1},	//	17
	{1,3,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,1,3,1},	//	18
	{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},	//	19
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}		//	20
};
																	
/*
static const unsigned short int g_iPacmanMaze[MAZE_HEIGHT][MAZE_WIDTH] =
{
//						 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2
//	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9		
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	//	 0
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	//	 1
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},	//	 2
	{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},	//	 3
	{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},	//	 4
	{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},	//	 5 
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},	//	 6
	{1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1},	//	 7
	{1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1},	//	 8
	{1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1},	//	 9
	{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},	//	10
	{1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},	//	11
	{1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},	//	12
	{1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1},	//	13
	{1,1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1},	//	14
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},	//	15
	{1,1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1},	//	16
	{1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1},	//	17
	{1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},	//	18
	{1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1},	//	19
	{1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1},	//	20
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},	//	21
	{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},	//	22
	{1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},	//	23
	{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1},	//	24
	{1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1},	//	25
	{1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1},	//	26
	{1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1},	//	27
	{1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1},	//	28
	{1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1},	//	29
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},	//	30
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	//	31
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}	//	32
};
*/

typedef struct PACMAN_POINT
{
	int x;	
	int y;	

} PACMAN_POINT_t;

typedef struct PACMAN_GHOST
{
	char ghostNum;		
	int  countAI;		
	int  countMove;		
	char posOfPath;		
	bool bStatus;		

	PACMAN_POINT path[PACMAN_GHOST_PATH]; 

} PACMAN_GHOST_t;

class JHPacman
{
public:
	JHPacman();
	virtual ~JHPacman();

public:
	void OnInit();
	void OnSetGame();
	void OnSetStage();
	void OnExit();
	void OnStart();
	void OnUpdate();
	void moveGhost();
	void movePacman();
	void initAStar();
	void initGhost();
	void initGhostPath(char cGhostNum);
	void dumpMap();
	int countFood();	
	int* mergeMazeForAStar();
	void giveInteligenceToGhost(char cGhostNum);
	void turnDirection(char cDirection);
	void checkGhostToBeNormal();

	void onCollision();
	void onCollisionFood();
	void onCollisionSuper();
	void onCollisionFruit();
	void onCollisionGhost(char cGhostNum);

	void onFruitCheck();
	void onSuperCheck();
	void onStageClear();

	bool checkCollisionFree(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_FREE); };
	bool checkCollisionWall(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_WALL); };
	bool checkCollisionDoor(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_DOOR); };
	bool checkCollisionFood(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_FOOD); };
	bool checkCollisionSuper(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_SUPER); };
	bool checkCollisionFruit(int x, int y) { return (getTile(x, y) == PACMAN_BLOCK_FRUIT); };
	char checkCollisionGhost(int x, int y); 
	bool checkIfFruitIsThere() { return (getTile(PACMAN_BONUS_POSX, PACMAN_BONUS_POSY) == PACMAN_BLOCK_FRUIT); };

	void setTile(int x, int y, int iTile) { m_iPacmanMaze[y][x] = iTile; };
	int getTile(int x, int y);
	void setGameRun(bool bRun) { bGameRun = bRun; };
	void setDirection(char cDirection) { cPacmanDirection = cDirection; };
	bool getGameRun() { return bGameRun; };
	char getDirection()	{ return cPacmanDirection; }; 
	bool getPacmanSuper() { return bSuperPacman; };
	void setPacmanSuper(bool bSuper) { bSuperPacman = bSuper; };
	void setSuperCount(int iCount) { iSuperCount = iCount; };
	int  getSuperCount() { return iSuperCount; };
	void setFoodCount(int iCount) { iFoodCount = iCount; };
	int  getFoodCount() { return iFoodCount; };
	void setScore(int iScore) { iGameScore = iScore; };
	int  getScore() { return iGameScore; };
	void setStage(char cStage) { cGameStage = cStage; };
	char getStage() { return cGameStage; };
	void setLife(char cLife) { cPacmanLife = cLife; };
	char getLife() { return cPacmanLife; };
	PACMAN_POINT getPacmanPos() { return posPacman; };
	int getPacmanPosX() { return posPacman.x; };
	int getPacmanPosY() { return posPacman.y; };
	void setPacmanPos(int x, int y) { setPacmanPosX(x); setPacmanPosY(y); };	
	void setPacmanPosX(int x) { posPacman.x = x; };
	void setPacmanPosY(int y) { posPacman.y = y; };	
	PACMAN_POINT getGhostPos(char cGhostNum) { return ghost[cGhostNum].path[ghost[cGhostNum].posOfPath]; };
	int getGhostPosX(char cGhostNum) { return ghost[cGhostNum].path[ghost[cGhostNum].posOfPath].x; };
	int getGhostPosY(char cGhostNum) { return ghost[cGhostNum].path[ghost[cGhostNum].posOfPath].y; };
	bool getGhostStatus(char cGhostNum) { return ghost[cGhostNum].bStatus; };
	void setGhostStatus(char cGhostNum, bool bStatus) { ghost[cGhostNum].bStatus = bStatus; };
	void setPacmanMoveCount(int iCount) { iPacmanMoveCount = iCount; };
	int getPacmanMoveCount() { return iPacmanMoveCount; };
	void setFruitAppear(int iCount) { iFruitAppear = iCount; };
	int getFruitAppear() { return iFruitAppear; };
	void setFruitStay(int iCount) { iFruitStay = iCount; };
	int getFruitStay() { return iFruitStay; };

protected:
	bool bGameRun;			
	bool bSuperPacman;		
	int  iSuperCount;		
	char cPacmanDirection;	
	int  iFoodCount;		
	int	 iGameScore;		
	char cGameStage;		
	char cPacmanLife;		
	int	 iPacmanMoveCount;	 
	int	 iFruitAppear;		
	int  iFruitStay;		
	JHAStar* astar;			

	unsigned short int m_iPacmanMaze[PACMAN_MAZE_HEIGHT][PACMAN_MAZE_WIDTH];
	PACMAN_GHOST ghost[PACMAN_GHOST_NUM];
	PACMAN_POINT posPacman;	 
};

//--------------------------------------------------------------------------------------//

JHPacman::JHPacman()
{

}

JHPacman::~JHPacman()
{

}

void JHPacman::OnInit()
{
	initAStar();

	OnSetGame();

	OnSetStage();
}

void JHPacman::OnSetGame()
{
	setScore(0);
	setStage(1);
	setLife(PACMAN_INIT_LIFE);
	setGameRun(true);
}

void JHPacman::OnSetStage()
{
	setPacmanPos(PACMAN_INIT_POSX, PACMAN_INIT_POSY);
	setPacmanMoveCount(PACMAN_INIT_MOVE);
	setDirection(PACMAN_DIR_WEST);
	setSuperCount(0);
	setPacmanSuper(false);
	setFoodCount(countFood());
	setFruitAppear(PACMAN_BONUS_APPEAR);
	setFruitStay(0);
	dumpMap();
	initGhost();
}

void JHPacman::OnExit()
{
	delete astar;
	astar = NULL;

	setGameRun(false);
}

void JHPacman::OnStart()
{

}

void JHPacman::OnUpdate()
{
	moveGhost();
	onCollisionGhost(checkCollisionGhost(getPacmanPosX(), getPacmanPosY()));

	movePacman();
	onCollision();

	onSuperCheck();
	onFruitCheck();
	onStageClear();
}

void JHPacman::moveGhost()
{
	for (int i = 0 ; i < PACMAN_GHOST_NUM ; i++)
	{
		if (ghost[i].countMove <= 0)
		{
			char iNextPath = ghost[i].posOfPath + 1;

			if ((ghost[i].path[iNextPath].x == -1 && ghost[i].path[iNextPath].y == -1) || (iNextPath > (PACMAN_GHOST_PATH - 1)))
			{
				giveInteligenceToGhost(i);

				ghost[i].posOfPath = 0;
			}
			else
			{
				ghost[i].posOfPath = iNextPath;
			}

			ghost[i].countMove = PACMAN_GHOST_MOVE;
		}
		else
		{
			ghost[i].countMove--;
		}
	}

	checkGhostToBeNormal();
}

void JHPacman::movePacman()
{
	if (getPacmanMoveCount() <= 0)
	{
		int x = getPacmanPosX();
		int y = getPacmanPosY();

		switch (getDirection())
		{
			case PACMAN_DIR_NORTH:	y--; break;
			case PACMAN_DIR_EAST:	x++; break;
			case PACMAN_DIR_SOUTH:	y++; break;
			case PACMAN_DIR_WEST:	x--; break;
		}

		if (x >= PACMAN_MAZE_WIDTH)
		{
			x = 0;
		}
		else if (x < 0)
		{
			x = PACMAN_MAZE_WIDTH - 1;
		}

		if (!checkCollisionWall(x, y) && !checkCollisionDoor(x, y))
		{
			setPacmanPos(x, y);
		}

		setPacmanMoveCount(PACMAN_INIT_MOVE);
	}
	else
	{
		setPacmanMoveCount(getPacmanMoveCount() - 1);
	}
}

void JHPacman::initAStar()
{
	int map[PACMAN_MAZE_WIDTH * PACMAN_MAZE_HEIGHT];

	for (int i = 0 ; i < PACMAN_MAZE_HEIGHT ; i++)
	{
		for (int j = 0 ; j < PACMAN_MAZE_WIDTH ; j++)
		{
			if (g_iPacmanMaze[i][j] == PACMAN_BLOCK_WALL)
			{
				map[(i * PACMAN_MAZE_WIDTH) + j] = TILE_BLOCK;
			}
			else
			{
				map[(i * PACMAN_MAZE_WIDTH) + j] = TILE_PATH;
			}
		}
	}

	astar = new JHAStar((int*) map, PACMAN_MAZE_WIDTH, PACMAN_MAZE_HEIGHT);
}

void JHPacman::initGhost()
{
	for (int i = 0 ; i < PACMAN_GHOST_NUM ; i++)
	{
		ghost[i].countAI = PACMAN_GHOST_AIRESET + 100;
		ghost[i].countMove = PACMAN_GHOST_MOVE;
		ghost[i].posOfPath = 0;
		ghost[i].bStatus = true;

		initGhostPath(i);

		if (i == 0)
		{
			ghost[0].path[0].x = 11;
			ghost[0].path[0].y = 7;
		}

		for (int j = 0 ; j < (10 * i) ; j++)
		{
			ghost[i].path[j].x = PACMAN_GHOST_POSX + i;
			ghost[i].path[j].y = PACMAN_GHOST_POSY;
		}
	}
}

void JHPacman::initGhostPath(char cGhostNum)
{
	for (int i = 0 ; i < PACMAN_GHOST_PATH ; i++)
	{
		ghost[cGhostNum].path[i].x = -1;
		ghost[cGhostNum].path[i].y = -1;
	}
}

void JHPacman::dumpMap()
{
	for (int i = 0 ; i < PACMAN_MAZE_HEIGHT ; i++)
	{
		for (int j = 0 ; j < PACMAN_MAZE_WIDTH ; j++)
		{
			m_iPacmanMaze[i][j] = g_iPacmanMaze[i][j];
		}
	}	
}

int JHPacman::countFood()
{
	int iFood = 0;

	for (int i = 0 ; i < PACMAN_MAZE_HEIGHT ; i++)
	{
		for (int j = 0 ; j < PACMAN_MAZE_WIDTH ; j++)
		{
			if (g_iPacmanMaze[i][j] == PACMAN_BLOCK_FOOD)
			{
				iFood++;
			}
		}
	}

	return iFood;
}

int* JHPacman::mergeMazeForAStar()
{

}

void JHPacman::giveInteligenceToGhost(char cGhostNum)
{
	int iGhostX = getGhostPosX(cGhostNum);
	int iGhostY = getGhostPosY(cGhostNum);
	int iPacmanX = getPacmanPosX();
	int iPacmanY = getPacmanPosY();

	initGhostPath(cGhostNum);

	if ((rand() % 100) < ((cGhostNum + 1) * 10))
	{
		switch (cGhostNum)
		{
			case 0:	
			{
				iPacmanX = 1; 
				iPacmanY = 1; 
			}
			break;

			case 1:	
			{
				iPacmanX = PACMAN_MAZE_WIDTH - 2;
				iPacmanY = 1; 
			}
			break;
			
			case 2:	
			{
				iPacmanX = PACMAN_MAZE_WIDTH - 2; 
				iPacmanY = PACMAN_MAZE_HEIGHT - 2; 
			}
			break;
			
			case 3:	
			{
				iPacmanX = 1; 
				iPacmanY = PACMAN_MAZE_HEIGHT - 2; 
			}
			break;	
		}
	}

	AStar_Node* n = astar->findPath(iPacmanX, iPacmanY, iGhostX, iGhostY, false);
	AStar_Node* t = n;

	int i = 0;

	while (t != NULL)
	{
		ghost[cGhostNum].path[i].x = t->x;
		ghost[cGhostNum].path[i].y = t->y;
		t = t->parent;
		i++;
	}

	n->next = NULL;
}

void JHPacman::turnDirection(char cDirection)
{
	int x = getPacmanPosX();
	int y = getPacmanPosY();

	switch (cDirection)
	{
		case PACMAN_DIR_NORTH:	y--; break;
		case PACMAN_DIR_EAST:	x++; break;
		case PACMAN_DIR_SOUTH:	y++; break;
		case PACMAN_DIR_WEST:	x--; break;
	}

	if (!checkCollisionWall(x, y) && !checkCollisionDoor(x, y))
	{
		setDirection(cDirection);
	}
}

void JHPacman::checkGhostToBeNormal()
{
	for (int i = 0 ; i < PACMAN_GHOST_NUM ; i++)
	{
		if (getGhostStatus(i) == false)
		{	
			if (((getGhostPosX(i) >= PACMAN_GHOST_POSX) && (getGhostPosX(i) <= (PACMAN_GHOST_POSX + 4))) && (getGhostPosY(i) == PACMAN_GHOST_POSY))
			{
				setGhostStatus(i, true);
			}
		}
	}
}

void JHPacman::onCollision()
{
	int iPacmanPosX = getPacmanPosX();
	int iPacmanPosY = getPacmanPosY();

	if (checkCollisionFood(iPacmanPosX, iPacmanPosY))  { onCollisionFood();  }
	if (checkCollisionFruit(iPacmanPosX, iPacmanPosY)) { onCollisionFruit(); }
	if (checkCollisionSuper(iPacmanPosX, iPacmanPosY)) { onCollisionSuper(); }
	
	onCollisionGhost(checkCollisionGhost(iPacmanPosX, iPacmanPosY));
}

char JHPacman::checkCollisionGhost(int x, int y)
{ 
	char cReturn = -1;

	for (int i = 0 ; i < PACMAN_GHOST_NUM ; i++)
	{
		if ((getPacmanPosX() == getGhostPosX(i)) && (getPacmanPosY() == getGhostPosY(i)))
		{
			cReturn = i;
			break;
		}
	}

	return cReturn;
}

void JHPacman::onCollisionFood()
{
	setTile(getPacmanPosX(), getPacmanPosY(), PACMAN_BLOCK_FREE);
	setFoodCount(getFoodCount() - 1);
	setScore(getScore() + 1);
}

void JHPacman::onCollisionSuper()
{
	setTile(getPacmanPosX(), getPacmanPosY(), PACMAN_BLOCK_FREE);
	setPacmanSuper(true);
	setSuperCount(PACMAN_INIT_SUPER);
	setScore(getScore() + 3);
}

void JHPacman::onCollisionFruit()
{
	setTile(getPacmanPosX(), getPacmanPosY(), PACMAN_BLOCK_FREE);
	setFruitStay(0);
	setFruitAppear(PACMAN_BONUS_APPEAR);
	setScore(getScore() + 10);
}

void JHPacman::onCollisionGhost(char cGhostNum)
{
	if (cGhostNum >= 0)
	{
		if (getPacmanSuper())
		{
			if (getGhostStatus(cGhostNum))
			{
				setGhostStatus(cGhostNum, false);

				setScore(getScore() + 2);

				int iGhostPosX = getGhostPosX(cGhostNum);
				int iGhostPosY = getGhostPosY(cGhostNum);
				
				initGhostPath(cGhostNum);

				AStar_Node* n = astar->findPath(PACMAN_GHOST_POSX + 2, PACMAN_GHOST_POSY, iGhostPosX, iGhostPosY, false);
				AStar_Node* t = n;

				int i = 0;

				while (t != NULL)
				{
					ghost[cGhostNum].path[i].x = t->x;
					ghost[cGhostNum].path[i].y = t->y;
					t = t->parent;
					i++;
				}

				n->next = NULL;
			}
		}
		else
		{
			setLife(getLife() - 1);

			if (getLife() == 0)
			{
				OnExit();
			}
			else
			{
				setPacmanPos(PACMAN_INIT_POSX, PACMAN_INIT_POSY);
				setPacmanMoveCount(PACMAN_INIT_MOVE);
				setDirection(PACMAN_DIR_WEST);
				setSuperCount(0);
				setPacmanSuper(false);
				setFruitAppear(PACMAN_BONUS_APPEAR);
				setFruitStay(0);
				initGhost();
			}
		}
	}
}

void JHPacman::onFruitCheck()
{
	if (checkIfFruitIsThere())
	{
		if (getFruitStay() <= 0)
		{
			setTile(PACMAN_BONUS_POSX, PACMAN_BONUS_POSY, PACMAN_BLOCK_FREE);
			setFruitStay(0);
			setFruitAppear(PACMAN_BONUS_APPEAR);
		}
		else
		{
			setFruitStay(getFruitStay() - 1);
		}
	}
	else
	{
		if (getFruitAppear() <= 0)
		{
			setTile(PACMAN_BONUS_POSX, PACMAN_BONUS_POSY, PACMAN_BLOCK_FRUIT);
			setFruitStay(PACMAN_BONUS_STAY);
			setFruitAppear(0);
		}
		else
		{
			setFruitAppear(getFruitAppear() - 1);
		}
	}
}

void JHPacman::onSuperCheck()
{
	if (getPacmanSuper())
	{
		if (getSuperCount() <= 0)
		{
			setPacmanSuper(false);
		}
		else
		{
			setSuperCount(getSuperCount() - 1);
		}
	}
}

void JHPacman::onStageClear()
{
	if (getFoodCount() <= 0)
	{
		setStage(getStage() + 1);
		OnSetStage();
	}
}

int JHPacman::getTile(int x, int y) 
{ 
	int iTile = -1;

	if ((x < PACMAN_MAZE_WIDTH) && (x >= 0) && (y < PACMAN_MAZE_HEIGHT) && (y >= 0))
	{
		iTile = m_iPacmanMaze[y][x];
	}

	return iTile; 
}

//--------------------------------------------------------------------------------------//

#endif
