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
	void OnGameStartAct();				//	게임 시작 시점에 처리할 액션 (상속)
	void OnGameOverAct();				//	게임 오버 시점에 처리할 액션 (상속)
	void OnBlockCopyN2CAct();			//	다음 블록을 현재 블록으로 바꾸는 시점에 처리 될 액션 (상속)
	void OnLineCompleteAct(int nLine);	//	라인이 완성되는 시점에 처리할 액션 (상속)
	void OnBlockDownAct();				//	블록이 내려 가는 시점에서 처리할 액션 (상속) 
	void OnBlockTurnAct();				//	블록을 회전하는 시점에 처리할 액션 (상속)
	void OnBlockMoveAct();				//	블록을 움직이는 시점에 처리할 액션 (상속)	
	void OnImpossibleAct();				//	불가능한 움직임을 시도할 때 나타내는 액션 (상속)
	void OnSettleAct();					//	블록을 바닥에 고정 하는 시점에 처리할 액션 (상속)

public:
	int	m_nBlockCount;					//	일정 갯수의 블록이 맞추어 질 때마다 하강 속도 증가
};


//--------------------------------------------------------------------------------------//
#endif
