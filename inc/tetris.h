/**
 * # JHTetris Ver, 1.0
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

#ifndef _JHTETRIS_C_
#define _JHTETRIS_C_

#include <stdlib.h>
#include "jhstd.h"
#include "jhastar.h"
#include "jhansi.h"
#include "jhinput.h"

//--------------------------------------------------------------------------------------//

#define	TOTAL_BRICK_NUM_X	10			
#define	TOTAL_BRICK_NUM_Y	20			
#define INIT_SPEED		20			
#define	BLOCK_KIND		7			
#define	BLOCK_STATE		4			
#define	BLOCK_WIDTH		4			
#define	BLOCK_HEIGHT		4			
#define MOVE_TURN		0			
#define MOVE_DOWN		1			
#define MOVE_LEFT		2			
#define MOVE_RIGHT		3			
#define BRICK_EMPTY		0			
#define BRICK_FILLED		1			

#define BLOCK_COUNT		24

struct	Brick
{
	int		nColor;
	int		nFill;
};

class JHTetris
{
public:
	JHTetris();
	virtual ~JHTetris();

public:
	void	OnReset();					
	void	OnStart();					
	void	OnExit();					
	void	OnUpdate();					
	void	OnBlockCopyC2T();				
	void	OnBlockCopyT2C();				
	void	OnBlockCopyN2C();				
	void	OnSettle();					
	int		OnSetNext();				
	bool	OnDown();					
	bool	OnLeft();					
	bool	OnRight();					
	bool	OnRotate();					
	int		OnCheckLine();				
	bool	OnCheckOver();					
	bool	OnCheckCollision();				
	bool	OnCheckComplete(int nLine);			
	bool	OnCheckValidArea(int nX, int nY);
	void	OnArrangeLine(int nLine);			

public:
	virtual void	OnGameStartAct();			
	virtual	void	OnGameOverAct();			
	virtual	void	OnBlockCopyN2CAct();			
	virtual void	OnLineCompleteAct(int nLine);
	virtual void	OnBlockDownAct();			
	virtual void	OnBlockTurnAct();			
	virtual void	OnBlockMoveAct();			
	virtual void	OnImpossibleAct();			
	virtual void	OnSettleAct();				

public:
	Brick	m_BrkBoard[TOTAL_BRICK_NUM_X][TOTAL_BRICK_NUM_Y];
	Brick	m_BrkCurr[BLOCK_WIDTH][BLOCK_HEIGHT];		
	Brick	m_BrkNext[BLOCK_WIDTH][BLOCK_HEIGHT];		
	Brick	m_BrkTemp[BLOCK_WIDTH][BLOCK_HEIGHT];		
	int	m_nPosX;				
	int	m_nPosY;				
	int	m_nTmpPosX;				
	int	m_nTmpPosY;				
	int	m_nCurrBlockKind;			
	int	m_nNextBlockKind;			
	int	m_nTickCount;				
	int	m_nMovePoint;				
	int	m_nScore;				
	int	m_nLine;				
	bool	m_bGameBegin;					

	int	m_nBlockCount;
};

const int g_nBlockKinds[BLOCK_KIND][BLOCK_WIDTH][BLOCK_HEIGHT] = 
{
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	}
};

//--------------------------------------------------------------------------------------//
#endif

