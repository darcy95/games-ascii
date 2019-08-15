/* =====================================================================================
 *	JHPoker Ver, 1.0
 * 
 *	Copyright (c) Kimjuhoon 2005 All rights reserved
 *
 *	Redistribution and use in source and binary forms are permitted without any condition.
 *	Note that I cannot garantee anything about this source code. Work on your own risk.
 *
 */

#include "poker.h"

JHPokerPlayer::JHPokerPlayer()
{
	init();
}

JHPokerPlayer::~JHPokerPlayer()
{
	
}

P_ULINT	JHPokerPlayer::delMoney(P_ULINT nMoney)
{
	P_ULINT	nTemp = m_nMoney;

	m_nMoney = (m_nMoney > nMoney) ? (m_nMoney - nMoney) : 0;

	if (m_nMoney == 0)
	{
		return nTemp;
	}

	return 0;
}

int JHPokerPlayer::getEmptySlot()
{
	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		if (m_nHand[i] == POKER_CARD_NONE)
		{
			return i;
		}
	}

	return -1;
}

bool JHPokerPlayer::setCard(int nCardNum)
{
	int nEmptySlot = getEmptySlot();

	if (nEmptySlot < 0)
	{
		return false;
	}
	else
	{
		m_nHand[nEmptySlot]	= nCardNum;
	}

	return true;
}

int JHPokerPlayer::getEmptySlotNum()
{
	int nReturn = 0;

	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		if (m_nHand[i] == POKER_CARD_NONE)
		{
			nReturn++;
		}
	}

	return nReturn;
}

void JHPokerPlayer::sortHand()
{
	int i = 0;
	int j = 0;
	int	r = 0;

	for (i = 1 ; i < POKER_PLAYER_HAND ; i++) 
	{
		//	배열 번호대로가 아니라 카드의 값(0~12)을 기준으로 정렬하기 위해 POKER_CARD_COUNT로 나눈 갑들을 비교한다.
		for (j = i - 1, r = m_nHand[i] ; j >= 0 && (m_nHand[j] % POKER_CARD_COUNT) > (r % POKER_CARD_COUNT) ; j--)
		{
			m_nHand[j + 1] = m_nHand[j];
		}

		m_nHand[j + 1] = r;
	}
}

void JHPokerPlayer::initHand()
{
	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		m_nHand[i] = POKER_CARD_NONE;
	}
}

void JHPokerPlayer::init()
{
	initHand();
	setResultHand(0);
	setDrop(false);
	setLastBetAmount(0);
}

int	 JHPokerPlayer::getChoice()
{
//	return POKER_BETTING_CHECK;
	return POKER_BETTING_CALL;
}

bool JHPokerPlayer::accuMoney()
{
	return true;
}

void JHPokerPlayer::selectCards()
{

}

P_ULINT JHPokerPlayer::getAmount(int nChoice)
{
	return 0;
}

//--------------------------------------------------------------------------------------//
//	Class JHPoker
//--------------------------------------------------------------------------------------//

JHPoker::JHPoker()
{
	init();
	setTurn(0);
	setBoss(0);
	setPlayerNum(0);
	setMinPlayer(2);
	setMaxPlayer(4);
	setGameBegin(false);
	setGamePause(false);

	InitializePokerList();
}

JHPoker::~JHPoker()
{     
	POKER_SAFE_DELETE(PokerNodeHead);
	POKER_SAFE_DELETE(PokerNodeTail);
}

void JHPoker::DoUpdate()
{
	switch (getGameStep())
	{
		case POKER_STEP_NONE:
		{
			Wait();
		}
		break;

		case POKER_STEP_ANTE:
		{
			Ante();
		}
		break;

		case POKER_STEP_FIRSTDEAL:
		{
			DealFirstCards();
		}
		break;

		case POKER_STEP_BETTING1:
		case POKER_STEP_BETTING2:
		{
			Betting();
		}
		break;

		case POKER_STEP_THROWCARDS:
		{
			PlayerThrowCards();
		}
		break;

		case POKER_STEP_SECONDDEAL:
		{
			DealSecondCards();
		}
		break;

		case POKER_STEP_RESULT:
		{
			GetResult();
		}
		break;
	}
}

