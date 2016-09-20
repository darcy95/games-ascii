/* =====================================================================================
 *	JHListDouble Ver, 1.0
 * 
 */

#ifndef JHDOUBLELINKLIST_C_
#define JHDOUBLELINKLIST_C_

//--------------------------------------------------------------------------------------//

typedef struct JHNode 
{
	void*	Data;
	JHNode* Next;
	JHNode* Prev;

} JHNode_t;

class JHList
{
	public: 
		JHList();
		virtual ~JHList();

	public:
		int		count();
		bool	isEmpty();
		void	addHead(void*);
		void	addTail(void*);
		void	addBefere(JHNode*, void*);
		void	addAfter(JHNode*, void*);
		void	remHead();
		void	remTail();
		void	remIter(JHNode*);
		void	removeAll();
		JHNode*	getNext(JHNode*);
		JHNode*	getPrev(JHNode*);
		void*	getHead();
		void*	getTail();
		void*	getAt(JHNode*);

	private:
		JHNode* m_pHead;
		JHNode* m_pTail;
		JHNode* m_pCurr;
};
							   
//--------------------------------------------------------------------------------------//

JHList::JHList()
{

}

JHList::~JHList()
{

}

int	JHList::count()
{

}

bool JHList::isEmpty()
{

}

void JHList::addHead(void* pData)
{

}

void JHList::addTail(void* pData)
{

}

void JHList::addBefere(JHNode* pNode, void* pData)
{

}

void JHList::addAfter(JHNode* pNode, void* pData)
{

}

void JHList::remHead()
{

}

void JHList::remTail()
{

}

void JHList::remIter(JHNode* pNode)
{

}

void JHList::removeAll()
{

}

JHNode*	JHList::getNext(JHNode* pNode)
{

}

JHNode*	JHList::getPrev(JHNode* pNode)
{

}

void* JHList::getHead()
{

}

void* JHList::getTail()
{

}

void* JHList::getAt(JHNode* pNode)
{

}

//--------------------------------------------------------------------------------------//

#endif




































