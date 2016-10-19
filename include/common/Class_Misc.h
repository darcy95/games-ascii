/**
 * # JHMisc Ver, 0.1
 *
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#ifndef _JHMISC_C_
#define _JHMISC_C_

//--------------------------------------------------------------------------------------//

class JHMisc
{
	public:
		JHMisc();
		virtual ~JHMisc();

	public:
		int		StringReplace(char* szSrc, char* szFrom, char* szTo);
};

//--------------------------------------------------------------------------------------//
																							
JHMisc::JHMisc()
{

}

JHMisc::~JHMisc()
{

}

int JHMisc::StringReplace(char* szSrc, char* szFrom, char* szTo)
{
    int nSrc	= strlen(szSrc);
    int nTo		= strlen(szTo);
	int nFrom	= strlen(szFrom);

	char* szTemp = NULL;

	int nCount	= 0;
	int nFind	= 0;

	while ((szTemp = strstr(szSrc, szFrom)) != NULL)
    {
		nFind = szTemp - szSrc;
		memmove(&szSrc[nFind + nTo], &szSrc[nFind + nFrom], nSrc - (nFind + nFrom));
		nSrc = nSrc + (nTo - nFrom);
		szSrc[nSrc] = '\0';
		memcpy(&szSrc[nFind], szTo, nTo);
		nCount++;
    }

    return nCount;
}

//--------------------------------------------------------------------------------------//

#endif
