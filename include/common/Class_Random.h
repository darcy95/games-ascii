/* =====================================================================================
 *	JHRandom Ver, 1.0
 * 
 */

#ifndef _JHRANDOM_C_
#define _JHRANDOM_C_

//--------------------------------------------------------------------------------------//

class JHRandom
{
public:
	JHRandom(unsigned long nSeed = (unsigned)time(NULL));
	virtual ~JHRandom();

public:
	void	Shuffle(int* pCardBox, int nArrayNum);
	void	Seed(unsigned long nSeed = (unsigned)time(NULL));
	int		Random();										
	int		Random(int nStartNum, int nRange);				
	int		Random(int nRange);								

private:
	static	BOOL		ms_bGlobalSeed;
	static	int			ms_nShuffleCount;
};

//--------------------------------------------------------------------------------------//

BOOL	JHRandom::ms_bGlobalSeed = false;
int		JHRandom::ms_nShuffleCount = 2;

JHRandom::JHRandom(unsigned long nSeed)
{
	Seed(nSeed);
}

JHRandom::~JHRandom()
{

}

void JHRandom::Seed(unsigned long nSeed)
{
	if (ms_bGlobalSeed == false)
	{
		::srand(nSeed);
		ms_bGlobalSeed = true;
	}
}

int JHRandom::Random()
{
	return ::rand();
}

int JHRandom::Random(int nStartNum, int nRange)
{
	return nStartNum + (Random() % nRange);
}

int JHRandom::Random(int nRange)
{
	return Random(0, nRange);
}

void JHRandom::Shuffle(int* pCardBox, int nArrayNum)
{
	int		i;
	int		j;
	int		nRandom;
	int		nTemp;

	for (i = 0 ; i < ms_nShuffleCount ; i++)
	{
		for (j = 0 ; j < nArrayNum ; j++)
		{
			nRandom = Random() % nArrayNum;

			if (j != nRandom)
			{
				nTemp				= pCardBox[nRandom];
				pCardBox[nRandom]	= pCardBox[j];
				pCardBox[j]			= nTemp;
			}
		}
	}
}

//--------------------------------------------------------------------------------------//

#endif
