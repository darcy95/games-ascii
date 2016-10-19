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

#define TICTACTOE_SIZE_X	3
#define TICTACTOE_SIZE_Y	3
#define PLAYER_NONE			0
#define	PLAYER_O			1	//	Human
#define	PLAYER_X			2	//	Computer
#define PLAYER_DRAW			3

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

JHTicTacToe::JHTicTacToe()
{

}

JHTicTacToe::~JHTicTacToe()
{

}

void JHTicTacToe::OnInit()
{
	m_nTurn			= PLAYER_O;
	m_nWinner		= PLAYER_NONE;
	m_nLastWinner	= PLAYER_NONE;
	m_bGameBegin	= false;	
	m_nScoreWin		= 0;
	m_nScoreDraw	= 0;
	m_nScoreLose	= 0;
}

void JHTicTacToe::OnReset()
{
	m_nLastWinner = m_nWinner;
	m_nWinner = PLAYER_NONE;

	if (m_nLastWinner == PLAYER_O)
	{
		m_nTurn = PLAYER_X;
	}
	else if (m_nLastWinner == PLAYER_X)
	{
		m_nTurn = PLAYER_O;
	}
	else
	{
		chgTurn();
	}

	initBoard();
}

void JHTicTacToe::initBoard()
{
	for (int i = 0 ; i < (TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y) ; i++)
	{
		g_nBoard[i] = PLAYER_NONE;
	}
}

void JHTicTacToe::OnStart()
{
	OnInit();
	initBoard();
	m_bGameBegin = true;
}

void JHTicTacToe::OnUpdate()
{
	int nWinner = chkWinner();

	if (nWinner == PLAYER_NONE)
	{
		if (getTurn() == PLAYER_X)
		{
			DoPlayerX();
			chgTurn();
		}
	}
	else
	{
		m_nWinner = nWinner;
	}

	if (m_nWinner == PLAYER_O)
	{
		m_nScoreWin++;
	}
	else if (m_nWinner == PLAYER_X)
	{
		m_nScoreLose++;
	}
	else if (m_nWinner == PLAYER_DRAW)
	{
		m_nScoreDraw++;
	}
}

int	 JHTicTacToe::convBoard(int nX, int nY)
{
	return (nY * 3) + (nX % 3);
}

TTT_POINT JHTicTacToe::convBoard(int nArray)
{
	TTT_POINT	ptTemp;

	ptTemp.nX = nArray % 3;
	ptTemp.nY = nArray / 3;

	return ptTemp;
}

bool JHTicTacToe::setBoard(int nX, int nY, int nPlayer)
{
	int nArray = convBoard(nX, nY);

	if (getBoard(nArray) == PLAYER_NONE)
	{
		setBoard(nArray, nPlayer);
		return true;
	}
	
	return false;
}

int JHTicTacToe::getBoard(int nX, int nY)
{
	int nArray = convBoard(nX, nY);
	return getBoard(nArray);
}

bool JHTicTacToe::setBoard(int nArray, int nPlayer)
{
	if (m_nWinner == PLAYER_NONE)
	{
		if (getBoard(nArray) == PLAYER_NONE)
		{
			g_nBoard[nArray] = nPlayer;
			return true;
		}
	}

	return false;
}

int JHTicTacToe::getBoard(int nArray)
{
	return g_nBoard[nArray];
}