void JHPoker::handleChoice(JHPokerPlayer* pPlayer, int nChoice)
{
	switch (nChoice)
	{
		case POKER_BETTING_FOLD:
		{
			pPlayer->setDrop(true);
		}
		break;

		case POKER_BETTING_BET:		break;
		case POKER_BETTING_CALL:	break;
		case POKER_BETTING_RAISE:	break;
		case POKER_BETTING_CHECK:	break;
	}
}

void JHPoker::init()
{
	initDeck();
	Shuffle();
	setWinner(-1); // Nobody
	setGameStep(POKER_STEP_NONE);
	setCardIndex(POKER_CARD_ALL - 1);
	setLastTurn(false);
	setBetBuff(POKER_BETTING_NONE);
	setBetMoney(0);
	setStayMoney(0);
	setCheck(true);
	initSelBuff();
	setGamePause(false);
	setRaised(false);
}

void JHPoker::initDeck()
{
	for (int i = 0 ; i < POKER_CARD_ALL ; i++)
	{
		m_nDeck[i] = i;
	}
}

void JHPoker::initSelBuff()
{
	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		m_bSelBuff[i] = false;
	}
}

void JHPoker::initPlayers()
{
	int i;
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		pEachPlayer[i]->init();
	}
}

void JHPoker::Shuffle()
{
	int	i;
	int	j;
	int	nRandom;
	int	nTemp;

	srand((unsigned) time(NULL));

	for (i = 0 ; i < POKER_SHUFFLE_TIME ; i++)
	{
		for (j = 0 ; j < POKER_CARD_ALL ; j++)
		{
			nRandom = random() % POKER_CARD_ALL;

			if (j != nRandom)
			{
				nTemp				= m_nDeck[nRandom];
				m_nDeck[nRandom]	= m_nDeck[j];
				m_nDeck[j]			= nTemp;
			}
		}
	}
}

int JHPoker::setTurnClockwise()
{
	int i = 0;
	int j = 0;
	int	r = 0;
	int nPlayers = getPlayerNum();
	int nPlayer[nPlayers];	

	bool bLastTurn = false;

	PokerNode*		ptr;
	JHPokerPlayer*	pPlayer;

	for (i = 0 ; i < nPlayers ; i++)
	{
		nPlayer[i] = 0;
	}

	ptr = PokerNodeHead->Next;

	for (i = 0 ; ptr != PokerNodeTail ; i++)
	{
		pPlayer = (JHPokerPlayer*) ptr->data;
		nPlayer[i] = pPlayer->getSeat();
		ptr = ptr->Next;
	}

	//	Insertion Sort
	for (i = 1 ; i < nPlayers ; i++) 
	{
		for (j = i - 1, r = nPlayer[i] ; j >= 0 && nPlayer[j] > r ; j--)
		{
			nPlayer[j + 1] = nPlayer[j];
		}

		nPlayer[j + 1] = r;
	}

	for (i = 0 ; i < nPlayers ; i++)
	{
		if (nPlayer[i] == m_nTurn)
		{
			m_nTurn	= (i == (nPlayers - 1)) ? nPlayer[0] : nPlayer[i + 1];

			bLastTurn = (m_nTurn == nPlayer[nPlayers - 1]) ? true : false;

			setLastTurn(bLastTurn);

			break;
		}
	}

	return m_nTurn;
}

int JHPoker::getEmptySeat()
{
	int		i = 0;
	int		nMax = getMaxPlayer();
	bool	bPlayerSeat[nMax];

	for (i = 0 ; i < nMax ; i++)
	{
		bPlayerSeat[i] = false;
	}

	PokerNode*		ptr;
	JHPokerPlayer*	pPlayer;

	ptr = PokerNodeHead->Next;

	while (ptr != PokerNodeTail) 
	{
		pPlayer = (JHPokerPlayer*) ptr->data;
		bPlayerSeat[pPlayer->getSeat()] = true;
		ptr = ptr->Next;
	}
	
	for (i = 0 ; i < nMax ; i++)
	{
		if (bPlayerSeat[i] == false)
		{
			return i;
		}
	}

	return -1;
}

