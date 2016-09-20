#ifndef _STDAFX_C_
#define _STDAFX_C_

//--/ Including standard C headers /----------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <getopt.h>

//--/ Type definition for the WIN32 compatibility /-------------------------------------//

#include "Struct.h"		//	often used structs

typedef unsigned char	BYTE;		//	0 ~ 255
typedef unsigned short	WORD;		//	0 ~ 65535
typedef unsigned long	DWORD;
typedef unsigned int	UINT;
typedef long			LONG;
typedef int				BOOL;
#define TRUE			1
#define FALSE			0
#define ASSERT(x)		assert(x)

//--------------------------------------------------------------------------------------//

#endif