int	JHTicTacToe::chkWinner()
{
	int i = 0;
	int nSum[8];
	int nPlayerOSum = PLAYER_O * PLAYER_O * PLAYER_O;
	int nPlayerXSum = PLAYER_X * PLAYER_X * PLAYER_X;

	nSum[0] = g_nBoard[convBoard(0, 0)] * g_nBoard[convBoard(0, 1)] * g_nBoard[convBoard(0, 2)]; 
	nSum[1] = g_nBoard[convBoard(1, 0)] * g_nBoard[convBoard(1, 1)] * g_nBoard[convBoard(1, 2)]; 
	nSum[2] = g_nBoard[convBoard(2, 0)] * g_nBoard[convBoard(2, 1)] * g_nBoard[convBoard(2, 2)]; 
	nSum[3] = g_nBoard[convBoard(0, 0)] * g_nBoard[convBoard(1, 0)] * g_nBoard[convBoard(2, 0)]; 
	nSum[4] = g_nBoard[convBoard(0, 1)] * g_nBoard[convBoard(1, 1)] * g_nBoard[convBoard(2, 1)]; 
	nSum[5] = g_nBoard[convBoard(0, 2)] * g_nBoard[convBoard(1, 2)] * g_nBoard[convBoard(2, 2)]; 
	nSum[6] = g_nBoard[convBoard(0, 0)] * g_nBoard[convBoard(1, 1)] * g_nBoard[convBoard(2, 2)]; 
	nSum[7] = g_nBoard[convBoard(0, 2)] * g_nBoard[convBoard(1, 1)] * g_nBoard[convBoard(2, 0)]; 

	for (i = 0 ; i < 8 ; i++)
	{
		if (nSum[i] == nPlayerOSum)
		{
			return PLAYER_O;
		}
	}

	for (i = 0 ; i < 8 ; i++)
	{
		if (nSum[i] == nPlayerXSum)
		{
			return PLAYER_X;
		}
	}

	for (i = 0 ; i < (TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y) ; i++)
	{
		if (g_nBoard[i] == PLAYER_NONE)
		{
			return PLAYER_NONE;
		}
	}

	return PLAYER_DRAW;
}

int	JHTicTacToe::getWinner()
{
	return m_nWinner;
}

void JHTicTacToe::setTurn(int nTurn)
{
	m_nTurn = nTurn;
}

int	JHTicTacToe::getTurn()
{
	return m_nTurn;
}

void JHTicTacToe::chgTurn()
{
	if (getTurn() == PLAYER_O)
	{
		setTurn(PLAYER_X);
	}
	else
	{
		setTurn(PLAYER_O);
	}	
}

int JHTicTacToe::getScoreWin()
{
	return m_nScoreWin;
}

int JHTicTacToe::getScoreDraw()
{
	return m_nScoreDraw;
}

int JHTicTacToe::getScoreLose()
{
	return m_nScoreLose;
}

void JHTicTacToe::DoPlayerX()
{
	int i = 0;
	int nMaxPossibility = 0;
	int nMaxEdge = chkEdgePossibility();
	int nMaxApex = chkApexPossibility();

	for (int i = 0 ; i < (TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y) ; i++)
	{
		if (chkWinningPoint(i))
		{
			setBoard(i, PLAYER_X);
			return;
		}
	}

	for (int i = 0 ; i < (TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y) ; i++)
	{
		if (chkLosingPoint(i))
		{
			setBoard(i, PLAYER_X);
			return;
		}
	}

	if (chkCenterFree())
	{
		setBoard(4, PLAYER_X);
		return;
	}

	nMaxPossibility = (nMaxEdge > nMaxApex) ? nMaxEdge : nMaxApex;

	if (chkApex(0) == nMaxPossibility)
	{
		setBoard(0, PLAYER_X);
		return;
	}
	else if (chkApex(2) == nMaxPossibility)
	{
		setBoard(2, PLAYER_X);
		return;
	}
	else if (chkApex(6) == nMaxPossibility)
	{
		setBoard(6, PLAYER_X);
		return;
	}
	else if (chkApex(8) == nMaxPossibility)
	{
		setBoard(8, PLAYER_X);
		return;
	}

	if (chkEdge(1) == nMaxPossibility)
	{
		setBoard(1, PLAYER_X);
		return;
	}
	else if (chkEdge(3) == nMaxPossibility)
	{
		setBoard(3, PLAYER_X);
		return;
	}
	else if (chkEdge(5) == nMaxPossibility)
	{
		setBoard(5, PLAYER_X);
		return;
	}
	else if (chkEdge(7) == nMaxPossibility)
	{
		setBoard(7, PLAYER_X);
		return;
	}
}

bool JHTicTacToe::chkWinningPoint(int nArray)
{
	bool bReturn = false;
	unsigned short int nTempBoard[TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y];
	memcpy(&nTempBoard, &g_nBoard, sizeof(g_nBoard));

	if (getBoard(nArray) == PLAYER_NONE)
	{
		g_nBoard[nArray] = PLAYER_X;
	
		if (chkWinner() == PLAYER_X)
		{
			bReturn = true;
		}
	}

	memcpy(&g_nBoard, &nTempBoard, sizeof(g_nBoard));

	return bReturn;
}

