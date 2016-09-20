#include "common/StdAfx.h"
#include "common/Class_Poker.h"
#include "common/Class_Ansi.h"
#include "common/Func_Inputk.h"
#include "Class_PokerExt.h"

JHAnsi		g_Ansi;
JHPokerExt	g_Poker;

int main(int argc, char *argv[])
{
	int		i = 0; 
	char	szName[20];

	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);

	g_Poker.setMaxPlayer(5);
	g_Poker.setBoss(0);
	g_Poker.setTurn(0);
	g_Poker.setGameBegin(true);
	g_Poker.draw_title();
	g_Poker.draw_entrance(szName);

	//	Player 0 추가
	JHPokerPlayer* pPlayer0 = new JHPokerPlayer;
	pPlayer0->setMoney(100000);
	pPlayer0->setName(szName);	
	pPlayer0->setHuman(true);
	g_Poker.addPlayer(pPlayer0);
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "     ---> Player");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " %10s ", pPlayer0->getName());
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "entered the room.\r\n");

	//	Player 1 추가
	JHPokerPlayer* pPlayer1 = new JHPokerPlayer;
	pPlayer1->setMoney(100000);
	pPlayer1->setName("Peter");
	pPlayer1->setHuman(true);
	g_Poker.addPlayer(pPlayer1);
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "     ---> Player");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " %10s ", pPlayer1->getName());
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "entered the room.\r\n");

	//	Player 2 추가
	JHPokerPlayer* pPlayer2 = new JHPokerPlayer;
	pPlayer2->setMoney(100000);
	pPlayer2->setName("Mary");
	pPlayer2->setHuman(true);
	g_Poker.addPlayer(pPlayer2);
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "     ---> Player");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " %10s ", pPlayer2->getName());
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "entered the room.\r\n");

	//	Player 3 추가
	JHPokerPlayer* pPlayer3 = new JHPokerPlayer;
	pPlayer3->setMoney(100000);
	pPlayer3->setName("Coral");
	pPlayer3->setHuman(true);
	g_Poker.addPlayer(pPlayer3);
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "     ---> Player");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " %10s ", pPlayer3->getName());
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "entered the room.\r\n");

	//	Player 4 추가
	JHPokerPlayer* pPlayer4 = new JHPokerPlayer;
	pPlayer4->setMoney(100000);
	pPlayer4->setName("Mr, Boss");
	pPlayer4->setHuman(true);
	g_Poker.addPlayer(pPlayer4);
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "     ---> Player");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " %10s ", pPlayer4->getName());
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "entered the room.\r\n");

	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "\r\n\r\n  >>>> ");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLUE, "Press any key to enter the game room");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, " <<<<\r\n\r\n");
	g_Poker.draw_pause();

	while (g_Poker.isGameBegin())
	{
		g_Poker.DoUpdate();
		g_Ansi.cls();
		g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
		g_Poker.draw_all();
		g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 23);
	}

	return 0;
}
