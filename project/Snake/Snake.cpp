/**
 * # Snake
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


#include "snake.h"

#define	PROGRAM_NAME	"SNAKE"
#define PROGRAM_VER		"Ver, 1.0"
#define PROGRAM_URL		"https://www.githum.com/darcy95/games-ascii"

#define OFFSET_GAME_X	1
#define OFFSET_GAME_Y	3

JHAnsi		g_Ansi;
JHSnake		g_Snake;

static void draw_title();
static void draw_frame();
static void draw_select_speed();
static void draw_select_maze();
void draw_board();
void draw_score();
void draw_Food();
void draw_Special();
void draw_all();
void draw_result();

int main(int argc, char *argv[])
{
	int nKey;
	int nSpeed = -1;
	int nMaze = -1;	
	bool bCorrect;
	char cKey;

	do
	{
		bCorrect = true;
		g_Ansi.cls();
		g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
		draw_title();
		draw_select_speed();
		cKey = getchar();
		
		switch (cKey)
		{
			case '1': nSpeed = 1; break;
			case '2': nSpeed = 2; break;
			case '3': nSpeed = 3; break;
			case '4': nSpeed = 4; break;
			default: bCorrect = false; break;
		}

	}
	while(!bCorrect);

	do
	{
		bCorrect = true;
		g_Ansi.cls();
		g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
		draw_title();
		draw_select_maze();
		cKey = getchar();
		
		switch (cKey)
		{
			case '0': nMaze = 0; break;
			case '1': nMaze = 1; break;
			case '2': nMaze = 2; break;
			case '3': nMaze = 3; break;
			case '4': nMaze = 4; break;
			case '5': nMaze = 5; break;
			case '6': nMaze = 6; break;
			default: bCorrect = false; break;
		}
	}
	while(!bCorrect);

	g_Snake.setSpeed(nSpeed - 1);
	g_Snake.setMaze(nMaze);
	g_Snake.OnStart();

	while (g_Snake.getBegin())
	{		
		nKey = -1;

		g_Snake.OnUpdate();

		draw_all();
				
		nKey = getch();
	
		switch (nKey)
		{
			case '4': g_Snake.turnLeft(); break;
			case '6': g_Snake.turnRight(); break;
			default: continue;
		}
	}

	draw_result();	

	return 0;
}

static void draw_title()
{
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+----------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|                  SNAKE                 |\r\n");
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+----------------------------------------+\r\n");
}

static void draw_frame()
{
	for (int i = 0 ; i < FIELD_SIZE_Y ; i++)
	{
		g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "|                                        |\r\n");
	}
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "+----------------------------------------+\r\n");
}

static void draw_select_speed()
{
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "+----------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "| How fast do you want play?             |\r\n");
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "+----------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLACK,	 ANSI_BLACK, "\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "1) Fast\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "2) Normal\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "3) Slow\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "4) Very Slow\r\n");	
	g_Ansi.drawText(ANSI_BLACK,  ANSI_BLACK, "\r\n");
	g_Ansi.drawText(ANSI_GRAY,	 ANSI_BLACK, "Speed : ");
}

static void draw_select_maze()
{
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "+----------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "| Which maze do you want to play?        |\r\n");
	g_Ansi.drawText(ANSI_LIME,	 ANSI_BLACK, "+----------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLACK,  ANSI_BLACK, "\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "1) BOX\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "2) CORNER\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "3) SPIRAL\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "4) TUNNEL\r\n");	
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "5) BLOCKADE\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "6) TWISTED\r\n");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "0) NONE\r\n");
	g_Ansi.drawText(ANSI_BLACK,  ANSI_BLACK, "\r\n");
	g_Ansi.drawText(ANSI_GRAY,	 ANSI_BLACK, "Maze : ");
}

void draw_board()
{
	int x;
	int y;

	for (y = SCREEN_START_Y ; y <= FIELD_SIZE_Y ; y++)
	{
		for (x = SCREEN_START_X ; x <= FIELD_SIZE_X ; x++)
		{
			if (g_nMaze[g_Snake.getMaze()][y - 1][x - 1] == BLOCK_WALL)
			{
				g_Ansi.setCursor(x + OFFSET_GAME_X, y + OFFSET_GAME_Y);
				g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "#");
			}
		}
	}

	for (y = SCREEN_START_Y ; y <= FIELD_SIZE_Y ; y++)
	{
		for (x = SCREEN_START_X ; x <= FIELD_SIZE_X ; x++)
		{
			g_Ansi.setCursor(x + OFFSET_GAME_X, y + OFFSET_GAME_Y);

			if (g_Snake.m_nSnakeOnField[y - 1][x - 1] == SNAKE_BODY)
			{
				g_Ansi.drawText(ANSI_PURPLE, ANSI_BLACK, "X");
			}
			else if (g_Snake.m_nSnakeOnField[y - 1][x - 1] == SNAKE_HEAD)
			{
				g_Ansi.drawText(ANSI_RED, ANSI_BLACK, "0");
			}
		}
	}
}

void draw_score()
{
	g_Ansi.setCursor(SCREEN_START_X + OFFSET_GAME_X + 42, SCREEN_START_Y + OFFSET_GAME_Y + 1);	
	g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, "Score : ");
	g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, g_Snake.getScore() * 100);
}

void draw_Food()
{
	SNAKE_POINT spFood;
	spFood = g_Snake.getFood();

	g_Ansi.setCursor(SCREEN_START_X + spFood.x + OFFSET_GAME_X, SCREEN_START_Y + spFood.y + OFFSET_GAME_Y);
	g_Ansi.drawText(ANSI_BROWN, ANSI_BLACK, "*");
}

void draw_Special()
{
	if (g_Snake.getSpecial())
	{
		SNAKE_POINT spSpecial;
		spSpecial = g_Snake.getSpecialPos();

		g_Ansi.setCursor(SCREEN_START_X + spSpecial.x + OFFSET_GAME_X, SCREEN_START_Y + spSpecial.y + OFFSET_GAME_Y);
		g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, "&");
	}
}

void draw_all()
{
	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);
	draw_title();
	draw_frame();
	draw_board();
	draw_Food();
	draw_Special();
	draw_score();
}

void draw_result()
{
	char* pSpeed;

	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);

	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "|                    GAME OVER                    |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Your Score :                                   |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Food(s) :                                      |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Speed of this game :                           |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X + 30, SCREEN_START_Y + 3);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, g_Snake.getScore() * 100);

	g_Ansi.setCursor(SCREEN_START_X + 30, SCREEN_START_Y + 4);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, g_Snake.getFoods());

	g_Ansi.setCursor(SCREEN_START_X + 30, SCREEN_START_Y + 5);
	
	switch(g_Snake.getSpeed())
	{
		case 0:	strcpy(pSpeed, "Fast"); break;
		case 1:	strcpy(pSpeed, "Normal"); break;
		case 2:	strcpy(pSpeed, "Slow"); break;
		case 3:	strcpy(pSpeed, "Very slow"); break;
	}

	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, pSpeed);

	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 8);
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, PROGRAM_NAME " " PROGRAM_VER "\r\n");
	g_Ansi.drawText(ANSI_BROWN,  ANSI_BLACK, "PROJECT URL : " PROGRAM_URL "\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 12);
}
