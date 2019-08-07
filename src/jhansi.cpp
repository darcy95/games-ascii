/** 
 * # JHAnsi Ver, 1.0
 * 
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#include "jhansi.h"

JHAnsi::JHAnsi()
{

}

JHAnsi::~JHAnsi()
{

}

void JHAnsi::drawText(int nColor, int nBackColor, const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	printf("\033[4%d;3%dm", nBackColor, nColor);
	vprintf(fmt, vl);
	printf("\033[0m");

	va_end(vl);
}

