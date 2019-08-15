/**
 * # JHTicTacToe Ver, 1.0
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


#ifndef _JHTICTACTOE_C_
#define _JHTICTACTOE_C_

//--------------------------------------------------------------------------------------//

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
#include <vector>

#include "jhstd.h"
#include "jhansi.h"
#include "jhinput.h"

#define TICTACTOE_SIZE_X	3
#define TICTACTOE_SIZE_Y	3
#define PLAYER_NONE		0
#define	PLAYER_O		1	//	Human
#define	PLAYER_X		2	//	Computer
#define PLAYER_DRAW		3

struct TTT_POINT
{
	int nX;
	int nY;
};

unsigned short int g_nBoard[TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y];

class JHTicTacToe
{
public:
	JHTicTacToe();
	virtual ~JHTicTacToe();

public:
	void		OnInit();
	void		OnReset();
	void		initBoard();
	void		OnStart();
	void		OnUpdate();
	int			convBoard(int nX, int nY);
	TTT_POINT	convBoard(int nArray);
	bool		setBoard(int nX, int nY, int nPlayer);
	int			getBoard(int nX, int nY);
	bool		setBoard(int nArray, int nPlayer);
	int			getBoard(int nArray);
	int			chkWinner();
	int			getWinner();
	void		setTurn(int nTurn);
	int			getTurn();
	void		chgTurn();
	int			getScoreWin();
	int			getScoreDraw();
	int			getScoreLose();

public:
	bool	m_bGameBegin;

protected:
	void	DoPlayerX();
	bool	chkWinningPoint(int nArray);		//	Check if computer can win, when he get this point.
	bool	chkLosingPoint(int nArray);			//	Check if computer lose, when player get this point.
	bool	chkCenterFree();					//	Check if no mark at the center.
	int		chkApexPossibility();				//	Return the maximum possiblity of apex.
	int		chkApex(int nArray);				//	Return how many winning possibilities the apex has.
	int		chkEdgePossibility();				//	Return the maximum possiblity of edge.
	int		chkEdge(int nArray);				//	Return how many winning possibilities the edge has.
	int		Max(int* nArray, int nSize);
	
protected:
	int		m_nTurn;
	int		m_nWinner;
	int		m_nLastWinner;
	int		m_nScoreWin;
	int		m_nScoreDraw;
	int		m_nScoreLose;
};

//--------------------------------------------------------------------------------------//

#endif
