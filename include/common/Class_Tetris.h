/* =====================================================================================
 *	JHTetris Ver, 1.0
 * 
 */

#ifndef _JHTETRIS_C_
#define _JHTETRIS_C_

//--------------------------------------------------------------------------------------//

#define	TOTAL_BRICK_NUM_X		10			
#define	TOTAL_BRICK_NUM_Y		20			
#define INIT_SPEED				20			
#define	BLOCK_KIND				 7			
#define	BLOCK_STATE				 4			
#define	BLOCK_WIDTH				 4			
#define	BLOCK_HEIGHT			 4			
#define MOVE_TURN				 0			
#define MOVE_DOWN				 1			
#define MOVE_LEFT				 2			
#define MOVE_RIGHT				 3			
#define BRICK_EMPTY				 0			
#define BRICK_FILLED			 1			

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
	void	OnReset();							//	
	void	OnStart();							//	
	void	OnExit();							//	
	void	OnUpdate();							//	
	void	OnBlockCopyC2T();					//	
	void	OnBlockCopyT2C();					//	
	void	OnBlockCopyN2C();					//	
	void	OnSettle();							//	
	int		OnSetNext();						//	
	bool	OnDown();							//	
	bool	OnLeft();							//	
	bool	OnRight();							//	
	bool	OnRotate();							//	
	int		OnCheckLine();						//	
	bool	OnCheckOver();						//	
	bool	OnCheckCollision();					//	
	bool	OnCheckComplete(int nLine);			//	
	bool	OnCheckValidArea(int nX, int nY);	//	
	void	OnArrangeLine(int nLine);			//	

public:
	virtual void	OnGameStartAct();				//
	virtual	void	OnGameOverAct();				//
	virtual	void	OnBlockCopyN2CAct();			//
	virtual void	OnLineCompleteAct(int nLine);	//	
	virtual void	OnBlockDownAct();				//	
	virtual void	OnBlockTurnAct();				//	
	virtual void	OnBlockMoveAct();				//	
	virtual void	OnImpossibleAct();				//	
	virtual void	OnSettleAct();					//	

public:
	Brick	m_BrkBoard[TOTAL_BRICK_NUM_X][TOTAL_BRICK_NUM_Y];		//	
	Brick	m_BrkCurr[BLOCK_WIDTH][BLOCK_HEIGHT];					//	
	Brick	m_BrkNext[BLOCK_WIDTH][BLOCK_HEIGHT];					//	
	Brick	m_BrkTemp[BLOCK_WIDTH][BLOCK_HEIGHT];					//	
	int		m_nPosX;												//	
	int		m_nPosY;												//	
	int		m_nTmpPosX;												//	
	int		m_nTmpPosY;												//	
	int		m_nCurrBlockKind;										//	
	int		m_nNextBlockKind;										//	
	int		m_nTickCount;											//	
	int		m_nMovePoint;											//	
	int		m_nScore;												//
	int		m_nLine;												//
	bool	m_bGameBegin;											//
};


//--------------------------------------------------------------------------------------//

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

JHTetris::JHTetris()
{

}

JHTetris::~JHTetris()
{

}

void JHTetris::OnReset()
{
	int i = 0;
	int j = 0;

	for (i = 0 ; i < TOTAL_BRICK_NUM_X ; i++)
	{
		for (j = 0 ; j < TOTAL_BRICK_NUM_Y ; j++)
		{
			m_BrkBoard[i][j].nFill	= BRICK_EMPTY;
			m_BrkBoard[i][j].nColor = 0;
		}
	}

	for (i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			m_BrkCurr[i][j].nFill	= BRICK_EMPTY;
			m_BrkCurr[i][j].nColor	= 0;

			m_BrkNext[i][j].nFill	= BRICK_EMPTY;
			m_BrkNext[i][j].nColor	= 0;

			m_BrkTemp[i][j].nFill	= BRICK_EMPTY;
			m_BrkTemp[i][j].nColor	= 0;			
		}
	}

	m_nPosX				= 0;
	m_nPosY				= 0;
	m_nTmpPosX			= 0;
	m_nTmpPosY			= 0;
	m_nCurrBlockKind	= 0;
	m_nNextBlockKind	= 0;
	m_nTickCount		= 0;
	m_nMovePoint		= INIT_SPEED;
	m_nScore			= 0;
	m_nLine				= 0;
	m_bGameBegin		= false;
}

