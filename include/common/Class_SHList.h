/* =====================================================================================
 *	JHList Ver, 0.1
 * 
 *	USAGE :
 *
 *		POINT	P[10];
 *
 *		for (int i  = 0 ; i < 10 ; i++)	
 *		{		
 *			P[i].nX = i;
 *			P[i].nY = i * i;
 *			printf("POINT(%d, %d)\r\n", P[i].nX, P[i].nY);
 *			List.AddTail(&P[i]);
 *		}
 *
 *		SHPOS	pos;										
 *		pos = List.GetHeadPosition();						
 *		POINT*	POI;
 *
 *		while (pos)											
 *		{
 *			POI = (POINT*) List.GetNext(pos);				
 *			printf("POINT(%d, %d)\r\n", POI->nX, POI->nY);
 *		}
 *
 */

#ifndef _SHLIST_C_
#define _SHLIST_C_

//--------------------------------------------------------------------------------------//

class SHLinkList;
class SHListLP;

struct _SHNode
{
	_SHNode*	pNext;				//	Next Node
	_SHNode*	pPrev;				//	Previous Node
	char		Data;				//	Actual Data Point
};

typedef _SHNode* SHPOS;

class SHLinkList
{
	protected:
		struct _SPlex
		{
			_SPlex*		m_pNext;
		};

		int		m_nBlockSize;		//	Memory Block Size
		int		m_nDataSize;		//	Data Size
		int		m_nCount;			//	Data Count

		_SHNode*	m_pNodeHead;	//	Head Node
		_SHNode*	m_pNodeTail;	//	Tail Node
		_SHNode*	m_pNodeFree;	//	Next FreeNode
		_SPlex*		m_pBlocks;		//	Memory Block

	protected:
		//	Implement
		_SHNode*	NewNode(_SHNode*, _SHNode*);
		void		FreeNode(_SHNode*);

	public:
		//	Attribute
		int		GetCount() const;
		BOOL	IsEmpty() const;
		void*	GetHead() const;
		void*	GetTail() const;

		//	Operation
		SHPOS	AddHead();
		SHPOS	AddHead(void*);
		SHPOS	AddTail();
		SHPOS	AddTail(void*);
		SHPOS	InsertAfter(SHPOS);
		SHPOS	InsertAfter(SHPOS, void*);
		SHPOS	InsertBefore(SHPOS);
		SHPOS	InsertBefore(SHPOS, void*);
		SHPOS	InsertCompare(void*);
		SHPOS	InsertCompareSet(void*);

		void	RemoveHead();
		void	RemoveTail();
		void	RemoveAt(SHPOS);
		void	RemoveAll();

		SHPOS	GetHeadPosition()	const;
		SHPOS	GetTailPosition()	const;
		void*	GetNext(SHPOS&);
		void*	GetPrev(SHPOS&);

		SHPOS	FindIndex(int nIndex) const;
		SHPOS	Find(void* lpData);

	public:
		SHLinkList(int nDataSize = 0, int nBlock = 10);
		virtual ~SHLinkList();

	public:
		//	Virtual Function
		virtual int		Compare(void*, void*) const;
		virtual void	FreeData(void*);
		virtual void	SetAt(SHPOS, void*);
		virtual void*	GetAt(SHPOS) const;
};

class SHListLP : public SHLinkList
{
	public:
		BOOL	m_bAutoDelete;

	public:
		SHListLP(int nBlock=10) : SHLinkList(sizeof(void*), nBlock) { m_bAutoDelete = FALSE; }
		virtual ~SHListLP();

		virtual void	SetAt(SHPOS SHPOS, void* pData);
		virtual void*	GetAt(SHPOS SHPOS) const;

	protected:
		virtual void	FreeData(void* pData);

	public:
		void	SetAutoDelete(BOOL bTrue)	{ m_bAutoDelete = bTrue; }
		BOOL	GetAutoDelete()				{ return m_bAutoDelete; }
};

class SHListObject : public SHListLP
{
	public:
		SHListObject(int nBlock=10) : SHListLP(nBlock) { ; }
		virtual ~SHListObject();

	protected:
		virtual void	FreeData(void* pData);
};

//	Inline
inline int SHLinkList::GetCount() const
{
	return m_nCount;
}

inline BOOL SHLinkList::IsEmpty() const
{
	return (!m_nCount);
}

inline void* SHLinkList::GetHead() const
{
	if (m_pNodeHead)
	{
		return GetAt(m_pNodeHead);
	}
	else
	{
		return NULL;
	}
}

inline void* SHLinkList::GetTail() const
{
	if (m_pNodeTail)
	{
		return GetAt(m_pNodeTail);
	}
	else
	{
		return NULL;
	}
}

inline SHPOS SHLinkList::GetHeadPosition() const
{
	return m_pNodeHead;
}

inline SHPOS SHLinkList::GetTailPosition() const
{
	return m_pNodeTail;
}

inline void* SHLinkList::GetNext(SHPOS& pPos)
{
	void*	pData;

	pData = GetAt(pPos);
	pPos  = pPos->pNext;

	return pData;
}

