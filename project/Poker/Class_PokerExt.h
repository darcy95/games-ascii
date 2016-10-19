/**
 * # Poker
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

/**
 * # Attribution
 *
 * This program internally uses the poker hand evaluator developed by Kevin L.
 *
 *  //----------------------------------------------------------------------//
 *  //	Kevin L. Suffecool'5 Poker Hand Evaluator 
 *  //	Web Site  - http://www.suffecool.net/poker/evaluator.html
 *  //----------------------------------------------------------------------//
 *
 */



#ifndef _JHPOKER_EXT_C_
#define _JHPOKER_EXT_C_

extern JHAnsi g_Ansi;

//--------------------------------------------------------------------------------------//

class JHPokerExt : public JHPoker
{
public:
	virtual int		getChoice();
	virtual	P_ULINT getAmount(int nChoice);
	virtual void	selectCards();
	virtual bool	accuMoney(P_ULINT nAmount);

public:
	void draw_title();
	void draw_frame();
	void draw_betmoney();
	void draw_pause();
	void draw_player();
	void draw_hand(JHPokerPlayer* pPlayer, int nX, int nY);
	void draw_turn();
	void draw_boss();
	void draw_hold(int nSeat);
	void draw_all();
	void draw_result();
	void draw_info();
	void draw_entrance(char* szName);
	void draw_askmore();
};

//--------------------------------------------------------------------------------------//

int	JHPokerExt::getChoice()
{
	int	 i = 0;
	int	 nChoice = POKER_BETTING_NONE;
	bool bBet[6];

	draw_turn();
	draw_betmoney();
	draw_player();

	do
	{
		for (i = 0 ; i < 6 ; i++)
		{
			bBet[i] = false;
		}

		g_Ansi.remLine(SCREEN_START_Y + 23);
		printf("Your Turn : ");
		printf("%d)Fold ",	POKER_BETTING_FOLD);

		bBet[POKER_BETTING_FOLD] = true;
	
		if (getStayMoney() == 0)
		{
			printf("%d)Bet ",	POKER_BETTING_BET);
			
			bBet[POKER_BETTING_BET] = true;
		}
		else if (getStayMoney() > 0)
		{
			printf("%d)Call ",	POKER_BETTING_CALL);
			printf("%d)Raise ", POKER_BETTING_RAISE);
		
			bBet[POKER_BETTING_CALL]  = true;
			bBet[POKER_BETTING_RAISE] = true;
		}

		if (getCheck() == true)
		{
			printf("%d)Check ", POKER_BETTING_CHECK);
		
			bBet[POKER_BETTING_CHECK] = true;
		}

		scanf("%d", &nChoice);
		scanff();

		if (bBet[nChoice] == false)
		{
			nChoice = POKER_BETTING_NONE;
			continue;
		}
	}
	while ((nChoice < 1) || (nChoice > 5));

	setBetBuff(nChoice);

	return nChoice;
}

P_ULINT JHPokerExt::getAmount(int nChoice)
{
	P_ULINT nAmount = 0;

	if ((nChoice != POKER_BETTING_BET) && (nChoice != POKER_BETTING_RAISE))
	{
		return nAmount;
	}

	while ((nAmount < 1) || (nAmount > 1000))
	{
		g_Ansi.remLine(SCREEN_START_Y + 23);
		printf("How much? (1$ ~ 1000$) ");
		scanf("%d", &nAmount);
		scanff();
	}

	return nAmount;
}

void JHPokerExt::selectCards()
{
	int nChoice = -1;

	draw_turn();

	while (nChoice != 0)
	{
		g_Ansi.remLine(SCREEN_START_Y + 23);
		g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "Select card, which you want to hold ");
		g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "(0:Done, 1~5:Card Number)");
		g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, " - ");
		scanf("%d", &nChoice);
		scanff();

		if ((nChoice > 0) && (nChoice < 6))
		{
			toggleSelBuff(nChoice - 1);
			draw_hold(getTurn());
		}
	}
}

bool JHPokerExt::accuMoney(P_ULINT nAmount)
{
	int		nChoice = -1;
	bool	bChoice;

	draw_turn();
	draw_betmoney();
	draw_player();

	while ((nChoice != 0) && (nChoice != 1))
	{
		g_Ansi.remLine(SCREEN_START_Y + 23);
		g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "Money was raised. You need %5d$ for staying. ", nAmount);
		g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "0)Fold or 1)Call : ");
		scanf("%d", &nChoice);
		scanff();
	}		

	if (nChoice == 0)
	{
		bChoice = false;
	}
	else
	{
		bChoice = true;
	}

	return bChoice;
}

