/**
 * # JHAStar Ver, 1.0
 *
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#ifndef _JHASTAR_C_
#define _JHASTAR_C_

#include "jhstd.h"

//--------------------------------------------------------------------------------------//

#define WEIGHT_VH_MOVE 10
#define WEIGHT_DG_MOVE 14	

#define TILE_PATH  0
#define TILE_BLOCK 1

struct AStar_Node
{
	int		g;				//	Goal
	int		h;				//	Heuristic
	int		f;				//	Fitness
	
	int		x;
	int		y;

	AStar_Node*	parent;			
	AStar_Node*	child[8];		
	AStar_Node*	next;		
};

class JHAStar
{
	public:
		JHAStar(int* Map, int width, int height);
		virtual ~JHAStar();

	public:
		void	clearPath();
		int		calcManhattan(int sx, int sy, int tx, int ty);
	
		AStar_Node*	findPath(int sx, int sy, int tx, int ty, bool bDiag);
		AStar_Node*	findOpenedNode(int cx, int cy);
		AStar_Node*	findClosedNode(int cx, int cy);

		void	exploreSub(AStar_Node* current_node, int cx, int cy, int tx, int ty, int cost);
		bool	isMovable(int x, int y);
		void 	insertNode(AStar_Node* newNode);
		void	printOut();
				
	private:
		int		iMapWidth;
		int		iMapHeight;
		int**	ppMap;
		bool	bDiagonal;
		AStar_Node*	openedNodeList;
		AStar_Node*	closedNodeList;
};

//--------------------------------------------------------------------------------------//

#endif