bool JHTicTacToe::chkLosingPoint(int nArray)
{
	bool bReturn = false;
	unsigned short int nTempBoard[TICTACTOE_SIZE_X * TICTACTOE_SIZE_Y];
	memcpy(&nTempBoard, &g_nBoard, sizeof(g_nBoard));

	if (getBoard(nArray) == PLAYER_NONE)
	{
		g_nBoard[nArray] = PLAYER_O;
	
		if (chkWinner() == PLAYER_O)
		{
			bReturn = true;
		}
	}

	memcpy(&g_nBoard, &nTempBoard, sizeof(g_nBoard));

	return bReturn;
}

bool JHTicTacToe::chkCenterFree()
{
	if (getBoard(4) == PLAYER_NONE)
	{
		return true;
	}

	return false;
}

int	 JHTicTacToe::chkApexPossibility()
{
	int nPoss[4];
	nPoss[0] = chkApex(0);
	nPoss[1] = chkApex(2);
	nPoss[2] = chkApex(6);
	nPoss[3] = chkApex(8);

	return Max(nPoss, sizeof(nPoss));
}

int	 JHTicTacToe::chkApex(int nArray)
{
	if (getBoard(nArray) != PLAYER_NONE)
	{
		return -1;
	}

	int nPoss = 0;

	switch (nArray)
	{
		case 0:
		{
			if (g_nBoard[1] != PLAYER_O && g_nBoard[2] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[4] != PLAYER_O && g_nBoard[8] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[3] != PLAYER_O && g_nBoard[6] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 2:
		{
			if (g_nBoard[0] != PLAYER_O && g_nBoard[1] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[4] != PLAYER_O && g_nBoard[6] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[5] != PLAYER_O && g_nBoard[7] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 6:
		{
			if (g_nBoard[1] != PLAYER_O && g_nBoard[3] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[4] != PLAYER_O && g_nBoard[2] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[7] != PLAYER_O && g_nBoard[8] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 8:
		{
			if (g_nBoard[2] != PLAYER_O && g_nBoard[5] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[0] != PLAYER_O && g_nBoard[4] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[6] != PLAYER_O && g_nBoard[7] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;
	}

	return nPoss;
}

int	 JHTicTacToe::chkEdgePossibility()
{
	int nPoss[4];
	nPoss[0] = chkApex(1);
	nPoss[1] = chkApex(3);
	nPoss[2] = chkApex(5);
	nPoss[3] = chkApex(7);

	return Max(nPoss, sizeof(nPoss));
}

int	 JHTicTacToe::chkEdge(int nArray)
{
	if (getBoard(nArray) != PLAYER_NONE)
	{
		return -1;
	}

	int nPoss = 0;

	switch (nArray)
	{
		case 1:
		{
			if (g_nBoard[0] != PLAYER_O && g_nBoard[2] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[4] != PLAYER_O && g_nBoard[7] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 3:
		{
			if (g_nBoard[0] != PLAYER_O && g_nBoard[6] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[4] != PLAYER_O && g_nBoard[5] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 5:
		{
			if (g_nBoard[3] != PLAYER_O && g_nBoard[4] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[2] != PLAYER_O && g_nBoard[8] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;

		case 7:
		{
			if (g_nBoard[6] != PLAYER_O && g_nBoard[8] != PLAYER_O)
			{
				nPoss++;
			}

			if (g_nBoard[1] != PLAYER_O && g_nBoard[4] != PLAYER_O)
			{
				nPoss++;
			}
		}
		break;
	}

	return nPoss;
}

//	Insertion Sort
int	 JHTicTacToe::Max(int* nArray, int nSize)
{
	int nCount	= nSize / sizeof(int);
	int i = 0;
	int j = 0;
	int	r = 0;

	for (i = 1 ; i < nCount ; i++) 
	{
		for (j = i - 1, r = nArray[i] ; j >= 0 && nArray[j] > r ; j--)
		{
			nArray[j + 1] = nArray[j];
		}

		nArray[j + 1] = r;
	}

	return nArray[nCount - 1];
}

//--------------------------------------------------------------------------------------//

#endif