void JHPokerExt::draw_title()
{
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "+-----------------------------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "|                                 POKER                                 |\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "+-----------------------------------------------------------------------+\r\n");
}

void JHPokerExt::draw_frame()
{
	printf("\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "+---------------------+-+                       +---------------------+-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     | |                       |                     | |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     +-+                       |                     +-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     | |                       |                     | |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     +-+                       |                     +-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "+---------------------+-+---------------------+-+---------------------+-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     | |                     | |                     | |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     +-+                     +-+                     +-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     | |                     | |                     | |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                     +-+                     +-+                     +-+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                       |                       |                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "+-----------------------+-----------------------+-----------------------+\r\n");
}

void JHPokerExt::draw_betmoney()
{
	g_Ansi.setCursor(SCREEN_START_X + 26, SCREEN_START_Y + 5);
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "Total %12d$", getBetMoney());

	g_Ansi.setCursor(SCREEN_START_X + 26, SCREEN_START_Y + 6);
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "For Staying %6d$", getStayMoney());
}

void JHPokerExt::draw_pause()
{
	while (!kbhit());
}

void JHPokerExt::draw_player()
{
	int i;
	int nX = 0;
	int nY = 0;
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		switch (pEachPlayer[i]->getSeat())
		{
			case 0:	{ nX = 26; nY = 14; } break;
			case 1: { nX =  2; nY = 14; } break;
			case 2: { nX =  2; nY =  5; } break;
			case 3: { nX = 50; nY =  5; } break;
			case 4: { nX = 50; nY = 14;	} break;
		}

		g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY);
		g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, "%s", pEachPlayer[i]->getName());

		g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY + 1);
		g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "Money : %8d", pEachPlayer[i]->getMoney());

		draw_hand(pEachPlayer[i], nX, nY + 2);
	}
}

void JHPokerExt::draw_hand(JHPokerPlayer* pPlayer, int nX, int nY)
{
	int		nKind	= -1;
	int		nValue	= -1;
	char	szKind;
	char	szValue[2];

	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		if (pPlayer->isDrop() == true)
		{
				szKind = '-';
				sprintf(szValue, "--");
		}
		else
		{
			if ((pPlayer->isHuman() == true) || (getGameStep() == POKER_STEP_RESULT))
			{
				nKind	= getCardKind(pPlayer->getCard(i));
				nValue	= getCardValue(pPlayer->getCard(i));

				switch (nKind)
				{
					case POKER_KIND_SPADE:		szKind = 'S'; break;
					case POKER_KIND_DIAMOND:	szKind = 'D'; break;
					case POKER_KIND_HEART:		szKind = 'H'; break;
					case POKER_KIND_CLUB:		szKind = 'C'; break;
				}

				switch (nValue)
				{
					case 0:	sprintf(szValue, "A"); break;
					case 1:	case 2:	case 3:	case 4:	case 5:	
					case 6:	case 7:	case 8:	case 9:	sprintf(szValue, "%d", nValue + 1); break;
					case 10: sprintf(szValue, "J"); break;
					case 11: sprintf(szValue, "Q"); break;
					case 12: sprintf(szValue, "K"); break;					
				}
			}
			else
			{
				szKind = '*';
				sprintf(szValue, "??");
			}
		}

		g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY + i + 1);
		g_Ansi.drawText(ANSI_RED, ANSI_BLACK, "%d) ", i + 1);
		g_Ansi.drawText(ANSI_BLACK, ANSI_GRAY, "%c", szKind);
		g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "%s", szValue);
		printf(" ");
	}
}