inline void* SHLinkList::GetPrev(SHPOS& pPos)
{
	void*	pData;

	pData = GetAt(pPos);
	pPos  = pPos->pPrev;

	return pData;
}

inline SHPOS SHLinkList::AddHead(void* pData)
{
	SHPOS	pPos;

	pPos = AddHead();
	SetAt(pPos, pData);
	
	return pPos;
}

inline SHPOS SHLinkList::AddTail(void* pData)
{
	SHPOS	pPos;

	pPos = AddTail();
	SetAt(pPos, pData);

	return pPos;
}

inline SHPOS SHLinkList::InsertAfter(SHPOS nPos, void* pData)
{
	SHPOS	pPos;

	pPos = InsertAfter(nPos);
	SetAt(pPos, pData);

	return pPos;
}

inline SHPOS SHLinkList::InsertBefore(SHPOS nPos, void* pData)
{
	SHPOS	pPos;

	pPos = InsertBefore(nPos);
	SetAt(pPos, pData);

	return pPos;
}

inline SHPOS SHLinkList::InsertCompareSet(void* pData)
{
	SHPOS	pPos;

	pPos = InsertCompare(pData);
	SetAt(pPos, pData);

	return pPos;
}

//--------------------------------------------------------------------------------------//

SHLinkList::SHLinkList(int nDataSize, int nBlock)
{
	ASSERT(nDataSize > 0);

	m_nDataSize		= nDataSize;
	m_nBlockSize	= nBlock;
	m_nCount		= 0;

	m_pNodeHead		= NULL;
	m_pNodeTail		= NULL;
	m_pNodeFree		= NULL;
	m_pBlocks		= NULL;
}

SHLinkList::~SHLinkList()
{
	RemoveAll();
}

_SHNode* SHLinkList::NewNode(_SHNode* pPrev, _SHNode* pNext)
{
	_SHNode* pNewNode = NULL;

	//	Free Node Empty
	if (!m_pNodeFree)
	{
		_SPlex*	pNewBlock = (_SPlex*) new char[m_nBlockSize*(m_nDataSize + sizeof(_SHNode) - sizeof(char)) + sizeof(void*)];

		//	Memory Alloc Fail
		if (!pNewBlock)
		{
			return NULL;
		}

		pNewBlock->m_pNext = m_pBlocks;
		m_pBlocks = pNewBlock;

		//	Initialize New Nodes
		_SHNode* pNode;
		for (int i = 0 ; i < m_nBlockSize ; i++)
		{
			pNode = (_SHNode*) ((char*) pNewBlock + sizeof(void*) + i*(sizeof(_SHNode) - sizeof(char) + m_nDataSize));
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}

	m_nCount++;
	ASSERT(m_nCount > 0);
	pNewNode = m_pNodeFree;
	m_pNodeFree = pNewNode->pNext;

	pNewNode->pPrev = pPrev;
	pNewNode->pNext = pNext;

	//	Zero Init
	memset(&pNewNode->Data, 0, m_nDataSize);

	return pNewNode;
}

void SHLinkList::FreeNode(_SHNode* pNode)
{
	pNode->pNext = m_pNodeFree;
	m_pNodeFree	 = pNode;

	//	Call Free Data
	FreeData(&pNode->Data);

	m_nCount--;
	ASSERT(m_nCount >= 0);
}

void SHLinkList::RemoveAll()
{
	_SPlex	*pRoll, *pNext;

	//	Call Free Element
	SHPOS	pPos;
	while (pPos = GetHeadPosition())
	{
		RemoveAt(pPos);
	}

	pRoll = m_pBlocks;

	//	Free All Memory Block
	while (pRoll)
	{
		pNext = pRoll->m_pNext;
		delete pRoll;

		pRoll = pNext;
	}

	//	Initialize Pointer & Count
	m_nCount	= 0;
	m_pNodeHead = NULL;
	m_pNodeTail = NULL;
	m_pNodeFree = NULL;
	m_pBlocks	= NULL;
}

SHPOS SHLinkList::AddHead()
{
	_SHNode* pNewNode;
	pNewNode = NewNode(NULL, m_pNodeHead);

	if (m_pNodeHead)
	{
		m_pNodeHead->pPrev = pNewNode;
	}
	else
	{
		m_pNodeTail = pNewNode;
	}

	m_pNodeHead = pNewNode;

	return pNewNode;
}

SHPOS SHLinkList::AddTail()
{
	_SHNode* pNewNode;
	pNewNode = NewNode(m_pNodeTail, NULL);

	if (m_pNodeTail)
	{
		m_pNodeTail->pNext = pNewNode;
	}
	else
	{
		m_pNodeHead = pNewNode;
	}

	m_pNodeTail = pNewNode;

	return pNewNode;
}

SHPOS SHLinkList::InsertAfter(SHPOS pPos)
{
	_SHNode* pNewNode;
	pNewNode = NewNode(pPos, pPos->pNext);
	pPos->pNext = pNewNode;

	if (pNewNode->pNext)
	{
		pNewNode->pNext->pPrev = pNewNode;
	}
	else
	{
		m_pNodeTail = pNewNode;
	}

	return pNewNode;
}

SHPOS SHLinkList::InsertBefore(SHPOS pPos)
{
	_SHNode* pNewNode;
	pNewNode = NewNode(pPos->pPrev, pPos);
	pPos->pPrev = pNewNode;

	if (pNewNode->pPrev)
	{
		pNewNode->pPrev->pNext = pNewNode;
	}
	else
	{
		m_pNodeHead = pNewNode;
	}

	return pNewNode;
}

SHPOS SHLinkList::InsertCompare(void* pData)
{
	_SHNode* pNode;
	int		 nComp;
	pNode = m_pNodeHead;

	while (pNode)
	{
		nComp = Compare(pData, &pNode->Data);

		if (nComp < 0)
		{
			return (InsertBefore(pNode));
		}
		else if (!nComp)
		{
			while (pNode)
			{
				if (Compare(pData, &pNode->Data))
				{
					return (InsertBefore(pNode));
				}

				pNode = pNode->pNext;
			}

			return AddTail();
		}

		pNode = pNode->pNext;
	}

	return AddTail();
}

void SHLinkList::RemoveHead()
{
	if (!m_pNodeHead)
	{
		return;
	}

	SHPOS vP = m_pNodeHead;

	if (m_pNodeHead != m_pNodeTail)
	{
		m_pNodeHead->pNext->pPrev = NULL;
		m_pNodeHead = m_pNodeHead->pNext;
	}
	else
	{
		m_pNodeHead = NULL;
		m_pNodeTail = NULL;
	}

	FreeNode(vP);
}

void SHLinkList::RemoveTail()
{
	if (!m_pNodeTail)
	{
		return;
	}

	SHPOS vP = m_pNodeTail;

	if (m_pNodeTail != m_pNodeHead)
	{
		m_pNodeTail->pPrev->pNext = NULL;
		m_pNodeTail = m_pNodeTail->pPrev;
	}
	else
	{
		m_pNodeHead = NULL;
		m_pNodeTail = NULL;
	}

	FreeNode(vP);
}

void SHLinkList::RemoveAt(SHPOS pPos)
{
	if (pPos->pPrev)
	{
		pPos->pPrev->pNext = pPos->pNext;
	}
	else
	{
		m_pNodeHead = pPos->pNext;
	}

	if (pPos->pNext)
	{
		pPos->pNext->pPrev = pPos->pPrev;
	}
	else
	{
		m_pNodeTail = pPos->pPrev;
	}

	FreeNode(pPos);
}

void SHLinkList::SetAt(SHPOS pPos, void* pData)
{
	memcpy(&pPos->Data, pData, m_nDataSize);
}

SHPOS SHLinkList::FindIndex(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nCount)
	{
		return NULL;
	}

	_SHNode* pNode;
	pNode = m_pNodeHead;

	for (int i = 0; i < nIndex; i++)
	{
		pNode = pNode->pNext;
	}

	return pNode;
}