int JHPoker::addPlayer()
{
	if (getPlayerNum() > getMaxPlayer())
	{
		return -1;
	}

	JHPokerPlayer* pPlayer = new JHPokerPlayer;
	pPlayer->setMoney(POKER_START_MONEY);

	return addPlayer(pPlayer);
}

int JHPoker::addPlayer(JHPokerPlayer* pPlayer)
{
	if (getPlayerNum() > getMaxPlayer())
	{
		return -1;
	}

	int nEmptySeat = getEmptySeat();

	if (nEmptySeat >= 0)
	{
		pPlayer->setSeat(nEmptySeat);

		PokerNode* pNewPlayer = new PokerNode;
		pNewPlayer->data = (char*) pPlayer;

		InsertPokerNode(pNewPlayer);
		addPlayerNum();

		return nEmptySeat;
	}

	return -2;
}

bool JHPoker::remPlayer(int nPlayerIndex)
{
	if (getPlayerNum() <= 0)
	{
		return false;
	}

	if (isPlayerValid(nPlayerIndex))
	{
		DeletePokerNode(nPlayerIndex);
		delPlayerNum();
	}
	else
	{
		return false;
	}

	return true;
}

int	JHPoker::convHand(int nCard)
{
	int nNum  = (nCard + 12) % 13;
	int oSuit;

	switch ((nCard) / 13)
	{
		case POKER_KIND_CLUB:	 oSuit = 0x8000; break; 
		case POKER_KIND_DIAMOND: oSuit = 0x4000; break; 
		case POKER_KIND_HEART:	 oSuit = 0x2000; break; 
		case POKER_KIND_SPADE:	 oSuit = 0x1000; break; 
	}

	return (primes[nNum] | (nNum << 8) | oSuit | (1 << (16 + nNum)));
}

bool JHPoker::remPlayerAll()
{
	int i = 0;
	int nPlayers = getPlayerNum();
	int nIndex[nPlayers];

	PokerNode*		ptr;
	JHPokerPlayer*	pPlayer;

	ptr = PokerNodeHead->Next;

	i = 0;

	while (ptr != PokerNodeTail) 
	{
		pPlayer		= (JHPokerPlayer*) ptr->data;
		nIndex[i]	= pPlayer->getSeat();
		ptr			= ptr->Next;
		i++;
	}

	for (i = 0 ; i < nPlayers ; i++)
	{
		if (!remPlayer(nIndex[i]))
		{
			return false;
		}
	}

	return true;
}

int JHPoker::getRemains()
{
	int i, nCount = 0;
	int nPlayers = getPlayerNum();
	JHPokerPlayer*	pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		if (pEachPlayer[i]->isDrop() == false)
		{
			nCount++;
		}
	}

	return nCount;
}

bool JHPoker::isPlayerValid(int nPlayerIndex)
{
	PokerNode*		ptr;
	JHPokerPlayer*	pPlayer;

	ptr = PokerNodeHead->Next;

	while (ptr != PokerNodeTail) 
	{
		pPlayer = (JHPokerPlayer*) ptr->data;

		if (pPlayer->getSeat() == nPlayerIndex)
		{
			return true;
		}

		ptr = ptr->Next;
	}

	return false;
}

void JHPoker::dealSingleCard(JHPokerPlayer*	pPlayer, int nHowmany)
{
	if (pPlayer->isDrop() == false)
	{
		for (int i = 0 ; i < nHowmany ; i++)
		{
			pPlayer->setCard(getCardNum(getCardIndex()));
			setCardNum(getCardIndex(), POKER_CARD_NONE);
			remCardIndex();
		}
	}
}

void JHPoker::dealCardsToAll()
{
	int i;
	int nPlayers = getPlayerNum();
	JHPokerPlayer*	pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		dealSingleCard(pEachPlayer[i]);
		setTurnClockwise();
	}
}

