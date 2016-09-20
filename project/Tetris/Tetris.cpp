#include "common/StdAfx.h"
#include "common/Class_Tetris.h"
#include "common/Class_Ansi.h"
#include "common/Func_Inputk.h"
#include "Class_TetrisExt.h"

#define	PROGRAM_NAME	"TETRIS"
#define PROGRAM_VER		"Ver, 1.0"
#define PROGRAM_URL		"https://www.github.com/darcy95/games-ascii"

JHAnsi		g_Ansi;
JHTetrisExt	g_Tetris;

static void draw_title();
static void draw_frame();
void draw_board();
void draw_block();
void draw_score();
void draw_next();
void draw_all();
void draw_result();

int main(int argc, char *argv[])
{
	int nKey;
	g_Tetris.OnStart();
	g_Tetris.m_nMovePoint = 10;

	while (g_Tetris.m_bGameBegin)
	{		
		nKey = -1;

		g_Tetris.OnUpdate();

		draw_all();
				
		nKey = getch();
	
		switch (nKey)
		{
			case '4': g_Tetris.OnLeft();	break;
			case '5': g_Tetris.OnDown();	break;
			case '6': g_Tetris.OnRight();	break;
			case '8': g_Tetris.OnRotate();	break;
		}
	}

	draw_result();	

	return 0;
}

static void draw_title()
{
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLUE, "+----------+\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLUE, "|  TETRIS  |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLUE, "+----------+\r\n");
}

static void draw_frame()
{
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|          |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+----------+\r\n");
}

void draw_board()
{
	for (int i = 0 ; i < TOTAL_BRICK_NUM_X ; i++)
	{
		for (int j = 0 ; j < TOTAL_BRICK_NUM_Y ; j++)
		{
			g_Ansi.setCursor(i + 2, j + 4);

			if (g_Tetris.m_BrkBoard[i][j].nFill == BRICK_FILLED)
			{
				g_Ansi.drawText(g_Tetris.m_BrkBoard[i][j].nColor, ANSI_BLACK, BRICK_SYMBOL);
			}
		}
	}
}

void draw_block()
{
	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{	
			g_Ansi.setCursor(i + g_Tetris.m_nPosX + 2, j + g_Tetris.m_nPosY + 4);

			if (g_Tetris.m_BrkCurr[i][j].nFill == BRICK_FILLED)
			{
				if (g_Tetris.OnCheckValidArea(g_Tetris.m_nPosX + i, g_Tetris.m_nPosY + j))
				{
					g_Ansi.drawText(g_Tetris.m_BrkCurr[i][j].nColor, ANSI_BLACK, BRICK_SYMBOL);
				}
			}
		}
	}
}

void draw_score()
{
	g_Ansi.setCursor(15, 4);
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Score\t");
	g_Ansi.drawText(ANSI_BLUE,  ANSI_LTBLUE, (int) g_Tetris.m_nScore * 100);

	g_Ansi.setCursor(15, 5);
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Line(s)\t");
	g_Ansi.drawText(ANSI_BLUE,  ANSI_LTBLUE, (int) g_Tetris.m_nLine);

	g_Ansi.setCursor(15, 6);
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Speed\t");
	g_Ansi.drawText(ANSI_BLUE,  ANSI_LTBLUE, (int) g_Tetris.m_nMovePoint);
}

void draw_next()
{
	g_Ansi.setCursor(15, 8);
	g_Ansi.drawText(ANSI_PURPLE, ANSI_BLUE, "::NEXT::");

	for (int i = 0 ; i < BLOCK_WIDTH ; i++)
	{
		for (int j = 0 ; j < BLOCK_HEIGHT ; j++)
		{	
			if (g_Tetris.m_BrkNext[i][j].nFill == BRICK_FILLED)
			{
				g_Ansi.setCursor(17 + i, 9 + j);
				g_Ansi.drawText(g_Tetris.m_BrkNext[i][j].nColor, ANSI_BLACK, BRICK_SYMBOL);
			}
		}
	}
}

void draw_all()
{
	g_Ansi.cls();
	g_Ansi.setCursor(0, 0);
	draw_title();
	draw_frame();
	draw_block();
	draw_score();
	draw_next();
	draw_board();
	g_Ansi.setCursor(0, 24);
}

void draw_result()
{
	g_Ansi.cls();
	g_Ansi.setCursor(0, 0);

	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "|                  GAME OVER                      |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Your Score :                                   |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Completed Line(s) :                            |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Speed at the last moment :                     |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n\r\n");
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, PROGRAM_NAME " " PROGRAM_VER "\r\n");
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, "PROJECT URL : " PROGRAM_URL);

	g_Ansi.setCursor(35, 4);
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, (int) g_Tetris.m_nScore * 100);
	g_Ansi.setCursor(35, 5);
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, (int) g_Tetris.m_nLine);
	g_Ansi.setCursor(35, 6);
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, (int) g_Tetris.m_nMovePoint);
	g_Ansi.setCursor(0, 15);
}
