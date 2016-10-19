/**
 * # JHFileIO Ver, 0.1
 *
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 * 
 *	       open  stream for truncate create starting                            
 *	mode   read    write    file     file   position                            
 *	----   ----    -----    ----     ----   --------                            
 *	"r"     y        n       n        n     beginning 	   O_READONLY_NOCREATE	
 *	"r+"    y        y       n        n     beginning 	   O_READWRITE_NOCREATE	
 *	"w"     n        y       y        y     beginning 	   O_WRITEONLY_CREATE_TR
 *	"w+"    y        y       y        y     beginning 	   O_READWRITE_CREATE_TR
 *	"a"     n        y       n        y     end-of-file    O_WRITEONLY_CREATE	
 *	"a+"    y        y       n        y     end-of-file	   O_READWRITE_CREATE	
 *
 */

#ifndef _JHFILEIO_C_
#define _JHFILEIO_C_

//--------------------------------------------------------------------------------------//

#define O_READONLY_NOCREATE			0		//	r		
#define O_READWRITE_NOCREATE		1		//	r+
#define O_WRITEONLY_CREATE_TR		2		//	w
#define O_READWRITE_CREATE_TR		3		//	w+
#define O_WRITEONLY_CREATE			4		//	a
#define O_READWRITE_CREATE			5		//	a+

class JHFileIO
{
	public:
		JHFileIO();
		virtual ~JHFileIO();

	public:
		bool FileOpen(char* szFile, int nFlag = O_READWRITE_CREATE);
		bool CheckStream(FILE* Stream);
		bool FileReadAll(char* szBuff);
		int  FileReadLine(char* szBuff);
		bool FileReadAmount(char* szBuff, int nSize);
		bool FileClose();
		bool FileWrite(char* szData, int nSize);
		bool FileSeek(int nPos, int nWhence);
		void Rewind();
		int	 GetFileSize();
		int  GetPosition();

	public:
		FILE*	m_fStream;
		int		m_nOneCharBuff;
};

//--------------------------------------------------------------------------------------//

JHFileIO::JHFileIO()
{
	m_fStream = NULL;
}

JHFileIO::~JHFileIO()
{

}

bool JHFileIO::FileOpen(char* szFile, int nFlag)
{
	char szFlag[4];

	switch (nFlag)
	{
		case O_READONLY_NOCREATE:
		{
			strcpy(szFlag, "r");
		}
		break;

		case O_READWRITE_NOCREATE:
		{
			strcpy(szFlag, "r+");
		}
		break;

		case O_WRITEONLY_CREATE_TR:
		{
			strcpy(szFlag, "w");
		}
		break;

		case O_READWRITE_CREATE_TR:
		{
			strcpy(szFlag, "w+");
		}
		break;

		case O_WRITEONLY_CREATE:
		{
			strcpy(szFlag, "a");
		}
		break;

		case O_READWRITE_CREATE:
		{
			strcpy(szFlag, "a+");
		}
		break;
	}

	m_fStream = fopen(szFile, szFlag);

	return CheckStream(m_fStream);
}

bool JHFileIO::CheckStream(FILE* Stream)
{
	if (Stream == (FILE*) 0) 
	{ 
		return false;
	}

	return true;
}

bool JHFileIO::FileReadAll(char* szBuff)
{
	if (fread(szBuff, GetFileSize(), 1, m_fStream) < 1)
	{
		return false;
	}

	return true;
}

int JHFileIO::FileReadLine(char* szBuff)
{
	if (fgets(szBuff, 512, m_fStream) == (char*) 0)
	{
		return false;
	}

	return GetPosition();
}

bool JHFileIO::FileReadAmount(char* szBuff, int nSize)
{
	if (fread(szBuff, nSize, 1, m_fStream) < 1)
	{
		return false;
	}

	return true;
}

bool JHFileIO::FileClose()
{
	fclose(m_fStream);

	return true;
}

bool JHFileIO::FileWrite(char* szData, int nSize)
{
	if (fwrite(szData, nSize, 1, m_fStream) < 1)
	{ 
		return false;	
	} 

	return true;
}

bool JHFileIO::FileSeek(int nPos, int nWhence)
{
	return fseek(m_fStream, nPos, nWhence);
}

void JHFileIO::Rewind()
{
	rewind(m_fStream);
}

int JHFileIO::GetFileSize()
{
	int nPos  = GetPosition();
	int nSize = 0;
	
	FileSeek(0, SEEK_END);
	nSize = ftell(m_fStream);
	FileSeek(nPos, SEEK_SET);

	return nSize;
}

int JHFileIO::GetPosition()
{
	return ftell(m_fStream);
}

//--------------------------------------------------------------------------------------//

#endif