void JHTetris::OnStart()
{
	OnReset();
	m_bGameBegin = true;

	m_nNextBlockKind = OnSetNext();
	OnBlockCopyN2C();
	m_nNextBlockKind = OnSetNext();
	
	OnGameStartAct();
}

void JHTetris::OnExit()
{
	m_bGameBegin = false;
}

void JHTetris::OnUpdate()
{
	if (m_bGameBegin)
	{
		if (m_nTickCount < m_nMovePoint)
		{
			m_nTickCount++;
		}
		else
		{
			m_nTickCount = 0;
			OnDown();
		}
	}
}

void JHTetris::OnBlockCopyC2T()
{
	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			m_BrkTemp[i][j].nFill  = m_BrkCurr[i][j].nFill;
			m_BrkTemp[i][j].nColor = m_BrkCurr[i][j].nColor;
		}
	}

	m_nTmpPosX = m_nPosX;
	m_nTmpPosY = m_nPosY;
}

void JHTetris::OnBlockCopyT2C()
{
	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			m_BrkCurr[i][j].nFill  = m_BrkTemp[i][j].nFill;
			m_BrkCurr[i][j].nColor = m_BrkTemp[i][j].nColor;
		}
	}

	m_nPosX = m_nTmpPosX;
	m_nPosY = m_nTmpPosY;
}

void JHTetris::OnBlockCopyN2C()
{
	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			m_BrkCurr[i][j].nFill  = m_BrkNext[i][j].nFill;
			m_BrkCurr[i][j].nColor = m_BrkNext[i][j].nColor;
		}
	}

	m_nPosX = (TOTAL_BRICK_NUM_X / 2) - (BLOCK_WIDTH / 2);
	m_nPosY = 1 - BLOCK_HEIGHT;

	m_nCurrBlockKind = m_nNextBlockKind;

	OnBlockCopyN2CAct();
}

void JHTetris::OnSettle()
{
	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			if (OnCheckValidArea(m_nPosX + i, m_nPosY + j))
			{
				if (m_BrkCurr[i][j].nFill == BRICK_FILLED)
				{
					m_BrkBoard[m_nPosX + i][m_nPosY + j].nFill  = m_BrkCurr[i][j].nFill;
					m_BrkBoard[m_nPosX + i][m_nPosY + j].nColor = m_BrkCurr[i][j].nColor;
					m_BrkCurr[i][j].nFill  = BRICK_EMPTY;
					m_BrkCurr[i][j].nColor = BRICK_EMPTY;
				}
			}
		}
	}

	OnSettleAct();
}

int	JHTetris::OnSetNext()
{
	int nNextBlock = rand() % 7;

	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			m_BrkNext[i][j].nFill  = g_nBlockKinds[nNextBlock][i][j];
			m_BrkNext[i][j].nColor = nNextBlock + 1;
		}
	}

	return nNextBlock;
}

bool JHTetris::OnDown()
{
	bool	bReturn = true;

	if (m_bGameBegin)
	{
		OnBlockCopyC2T();
		m_nPosY++;

		if (OnCheckCollision())
		{
			bReturn = false;
			OnBlockCopyT2C();
			OnSettle();
			OnCheckLine();

			if (OnCheckOver())
			{
				OnGameOverAct();
				OnExit();
			}
			else
			{
				OnBlockCopyN2C();
				m_nNextBlockKind = OnSetNext();
			}
		}
		else
		{
			OnBlockDownAct();
		}
	}

	return	bReturn;
}

bool JHTetris::OnLeft()
{
	bool	bReturn = true;

	if (m_bGameBegin)
	{
		OnBlockCopyC2T();
		m_nPosX--;

		if (OnCheckCollision())
		{
			OnBlockCopyT2C();
			bReturn = false;
			OnImpossibleAct();
		}
		else
		{
			OnBlockMoveAct();
		}
	}

	return	bReturn;
}

bool JHTetris::OnRight()
{
	bool	bReturn = true;

	if (m_bGameBegin)
	{
		OnBlockCopyC2T();
		m_nPosX++;

		if (OnCheckCollision())
		{
			OnBlockCopyT2C();
			bReturn = false;
			OnImpossibleAct();
		}
		else
		{
			OnBlockMoveAct();
		}
	}

	return	bReturn;
}

