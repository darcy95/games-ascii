#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>

int getch(void);
int kbhit(void);

/*
 * CCHAR was changed from CMIN (it's already defined in termios.h)
 */

#define CCHAR 0

#ifdef CTIME
#undef CTIME
#endif

#ifdef CTIMEDEF
	#define CTIME CTIMEDEF
#else
	#define CTIME 1
#endif


/*
 *  kbhit()  --  a keyboard lookahead monitor
 *
 *  returns the number of characters available to read.
 */
int kbhit(void)
{
	int   cnt = 0;
	int   error;
	static struct termios Otty, Ntty;

	tcgetattr(0, &Otty);
	Ntty = Otty;

	Ntty.c_iflag		= 0;		/* input mode						*/
	Ntty.c_oflag		= 0;		/* output mode						*/
	Ntty.c_lflag        &= ~ICANON; /* raw mode							*/
	Ntty.c_cc[VMIN]		= CCHAR;	/* minimum characters to wait for	*/
	Ntty.c_cc[VTIME]	= CTIME;	/* minimum time to wait				*/

	if (0 == (error = tcsetattr(0, TCSANOW, &Ntty))) 
	{
		struct timeval tv;
		error += ioctl(0, FIONREAD, &cnt);
		error += tcsetattr(0, TCSANOW, &Otty);
		tv.tv_sec  = 0;
		tv.tv_usec = 100;			/* insert a minimal delay */
		select(1, NULL, NULL, NULL, &tv);
	}

	return (error == 0 ? cnt : -1);
}

/*
 *  getch()  --  a blocking single character input from stdin
 *
 *  Returns a character, or -1 if an input error occurs.
 *
 *
 *  Conditionals allow compiling with or without echoing of
 *  the input characters, and with or without flushing pre-existing
 *  existing  buffered input before blocking.
 *
 */
int getch(void)
{
	char   ch;
	int   error;
	static struct termios Otty, Ntty;

	fflush(stdout);
	tcgetattr(0, &Otty);
	Ntty = Otty;

	Ntty.c_iflag  =  0;			/* input mode	 */
	Ntty.c_oflag  =  0;			/* output mode	 */
	Ntty.c_lflag &= ~ICANON;	/* line settings */

#if 1
	/* disable echoing the char as it is typed	 */
	Ntty.c_lflag &= ~ECHO;		/* disable echo  */
#else
	/* enable echoing the char as it is typed	 */
	Ntty.c_lflag |=  ECHO;		/* enable echo   */
#endif
	Ntty.c_cc[VMIN]  = CCHAR;	/* minimum chars to wait for */
	Ntty.c_cc[VTIME] = CTIME;	/* minimum time to wait		 */

#if 1
/*
 * use this to flush the input buffer before blocking for new input
 */
#define FLAG TCSAFLUSH
#else
/*
 * use this to return a char from the current input buffer, or block if no input is waiting.
 */
#define FLAG TCSANOW

#endif

	if (0 == (error = tcsetattr(0, FLAG, &Ntty))) 
	{
		error  = read(0, &ch, 1 );				/* get char from stdin	*/
		error += tcsetattr(0, FLAG, &Otty);		/* restore old settings */
	}

	return (error == 1 ? (int) ch : -1 );
}

void scanff() 
{ 
	int c;

	do 
	{
		c = getchar();
	}
	while (c != '\n' && c != EOF); 
} 
