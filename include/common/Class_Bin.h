/**
 * # JHBin Ver, 0.1
 * 
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#ifndef _JHBIN_C_
#define _JHBIN_C_

#define BITS_OF_INT		(sizeof(int) * 8)
#define BITS_OF_SHORT	(sizeof(short int) * 8)
#define BITS_OF_CHAR	(sizeof(char) * 8)

#define UPPER	1	
#define LOWER	0	

//--------------------------------------------------------------------------------------//

class JHBin
{
	public:
		JHBin();
		virtual ~JHBin();

	public:
		void		printbits(char);
		char		printbit(char, char);
		char		setBit(char, char);
		bool		isSet(char, char);
		char		resetBit(char, char);
		bool		isReset(char, char);
		char		toggle(char, char);
		char		toggle(char);
		void		asArray(char, char*);
		char		setAll(char);
		char		resetAll(char);

		void		printbits(short int);
		char		printbit(short int, char);
		short int	setBit(short int, char);
		bool		isSet(short int, char);
		short int	resetBit(short int, char);
		bool		isReset(short int, char);
		short int	toggle(short int, char);
		short int	toggle(short int);
		void		asArray(short int, char*);
		short int	setAll(short int);
		short int	resetAll(short int);
		
		void		printbits(int);
		char		printbit(int, char);
		int			setBit(int, char);
		bool		isSet(int, char);
		int			resetBit(int, char);
		bool		isReset(int, char);
		int			toggle(int, char);
		int			toggle(int);
		void		asArray(int, char*);
		int			setAll(int);
		int			resetAll(int);

		char		getChar(int, char);						// Get kth char(8-bits) out of int(32-bits)
		char		getChar(short int, char);				// Get kth char(8-bits) out of short int(16-bits)
		short int	getShort(int, char);					// Get kth short int (16-bit) out of int(32-bits)
		short int	combineChars(char, char);				// Combine 2 chars (Upperbyte and Lowerbyte)
		int			combineShorts(short int, short int);	// Combine 2 ints (Upperword and Lowerword)
};

//--------------------------------------------------------------------------------------//
//
//                                               9 8 7 6 5 4 3 2 1 0    DEC
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0| = 0
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1| = 1
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0| = 2
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0| = 4
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0| = 8
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0| = 16
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0| = 32
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0|0| = 64
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0|0|0| = 128
//	+---------------------------------------------------------------+
//
//	Set
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0|0|0|0| = 256
//	+---------------------------------------------------------------+
//	
//	Set 4th bit                                            V
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|1|0|0|0|0| = 272
//	+---------------------------------------------------------------+
//	
//	Set 6th and 14th bits              V               V
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|0|0|0|0|1|0|1|0|1|0|0|0|0| = 16720
//	+---------------------------------------------------------------+
//	
//	Reset 14th bits                    V
//	+---------------------------------------------------------------+
//	|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|1|0|1|0|1|0|0|0|0| = 336
//	+---------------------------------------------------------------+
//	
//	toggle(336)
//	+---------------------------------------------------------------+
//	|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|1|0|1|0|1|1|1|1| = -337
//	+---------------------------------------------------------------+
//	
//	getChar(-337, 3) = -1	getChar(-337, 2) = -1	getChar(-337, 1) = -2	getChar(-337, 0) = -81
//	+---------------+		+---------------+		+---------------+		+---------------+
//	|1|1|1|1|1|1|1|1|		|1|1|1|1|1|1|1|1|		|1|1|1|1|1|1|1|0|		|1|0|1|0|1|1|1|1|	
//	+---------------+		+---------------+		+---------------+		+---------------+	
//	
//	getShort(-337, 1) = -1				getShort(-337, 0) = -377
//	+-------------------------------+	+-------------------------------+
//	|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|	|1|1|1|1|1|1|1|0|1|0|1|0|1|1|1|1|	
//	+-------------------------------+	+-------------------------------+	
//	
//	combineChars(-1, -1) = -1			combineChars(-2, -81) = -377
//	+-------------------------------+	+-------------------------------+
//	|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|	|1|1|1|1|1|1|1|0|1|0|1|0|1|1|1|1|	
//	+-------------------------------+	+-------------------------------+	
//	
//	combineShorts(-1, -377) = -377
//	+---------------------------------------------------------------+
//	|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|1|0|1|0|1|1|1|1|	
//	+---------------------------------------------------------------+	
//
//--------------------------------------------------------------------------------------//	

JHBin::JHBin()
{

}

JHBin::~JHBin()
{

}

void JHBin::printbits(char nValue)
{
	int i, j;

	for (i = (BITS_OF_INT / 4) - 1, j = 1 ; i >= 0 ; i--, j++) 
	{ 
		printf("%d", printbit(nValue, i)); 
	} 
}

void JHBin::printbits(short int nValue)
{
	for (int i = 1 ; i >= 0 ; i--)
	{
		printbits(getChar(nValue, i));
		printf(" ");
	}
}

void JHBin::printbits(int nValue)
{ 
	for (int i = 1 ; i >= 0 ; i--)
	{
		printbits(getShort(nValue, i));
	}
} 

char JHBin::printbit(char nValue, char nBit)
{
	return (nValue >> nBit) & 0x01;
}

char JHBin::printbit(short int nValue, char nBit)
{
	return (nValue >> nBit) & 0x01;
}

char JHBin::printbit(int nValue, char nBit)
{
	return (nValue >> nBit) & 0x01;
}

char JHBin::setBit(char nValue, char nBit)
{
	return nValue |= (1 << nBit);
}

short int JHBin::setBit(short int nValue, char nBit)
{
	return nValue |= (1 << nBit);
}

int JHBin::setBit(int nValue, char nBit)
{
	return nValue |= (1 << nBit);
}

bool JHBin::isSet(char nValue, char nBit)
{
	return nValue & (1 << nBit);
}

bool JHBin::isSet(short int nValue, char nBit)
{
	return nValue & (1 << nBit);
}

bool JHBin::isSet(int nValue, char nBit)
{
	return nValue & (1 << nBit);
}

char JHBin::resetBit(char nValue, char nBit)
{
	return nValue &= ~(1 << nBit);
}

short int JHBin::resetBit(short int nValue, char nBit)
{
	return nValue &= ~(1 << nBit);
}

int JHBin::resetBit(int nValue, char nBit)
{
	return nValue &= ~(1 << nBit);
}

bool JHBin::isReset(char nValue, char nBit)
{
	return !isSet(nValue, nBit);
}

bool JHBin::isReset(short int nValue, char nBit)
{
	return !isSet(nValue, nBit);
}

bool JHBin::isReset(int nValue, char nBit)
{
	return !isSet(nValue, nBit);
}

char JHBin::setAll(char)
{
	return -1;
}

short int JHBin::setAll(short int)
{
	return -1;
}

int JHBin::setAll(int)
{
	return -1;
}

char JHBin::resetAll(char)
{
	return 0;
}

short int JHBin::resetAll(short)
{
	return 0;
}

int JHBin::resetAll(int)
{
	return 0;
}

char JHBin::toggle(char nValue, char nBit)
{
	return nValue ^= (1 << nBit);
}

short int JHBin::toggle(short int nValue, char nBit)
{
	return nValue ^= (1 << nBit);
}

int JHBin::toggle(int nValue, char nBit)
{
	return nValue ^= (1 << nBit);
}

char JHBin::toggle(char nValue)
{
	return nValue = -(nValue + 1);
}

short int JHBin::toggle(short int nValue)
{
	return nValue = -(nValue + 1);
}

int JHBin::toggle(int nValue)
{
	return nValue = -(nValue + 1);
}

void JHBin::asArray(char nValue, char* pBits)
{
	char cBits[BITS_OF_CHAR];

	int i;

	for (i = BITS_OF_CHAR - 1 ; i >= 0 ; i--)
	{
		cBits[i] = printbit(nValue, i);
	}

	memcpy(pBits, cBits, sizeof(cBits));
}

void JHBin::asArray(short int nValue, char* pBits)
{
	char cBits[BITS_OF_SHORT];

	int i;

	for (i = BITS_OF_SHORT - 1 ; i >= 0 ; i--)
	{
		cBits[i] = printbit(nValue, i);
	}

	memcpy(pBits, cBits, sizeof(cBits));
}

void JHBin::asArray(int nValue, char* pBits)
{
	char cBits[BITS_OF_INT];

	int i;

	for (i = BITS_OF_INT - 1 ; i >= 0 ; i--)
	{
		cBits[i] = printbit(nValue, i);
	}

	memcpy(pBits, cBits, sizeof(cBits));
}

char JHBin::getChar(int nValue, char k)
{
	int i = 0;
	int newValue = resetAll(nValue);

	for (i = 0 ; i < BITS_OF_CHAR ; i++)
	{
		newValue = isSet(nValue, (k * BITS_OF_CHAR) + i) ? setBit(newValue, i) : resetBit(newValue, i);
	}

	return (char) newValue;
}

char JHBin::getChar(short int nValue, char k)
{
	int i = 0;
	int newValue = resetAll(nValue);

	for (i = 0 ; i < BITS_OF_CHAR ; i++)
	{
		newValue = isSet(nValue, (k * BITS_OF_CHAR) + i) ? setBit(newValue, i) : resetBit(newValue, i);
	}

	return (char) newValue;
}

short int JHBin::getShort(int nValue, char k)
{
	int i = 0;
	int newValue = resetAll(nValue);

	for (i = 0 ; i < BITS_OF_SHORT ; i++)
	{
		newValue = isSet(nValue, (k * BITS_OF_SHORT) + i) ? setBit(newValue, i) : resetBit(newValue, i);
	}

	return (short int) newValue;
}

short int JHBin::combineChars(char nUpper, char nLower)
{
	int newValue = resetAll((int) 0);

	for (int i = 0 ; i < BITS_OF_CHAR ; i++)
	{
		newValue = isSet((int) nLower, i) ? setBit(newValue, i) : resetBit(newValue, i);
	}

	for (int i = 0 ; i < BITS_OF_CHAR ; i++)
	{
		newValue = isSet((int) nUpper, i) ? setBit(newValue, BITS_OF_CHAR + i) : resetBit(newValue, BITS_OF_CHAR + i);
	}

	return (short int) newValue;
}

int JHBin::combineShorts(short int nUpper, short int nLower)
{
	int newValue = resetAll((int) 0);

	for (int i = 0 ; i < BITS_OF_SHORT ; i++)
	{
		newValue = isSet((int) nLower, i) ? setBit(newValue, i) : resetBit(newValue, i);
	}

	for (int i = 0 ; i < BITS_OF_SHORT ; i++)
	{
		newValue = isSet((int) nUpper, i) ? setBit(newValue, BITS_OF_SHORT + i) : resetBit(newValue, BITS_OF_SHORT + i);
	}

	return newValue;
}

//--------------------------------------------------------------------------------------//

#endif