bool JHTetris::OnRotate()
{
	bool	bReturn = true;

	if (m_bGameBegin)
	{
		OnBlockCopyC2T();

		for (int i = 0 ; i < BLOCK_WIDTH ; i++)
		{
			for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
			{
				m_BrkCurr[i][j].nFill	= m_BrkTemp[j][BLOCK_HEIGHT - 1 - i].nFill;
				m_BrkCurr[i][j].nColor	= m_BrkTemp[j][BLOCK_HEIGHT - 1 - i].nColor;
			}
		}

		if (OnCheckCollision())
		{
			OnBlockCopyT2C();
			bReturn = false;
			OnImpossibleAct();
		}
		else
		{
			OnBlockTurnAct();
		}
	}

	return	bReturn;
}

int	JHTetris::OnCheckLine()
{
	int	nReturn = 0;

	for (int i = 0 ; i < TOTAL_BRICK_NUM_Y ; i++)
	{
		if (OnCheckComplete(i))
		{
			OnArrangeLine(i);
			nReturn++;
		}
	}

	if (nReturn > 0)
	{
		m_nScore = m_nScore + nReturn + (nReturn - 1);
	}

 	m_nLine = m_nLine + nReturn;

	return	nReturn;
}

bool JHTetris::OnCheckOver()
{
	bool	bReturn = false;

	if (m_nPosY < 0)
	{
		bReturn = true;
	}

	return	bReturn;
}

bool JHTetris::OnCheckCollision()
{
	int		i = 0;
	int		j = 0;
	bool	bReturn = false;

	for (i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			if (OnCheckValidArea(m_nPosX + i, m_nPosY + j))
			{
				if (m_BrkBoard[m_nPosX + i][m_nPosY + j].nFill & m_BrkCurr[i][j].nFill)
				{
					bReturn = true;
				}
			}
		}
	}

	for (i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (j = 0 ; j < BLOCK_HEIGHT ; j++)
		{
			if (m_BrkCurr[i][j].nFill == BRICK_FILLED)
			{
				if ((m_nPosX + i) < 0)
				{
					bReturn = true;
				}

				if ((m_nPosX + i) >= TOTAL_BRICK_NUM_X)
				{
					bReturn = true;
				}

				if ((m_nPosY + j) >= TOTAL_BRICK_NUM_Y)
				{
					bReturn = true;
				}
			}
		}
	}

	return	bReturn;
}

bool JHTetris::OnCheckComplete(int nLine)
{
	bool	bReturn = true;

	for (int i = 0 ; i < TOTAL_BRICK_NUM_X ; i++)
	{
		if (m_BrkBoard[i][nLine].nFill == BRICK_EMPTY)
		{
			bReturn = false;
			break;
		}
	}

	if (bReturn)
	{
		OnLineCompleteAct(nLine);
	}

	return bReturn;
}

bool JHTetris::OnCheckValidArea(int nX, int nY)
{
	bool bReturn = true;

	if (nX < 0)
	{
		bReturn = false;
	}
	else if (nX >= TOTAL_BRICK_NUM_X)
	{
		bReturn = false;
	}
	else if (nY < 0)
	{
		bReturn = false;
	}
	else if (nY >= TOTAL_BRICK_NUM_Y)
	{
		bReturn = false;
	}

	return bReturn;
}

void JHTetris::OnArrangeLine(int nLine)
{
	for (int i = 0 ; i < TOTAL_BRICK_NUM_X ; i++)
	{
		m_BrkBoard[i][nLine].nFill	= BRICK_EMPTY;
		m_BrkBoard[i][nLine].nColor	= 0;
	}

	for (int j = nLine ; j > 0 ; j--)
	{
		for (int k = 0 ; k < TOTAL_BRICK_NUM_X ; k++)
		{
			m_BrkBoard[k][j].nFill	= m_BrkBoard[k][j - 1].nFill;
			m_BrkBoard[k][j].nColor	= m_BrkBoard[k][j - 1].nColor;
		}
	}
}

/////////////////=======================================================/////////////////
/////////																		/////////
/////////						VIRTUAL MEMBERS									/////////
/////////																		/////////
/////////////////=======================================================/////////////////

void JHTetris::OnGameStartAct()
{

}

void JHTetris::OnGameOverAct()
{

}

void JHTetris::OnBlockCopyN2CAct()
{

}

void JHTetris::OnLineCompleteAct(int nLine)
{

}

void JHTetris::OnBlockDownAct()
{

}

void JHTetris::OnBlockTurnAct()
{

}

void JHTetris::OnBlockMoveAct()
{

}

void JHTetris::OnImpossibleAct()
{
}

void JHTetris::OnSettleAct()
{

}

//--------------------------------------------------------------------------------------//

#endif
