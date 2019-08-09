#ifndef _JHSTD_C_
#define _JHSTD_C_

#define TRUE      1
#define FALSE     0
#define ASSERT(x) assert(x)

// POINT
struct POINT
{
    int x;
    int y;
};

typedef unsigned char   BYTE;  // 0 ~ 255
typedef unsigned short  WORD;  // 0 ~ 65535
typedef unsigned long   DWORD;
typedef unsigned int    UINT;
typedef long            LONG;
typedef int             BOOL;

//--------------------------------------------------------------------------------------//

#endif
