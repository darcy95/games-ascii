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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <getopt.h>

#include "jhstd.h"
#include "jhastar.h"
#include "jhansi.h"
#include "jhinput.h"

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
#endif
