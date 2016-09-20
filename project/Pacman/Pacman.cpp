#include "common/StdAfx.h"
#include "common/Class_AStar.h"
#include "common/Class_Pacman.h"
#include "common/Class_Ansi.h"
#include "common/Func_Inputk.h"

#define	PROGRAM_NAME	"PACMAN"
#define PROGRAM_VER		"Ver, 1.0"
#define PROGRAM_URL		"https://www.github.com/darcy95/games-ascii"

JHAnsi		g_Ansi;
JHPacman	g_Pacman;

static void draw_all();
static void draw_maze();
static void draw_pacman();
static void draw_ghosts();
static void draw_title();
static void draw_score();
static void draw_life();
static void draw_statge();
static void draw_result();

int main(int argc, char *argv[])
{
	int iInput;
	int iRedrawInterval = PACMAN_INIT_MOVE;
	
	g_Pacman.OnInit();

	while (g_Pacman.getGameRun())
	{
		g_Pacman.OnUpdate();

		if (iRedrawInterval <= 0)
		{
			draw_all();
			iRedrawInterval = PACMAN_INIT_MOVE;
		}
		else
		{
			iRedrawInterval--;
		}

		iInput = -1;
		iInput = getch();

		switch (iInput)
		{
			case '8': g_Pacman.turnDirection(PACMAN_DIR_NORTH);	break;
			case '6': g_Pacman.turnDirection(PACMAN_DIR_EAST);	break;
			case '5': g_Pacman.turnDirection(PACMAN_DIR_SOUTH);	break;
			case '4': g_Pacman.turnDirection(PACMAN_DIR_WEST);	break;
		}
	}

	draw_result();
	
	g_Pacman.OnExit();

	return 0;
}

static void draw_all()
{
	draw_maze();
	draw_ghosts();
	draw_pacman();
	draw_title();
	draw_score();
	draw_life();
	draw_statge();	
	g_Ansi.setCursor(1, 22);	
}

static void draw_maze()
{
	g_Ansi.cls();
	g_Ansi.setCursor(1, 1);

	for (int i = 0 ; i < PACMAN_MAZE_HEIGHT ; i++)
	{
		for (int j = 0 ; j < PACMAN_MAZE_WIDTH ; j++)
		{
			switch (g_Pacman.getTile(j, i))
			{
				case PACMAN_BLOCK_WALL:  	
					g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "[]");
					break;
					
				case PACMAN_BLOCK_DOOR:
					g_Ansi.drawText(ANSI_LTBLUE, ANSI_BLACK, "--"); 
					break;
					
				case PACMAN_BLOCK_FOOD:	 
					g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, " .");
					break;
					
				case PACMAN_BLOCK_SUPER: 
					g_Ansi.drawText(ANSI_GRAY, ANSI_BLACK, " +");
					break;
					
				case PACMAN_BLOCK_FRUIT: 
					g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " &");
					break;
					
				default: 
					g_Ansi.drawText(ANSI_BLACK, ANSI_BLACK, "  ");
					break;
			}
		}

		printf("\n");
	}
}

static void draw_pacman()
{
	g_Ansi.setCursor(g_Pacman.getPacmanPosX() * 2 + 1, g_Pacman.getPacmanPosY() + 1); 

	if (g_Pacman.getPacmanSuper())
	{
		g_Ansi.drawText(ANSI_LIME, ANSI_BLACK, " 0");
	}
	else
	{
		g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, " 0");	
	}
}

static void draw_ghosts()
{
	for (int i = 0 ; i < PACMAN_GHOST_NUM ; i++)
	{
		g_Ansi.setCursor(g_Pacman.getGhostPosX(i) * 2 + 1, g_Pacman.getGhostPosY(i) + 1); 
		if (g_Pacman.getGhostStatus(i))
		{
			g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, " X");	
		}
		else
		{
			g_Ansi.drawText(ANSI_RED, ANSI_BLACK, "..");	
		}
	}
}

static void draw_title()
{
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 1);
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "+--------------+");
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 2);	
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "|    PACMAN    |");
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 3);	
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "+--------------+");
}

static void draw_score()
{
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 5);	
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Score : %d", g_Pacman.getScore() * 10);
}

static void draw_life()
{
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 6);	
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Life : ");
	
	for (int i = 0 ; i < g_Pacman.getLife() ; i++)
	{
		g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, " O");		
	}
}

static void draw_statge()
{
	g_Ansi.setCursor(PACMAN_MAZE_WIDTH * 2 + 3, 7);	
	g_Ansi.drawText(ANSI_WHITE, ANSI_BLACK, "Stage : %d", g_Pacman.getStage());
}

static void draw_result()
{
	g_Ansi.cls();
	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y);

	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_BLUE, ANSI_GRAY, "|                    GAME OVER                    |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Your Score :                                   |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "|  Stage :                                        |\r\n");
	g_Ansi.drawText(ANSI_RED,  ANSI_GRAY, "+-------------------------------------------------+\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X + 30, SCREEN_START_Y + 3);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, "%d", g_Pacman.getScore() * 10);

	g_Ansi.setCursor(SCREEN_START_X + 30, SCREEN_START_Y + 4);
	g_Ansi.drawText(ANSI_BLUE,  ANSI_GRAY, "%d", g_Pacman.getStage());

	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 8);
	g_Ansi.drawText(ANSI_WHITE,  ANSI_BLACK, PROGRAM_NAME " " PROGRAM_VER "\r\n");
	g_Ansi.drawText(ANSI_WHITE,  ANSI_BLACK, "PROJECT URL : " PROGRAM_URL "\r\n\r\n");

	g_Ansi.setCursor(SCREEN_START_X, SCREEN_START_Y + 12);
}
