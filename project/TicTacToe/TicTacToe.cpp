/**
 * # TicTacToe
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


#include "tictactoe.h"

#define	PROGRAM_NAME	"TicTacToe"
#define PROGRAM_VER	"Ver, 1.0"
#define PROGRAM_URL	"https://www.github.com/darcy95/games-ascii"

#define OFFSET_GAME_X	1
#define OFFSET_GAME_Y	3

#define PLAYER_NUMBER	2
#define CELL_WIDTH		3
#define CELL_HEIGHT		3

JHAnsi			g_Ansi;
JHTicTacToe		g_TicTacToe;

static unsigned short int g_nMark[PLAYER_NUMBER][CELL_WIDTH][CELL_HEIGHT] = 
{
	{
		{1,1,1},
		{1,0,1},
		{1,1,1},
	},
	{
		{1,0,1},
		{0,1,0},
		{1,0,1},
	}
};

static void draw_title();
static void draw_frame();
static void draw_continue();
void draw_board();
void draw_mark(int nPlayer, int nX, int nY);
void draw_score();
void draw_all();
void draw_result();

int main(int argc, char *argv[])
{
	int nKey;

	g_TicTacToe.OnStart();

	while (g_TicTacToe.m_bGameBegin)
	{		
		nKey = -1;

		g_TicTacToe.OnUpdate();

		draw_all();
				
		nKey = getch();
	
		switch (nKey)
		{
			case '1': if (g_TicTacToe.setBoard(6, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '2': if (g_TicTacToe.setBoard(7, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '3': if (g_TicTacToe.setBoard(8, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '4': if (g_TicTacToe.setBoard(3, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '5': if (g_TicTacToe.setBoard(4, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '6': if (g_TicTacToe.setBoard(5, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '7': if (g_TicTacToe.setBoard(0, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '8': if (g_TicTacToe.setBoard(1, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			case '9': if (g_TicTacToe.setBoard(2, PLAYER_O)) g_TicTacToe.chgTurn(); break;
			default: continue;
		}		
	}

	draw_result();	

	return 0;
}

static void draw_title()
{
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "+-----------------------------+\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "|          TIC TAC TOE        |\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "+-----------------------------+\r\n");
}

static void draw_frame()
{
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+---------+---------+---------+\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+---------+---------+---------+\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+---------+---------+---------+\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|         |         |         |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+---------+---------+---------+\r\n");
}

static void draw_continue()
{
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, "One more game?   ");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "Y)");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "es  ");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "N)");
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "o : ");
}

void draw_board()
{
	int i = 0;
	int j = 0;

	for (i = 0 ; i < TICTACTOE_SIZE_X ; i++)
	{
		for (j = 0 ; j < TICTACTOE_SIZE_Y ; j++)
		{
			if (g_TicTacToe.getBoard(j, i) == PLAYER_O)
			{
				draw_mark(PLAYER_O - 1, j, i);
			}
			else if (g_TicTacToe.getBoard(j, i) == PLAYER_X)
			{
				draw_mark(PLAYER_X - 1, j, i);
			}
		}
	}
}

void draw_mark(int nPlayer, int nX, int nY)
{
	int i = 0;
	int j = 0;

	for (i = 0 ; i < CELL_WIDTH ; i++)
	{
		for (j = 0 ; j < CELL_HEIGHT ; j++)
		{
			g_Ansi.setCursor(SCREEN_START_X + 4 + (nX * 10) + j, SCREEN_START_Y + 5 + (nY * 6) + i);

			if (g_nMark[nPlayer][i][j] == 1)
			{
				if (nPlayer == 0)
				{
					g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "#");
				}
				else
				{
					g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, "#");
				}
			}
		}
	}
}

void draw_score()
{
	g_Ansi.setCursor(SCREEN_START_X + 33, SCREEN_START_Y + 5);	
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "WIN  : ");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, g_TicTacToe.getScoreWin());

	g_Ansi.setCursor(SCREEN_START_X + 33, SCREEN_START_Y + 6);	
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "DRAW : ");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, g_TicTacToe.getScoreDraw());

	g_Ansi.setCursor(SCREEN_START_X + 33, SCREEN_START_Y + 7);	
	g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, "LOST : ");
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, g_TicTacToe.getScoreLose());
}

void draw_all()
{
	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
	draw_title();
	draw_frame();
	draw_board();
	draw_score();

	if (g_TicTacToe.getWinner() != PLAYER_NONE)
	{
		bool bCorrect;
		char cKey;

		do
		{
			bCorrect = true;
			g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 22);
			draw_continue();
			cKey = getchar();
			
			switch (cKey)
			{
				case 'Y': case 'y': g_TicTacToe.OnReset(); break;
				case 'N': case 'n': g_TicTacToe.m_bGameBegin = false; break;
				default: bCorrect = false; break;
			}
		}
		while(!bCorrect);
	}
}

void draw_result()
{
	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);

	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "|                    GAME OVER                    |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  WIN  :                                         |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  DRAW :                                         |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  LOST :                                         |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X + 10, SCREEN_START_Y + 3);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, g_TicTacToe.getScoreWin());

	g_Ansi.setCursor(SCREEN_START_X + 10, SCREEN_START_Y + 4);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, g_TicTacToe.getScoreDraw());

	g_Ansi.setCursor(SCREEN_START_X + 10, SCREEN_START_Y + 5);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, g_TicTacToe.getScoreLose());
	
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 8);
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, PROGRAM_NAME " " PROGRAM_VER "\r\n");
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, "PROJECT URL : " PROGRAM_URL "\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 12);
}