void JHPoker::calcMoney(JHPokerPlayer* pPlayer, int nChoice, P_ULINT nAmount)
{
	switch (nChoice)
	{
		case POKER_BETTING_BET:
		case POKER_BETTING_RAISE:
		{
			addStayMoney(nAmount);
			addBetMoney(getStayMoney());
			pPlayer->delMoney(getStayMoney());
			pPlayer->setLastBetAmount(getStayMoney());
		}
		break;

		case POKER_BETTING_CALL:
		{
			addBetMoney(getStayMoney());
			pPlayer->delMoney(getStayMoney());
			pPlayer->setLastBetAmount(getStayMoney());
		}
		break;

		case POKER_BETTING_FOLD:
		case POKER_BETTING_CHECK:
		{
			pPlayer->setLastBetAmount(0);
		}
		break;
	}
}

void JHPoker::calcMoney(JHPokerPlayer* pPlayer, P_ULINT nAmount, bool bPlayerGets)
{
	if (bPlayerGets == true)
	{
		pPlayer->addMoney(nAmount);
		delBetMoney(nAmount);
	}
	else
	{
		pPlayer->delMoney(nAmount);
		addBetMoney(nAmount);
	}
}

void JHPoker::listPlayers(JHPokerPlayer** ppPlayer)
{
	PokerNode*		ptr;
	JHPokerPlayer*	pTempPlayer;
	
	ptr = PokerNodeHead->Next;

	while (ptr != PokerNodeTail)
	{
		pTempPlayer = (JHPokerPlayer*) ptr->data;
		ppPlayer[pTempPlayer->getSeat()] = pTempPlayer;
		ptr = ptr->Next;
	}
}

void JHPoker::sortPlayers(JHPokerPlayer** ppPlayer, int nPlayers)
{
	int i = 0;
	int j = 0;
	int	r = 0;
	int nBoss = getBoss();
	JHPokerPlayer	TempPlayer[nPlayers];

	for (i = 1 ; i < nPlayers ; i++) 
	{
		for (j = i - 1, r = i ; j >= 0 && j > r ; j--)
		{
			ppPlayer[j + 1] = ppPlayer[j];
		}

		ppPlayer[j + 1] = ppPlayer[r];
	}

	for (i = 0 ; i < nPlayers ; i++) 
	{
		TempPlayer[i] = *ppPlayer[i];
	}

	for (i = 0 ; i < nPlayers ; i++) 
	{
		*ppPlayer[i] = TempPlayer[(i + nBoss) % nPlayers]; 
	}
}

int	JHPoker::calcWinner()
{
	int i = 0;
	int j = 0;
	int	r = 0;
	int nPlayers = getPlayerNum();
	int	nMinRank = 10000;
	JHPokerPlayer*	pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);

	for (i = 0 ; i < nPlayers ; i++)
	{
		if (pEachPlayer[i]->isDrop() != true)
		{
			nMinRank = (pEachPlayer[i]->getResultHand() < nMinRank) ? pEachPlayer[i]->getResultHand() : nMinRank;
		}
	}

	for (i = 0 ; i < nPlayers ; i++)
	{
		if (pEachPlayer[i]->getResultHand() == nMinRank)
		{
			return i;
		}
	}

	return -1;
}

void JHPoker::Wait()
{
	if (isGamePause() == false)
	{		
		init();
		initPlayers();
		setGameStep(getGameStep() + 1);
	}
}

void JHPoker::Ante()
{
	int i;
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		if (pEachPlayer[i]->delMoney(POKER_ANTE_MONEY) != 0)
		{
			pEachPlayer[i]->setDrop(true);
		}
		else
		{
			addBetMoney(POKER_ANTE_MONEY);
		}

		setTurnClockwise();
	}

	setGameStep(getGameStep() + 1);
}

void JHPoker::DealFirstCards()
{
	for (int i = 0 ; i < POKER_PLAYER_HAND ; i++)
	{
		dealCardsToAll();
	}

	setGameStep(getGameStep() + 1);
}

