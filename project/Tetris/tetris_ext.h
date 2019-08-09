#ifndef _JHTETRIS_EXT_C_
#define _JHTETRIS_EXT_C_

//--------------------------------------------------------------------------------------//

#include "tetris.h"

#define BRICK_SYMBOL	'#'
#define BLOCK_COUNT	24

class JHTetrisExt : public JHTetris
{
public:
	JHTetrisExt();
	virtual ~JHTetrisExt();

public:
	void OnGameStartAct();				//	���� ���� ������ ó���� �׼� (���)
	void OnGameOverAct();				//	���� ���� ������ ó���� �׼� (���)
	void OnBlockCopyN2CAct();			//	���� ����� ���� ������� �ٲٴ� ������ ó�� �� �׼� (���)
	void OnLineCompleteAct(int nLine);	//	������ �ϼ��Ǵ� ������ ó���� �׼� (���)
	void OnBlockDownAct();				//	����� ���� ���� �������� ó���� �׼� (���) 
	void OnBlockTurnAct();				//	����� ȸ���ϴ� ������ ó���� �׼� (���)
	void OnBlockMoveAct();				//	����� �����̴� ������ ó���� �׼� (���)	
	void OnImpossibleAct();				//	�Ұ����� �������� �õ��� �� ��Ÿ���� �׼� (���)
	void OnSettleAct();					//	����� �ٴڿ� ���� �ϴ� ������ ó���� �׼� (���)

public:
	int	m_nBlockCount;					//	���� ������ ����� ���߾� �� ������ �ϰ� �ӵ� ����
};


//--------------------------------------------------------------------------------------//
#endif