SHPOS SHLinkList::Find(void* pData)
{
	SHPOS	vPos = GetHeadPosition();
	SHPOS	vPosCur;
	void*	pD;

	while (vPos)
	{
		vPosCur = vPos;
		pD = GetNext(vPos);

		if (pD == pData)
		{
			return vPosCur;
		}
	}

	return NULL;
}

int	SHLinkList::Compare(void* pData1, void* pData2) const
{
	return (memcmp(pData1, pData2, m_nDataSize));
}

void SHLinkList::FreeData(void* pData)
{

}

void* SHLinkList::GetAt(SHPOS pPos) const
{
	return (&pPos->Data);
}

/////////////////////////////////////////////////
//	SHListLP
/////////////////////////////////////////////////
SHListLP::~SHListLP()
{
	RemoveAll();
}

void SHListLP::SetAt(SHPOS pPos, void* pData)
{
	memcpy(&pPos->Data, &pData, m_nDataSize);
}

void* SHListLP::GetAt(SHPOS pPos) const
{
	void* pReturn = NULL;
	memcpy(&pReturn, &pPos->Data, m_nDataSize);
	return pReturn;
}

void SHListLP::FreeData(void* pData)
{
	if (m_bAutoDelete)
	{
//		void* pDelete = NULL;
		char* pDelete = NULL;
		memcpy(&pDelete, pData, m_nDataSize);
		delete pDelete;
	}
}

/////////////////////////////////////////////////
//	SHListObject
/////////////////////////////////////////////////
SHListObject::~SHListObject()
{
	RemoveAll();
}

void SHListObject::FreeData(void* pData)
{
	if (m_bAutoDelete)
	{
//		void* pObject = NULL;
		char* pObject = NULL;
		memcpy(&pObject, pData, m_nDataSize);
		delete pObject;
	}
}

//--------------------------------------------------------------------------------------//

#endif