void JHPoker::PlayerThrowCards()
{
	int i, j;
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		if (pEachPlayer[i]->isDrop() == false)
		{
			if (pEachPlayer[i]->isHuman())
			{
				initSelBuff();
				selectCards();

				for (j = 0 ; j < POKER_PLAYER_HAND ; j++)
				{
					if (getSelBuff(j) == false)
					{
						pEachPlayer[i]->setCard(j, POKER_CARD_NONE);
					}
				}
			}
			else
			{
				pEachPlayer[i]->selectCards();
			}
		}

		setTurnClockwise();
	}

	setGameStep(getGameStep() + 1);
}

void JHPoker::DealSecondCards()
{
	int i;
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		dealSingleCard(pEachPlayer[i], pEachPlayer[i]->getEmptySlotNum());
		setTurnClockwise();
	}

	setGameStep(getGameStep() + 1);
}

void JHPoker::Betting()
{
	int i;
	int nPlayers = getPlayerNum();
	int nChoice = POKER_BETTING_NONE;

	P_ULINT	nAmount = 0;
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);
	sortPlayers(pEachPlayer, nPlayers);

	setCheck(true);		
	setRaised(false);	
	setStayMoney(0);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		if (pEachPlayer[i]->isDrop() == false)
		{
			if (getRemains() == 1)
			{
				setGameStep(POKER_STEP_RESULT);
				return;
			}

			if (pEachPlayer[i]->isHuman())
			{
				nChoice = getChoice();
				nAmount = getAmount(nChoice);
			}
			else
			{
				nChoice = pEachPlayer[i]->getChoice();
				nAmount = pEachPlayer[i]->getAmount(nChoice);
			}

			handleChoice(pEachPlayer[i], nChoice);
			calcMoney(pEachPlayer[i], nChoice, nAmount);

			if (getCheck() == true)
			{
				if ((nChoice == POKER_BETTING_CHECK) || (nChoice == POKER_BETTING_FOLD))
				{
					setCheck(true);

					setRaised(false);
				}
				else
				{
					setCheck(false);

					if (pEachPlayer[i]->getSeat() != getBoss())
					{
						setRaised(true);
					}
				}
			}
			else
			{
				if (nChoice == POKER_BETTING_RAISE)
				{
					setRaised(true);
				}
			}
		}

		setTurnClockwise();
	}

	if (isRaised() == true)
	{
		bool	bAccept;
		P_ULINT nAdjustment = 0;

		for (i = 0 ; i < nPlayers ; i++) 
		{
			nAdjustment = getStayMoney() - pEachPlayer[i]->getLastBetAmount();

			if ((pEachPlayer[i]->isDrop() == false) && (nAdjustment > 0))
			{
				if (pEachPlayer[i]->isHuman())
				{
					bAccept = accuMoney(nAdjustment);
				}
				else 
				{
					bAccept = pEachPlayer[i]->accuMoney();
				}

				if (bAccept == true)
				{
					calcMoney(pEachPlayer[i], nAdjustment, false);
				}
				else
				{
					pEachPlayer[i]->setDrop(true);
				}
			}

			setTurnClockwise();
		}	
	}

	setGameStep(getGameStep() + 1);
}

void JHPoker::GetResult()
{
	int i, j;
	int hand[5];
	int nPlayers = getPlayerNum();
	JHPokerPlayer* pEachPlayer[nPlayers];
	listPlayers(pEachPlayer);

	for (i = 0 ; i < nPlayers ; i++) 
	{
		for (j = 0 ; j < POKER_PLAYER_HAND ; j++)
		{
			hand[j] = convHand(pEachPlayer[i]->getCard(j));
		}

		pEachPlayer[i]->setResultHand(eval_5hand(hand));
	}

	setWinner(calcWinner());
	calcMoney(pEachPlayer[getWinner()], getBetMoney(), true);
	setBoss(getWinner());
	setTurn(getWinner());
	setGamePause(true);
	setGameStep(POKER_STEP_NONE);
}

int	JHPoker::getChoice()
{

}

void JHPoker::selectCards()
{

}

P_ULINT JHPoker::getAmount(int nChoice)
{

}

bool JHPoker::accuMoney(P_ULINT nAmount)
{

}
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