void JHPokerExt::draw_turn()
{
	int nX = 0;
	int nY = 0;

	g_Ansi.setCursor(SCREEN_START_X + 47, SCREEN_START_Y + 14);
	g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, " ");

	g_Ansi.setCursor(SCREEN_START_X + 23, SCREEN_START_Y + 14);
	g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, " ");

	g_Ansi.setCursor(SCREEN_START_X + 23, SCREEN_START_Y +  5);
	g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, " ");

	g_Ansi.setCursor(SCREEN_START_X + 71, SCREEN_START_Y +  5);
	g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, " ");

	g_Ansi.setCursor(SCREEN_START_X + 71, SCREEN_START_Y + 14);
	g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, " ");

	switch (getTurn())
	{
		case 0:	{ nX = 47; nY = 14; } break;
		case 1: { nX = 23; nY = 14; } break;
		case 2: { nX = 23; nY =  5; } break;
		case 3: { nX = 71; nY =  5; } break;
		case 4: { nX = 71; nY = 14;	} break;
	}

	g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY);
	g_Ansi.drawText(ANSI_GRAY, ANSI_RED, "T");
}

void JHPokerExt::draw_boss()
{
	int nX = 0;
	int nY = 0;

	switch (getBoss())
	{
		case 0:	{ nX = 47; nY = 16; } break;
		case 1: { nX = 23; nY = 16; } break;
		case 2: { nX = 23; nY =  7; } break;
		case 3: { nX = 71; nY =  7; } break;
		case 4: { nX = 71; nY = 16;	} break;
	}

	g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY);
	g_Ansi.drawText(ANSI_GRAY, ANSI_PURPLE, "B");
}

void JHPokerExt::draw_hold(int nSeat)
{
	int nX = 0;
	int nY = 0;

	switch (nSeat)
	{
		case 0:	{ nX = 34; nY = 17; } break;
		case 1: { nX = 10; nY = 17; } break;
		case 2: { nX = 10; nY =  8; } break;
		case 3: { nX = 58; nY =  8; } break;
		case 4: { nX = 58; nY = 17;	} break;
	}

	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY + i);
		
		if (getSelBuff(i) == true)
		{
			g_Ansi.drawText(ANSI_RED, ANSI_GRAY, "HOLD");
		}
		else
		{
			g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, "    ");
		}
	}
}

void JHPokerExt::draw_all()
{
	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
	draw_title();
	draw_frame();
	draw_betmoney();
	draw_turn();
	draw_boss();
	draw_player();
	draw_result();
	draw_askmore();
	draw_info();
}

void JHPokerExt::draw_result()
{
	int i, j;
	int nX, nY;
	int hand[5];
	int nPlayers = getPlayerNum();
	int nChoice = POKER_BETTING_NONE;
	P_ULINT	nAmount = 0;
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		switch (pEachPlayer[i]->getSeat())
		{
			case 0:	{ nX = 26; nY = 16; } break;
			case 1: { nX =  2; nY = 16; } break;
			case 2: { nX =  2; nY =  7; } break;
			case 3: { nX = 50; nY =  7; } break;
			case 4: { nX = 50; nY = 16;	} break;
		}

		if (pEachPlayer[i]->getResultHand() > 0)
		{
			g_Ansi.setCursor(SCREEN_START_X + nX, SCREEN_START_Y + nY);
			
			if (pEachPlayer[i]->isDrop() == true)
			{
				g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "%13s", "Fold");
			}
			else
			{
				g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "%15s", value_str[hand_rank(pEachPlayer[i]->getResultHand())]);
			}
		}
	}
}

void JHPokerExt::draw_info()
{
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 3);
	g_Ansi.drawText(ANSI_GRAY, ANSI_PURPLE, "Current Step : %d", getGameStep());
}

void JHPokerExt::draw_entrance(char* szName)
{
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "+-----------------------------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                                                                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "| Can you tell us your name?");
	g_Ansi.drawText(ANSI_RED,  ANSI_BLACK, " (up to 10 characters)                      ");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "|                                                                       |\r\n");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "+-----------------------------------------------------------------------+\r\n");
	g_Ansi.setCursor(SCREEN_START_X + 55, SCREEN_START_Y + 5);
	scanf("%s", szName);
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 9);
}

void JHPokerExt::draw_askmore()
{
	if (isGamePause() == true)
	{
		int nChoice = -1;

		while ((nChoice != 0) && (nChoice != 1))
		{
			g_Ansi.remLine(SCREEN_START_Y + 23);
			g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "0)End or 1)Deal : ");
			scanf("%d", &nChoice);
			scanff();
		}		

		if (nChoice == 0)
		{
			setGameBegin(false);
		}
		else if (nChoice == 1)
		{
			setGamePause(false);
		}
	}
}

//--------------------------------------------------------------------------------------//

#endif
