/** 
 * # JHAnsi Ver, 1.0
 * 
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#ifndef _JHANSI_C_
#define _JHANSI_C_

#include "jhstd.h"
#include <stdarg.h>

//--------------------------------------------------------------------------------------//

#define SCREEN_START_X 1	//	Note, that point of screen start with 1, not 0
#define SCREEN_START_Y 1	//	So, starting point is actually (1, 1)

enum ANSICOLOR	
{
	ANSI_BLACK	= 0, 
	ANSI_RED	= 1, 
	ANSI_LIME	= 2, 
	ANSI_BROWN	= 3, 
	ANSI_BLUE	= 4, 
	ANSI_PURPLE	= 5, 
	ANSI_LTBLUE	= 6, 
	ANSI_GRAY	= 7, 
	ANSI_WHITE	= 8
};

class JHAnsi
{
	public:
		JHAnsi();
		virtual ~JHAnsi();

	public:
		void cls()												{ printf("\033[2J"); };
		void setCursor(int nX, int nY)							{ printf("\033[%d;%dH", nY, nX); };		
		void remLine(int nLine)									{ printf("\033[%d;%dH\033[K", nLine, 1); };
		void hideCursor()										{ printf("\033[30;40m\033[2J\033[37m"); };
		void drawText(int nColor, int nBackColor, char* pText)	{ printf("\033[4%d;3%dm%s\033[0m", nBackColor, nColor, pText); };
		void drawText(int nColor, int nBackColor, char szText)	{ printf("\033[4%d;3%dm%c\033[0m", nBackColor, nColor, szText); };
		void drawText(int nColor, int nBackColor, int   nNum)	{ printf("\033[4%d;3%dm%d\033[0m", nBackColor, nColor, nNum); };
		void drawText(int nColor, int nBackColor, float fNum)	{ printf("\033[4%d;3%dm%f\033[0m", nBackColor, nColor, fNum); };
		void drawText(int nColor, int nBackColor, const char* fmt, ...);
};

//--------------------------------------------------------------------------------------//

#endif
