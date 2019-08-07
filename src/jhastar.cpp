/**
 * # JHAStar Ver, 1.0
 *
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#include "jhastar.h"

JHAStar::JHAStar(int* Map, int width, int height)
{
	int i = 0;
	int j = 0;

	iMapWidth  = width;
	iMapHeight = height;
	ppMap = new int*[iMapHeight];

	for (i = 0 ; i < height ; i++)
	{
		ppMap[i] = new int[width];
	}

	for (i = 0 ; i < iMapHeight ; i++)
	{
		for (j = 0 ; j < iMapWidth ; j++)
		{
			ppMap[i][j] = (int) Map[(i * iMapWidth) + j];
		}
	}

	openedNodeList = new AStar_Node;
	closedNodeList = new AStar_Node;
}

JHAStar::~JHAStar()
{
	int i = 0;

	for (i = 0 ; i < iMapHeight ; i++)
	{
		delete [] ppMap[i];
	}

	delete [] ppMap;

	clearPath();

	delete openedNodeList;
	delete closedNodeList;
	openedNodeList = NULL;
	closedNodeList = NULL;
}

void JHAStar::clearPath()
{
	AStar_Node* tmpNode1 = NULL;
	AStar_Node* tmpNode2 = NULL;

	if (openedNodeList != NULL)
	{
		tmpNode1 = openedNodeList->next;

		while (tmpNode1 != NULL)
		{
			tmpNode2 = tmpNode1;
			tmpNode1 = tmpNode1->next;
			delete tmpNode2;
			tmpNode2 = NULL;
		}

		openedNodeList->next = NULL;
	}

	if (closedNodeList != NULL)
	{
		tmpNode1 = closedNodeList->next;

		while (tmpNode1 != NULL)
		{
			tmpNode2 = tmpNode1;
			tmpNode1 = tmpNode1->next;
			delete tmpNode2;
			tmpNode2 = NULL;
		}

		closedNodeList->next = NULL;
	}
}

int JHAStar::calcManhattan(int sx, int sy, int tx, int ty)
{
	return (abs(sx - tx) + abs(sy - ty)) * WEIGHT_VH_MOVE;
}

AStar_Node* JHAStar::findPath(int sx, int sy, int tx, int ty, bool bDiag = true)
{
	clearPath();

	bDiagonal = bDiag;

	AStar_Node* firstNode = new AStar_Node;
	firstNode->x = sx;
	firstNode->y = sy;
	firstNode->g = 0;
	firstNode->h = calcManhattan(sx, sy, tx, ty);
	firstNode->f = firstNode->g + firstNode->h;
	firstNode->parent = NULL;
	firstNode->next = NULL;

	for (int i = 0 ; i < 8 ; i++)
	{
		firstNode->child[i] = NULL;
	}

	openedNodeList->next = firstNode;

	AStar_Node* current_node = NULL;

	while (1)
	{
		if (openedNodeList->next == NULL)
		{
			return NULL;
		}

		current_node = openedNodeList->next;
		openedNodeList->next = current_node->next;

		current_node->next = closedNodeList->next;
		closedNodeList->next = current_node;

		if ((current_node->x == tx) && (current_node->y == ty))
		{
			return current_node;
		}		

		if (bDiagonal)
		{
			if (isMovable(current_node->x + 1, current_node->y - 1)) 
			{ 
				exploreSub(current_node, current_node->x + 1, current_node->y - 1, tx, ty, WEIGHT_DG_MOVE);
			}

			if (isMovable(current_node->x + 1, current_node->y + 1)) 
			{ 
				exploreSub(current_node, current_node->x + 1, current_node->y + 1, tx, ty, WEIGHT_DG_MOVE); 
			}			

			if (isMovable(current_node->x - 1, current_node->y + 1)) 
			{ 
				exploreSub(current_node, current_node->x - 1, current_node->y + 1, tx, ty, WEIGHT_DG_MOVE); 
			}

			if (isMovable(current_node->x - 1, current_node->y - 1)) 
			{
				exploreSub(current_node, current_node->x - 1, current_node->y - 1, tx, ty, WEIGHT_DG_MOVE);
			}
		}

		if (isMovable(current_node->x + 1, current_node->y)) 
		{ 
			exploreSub(current_node, current_node->x + 1, current_node->y, tx, ty, WEIGHT_VH_MOVE); 
		}

		if (isMovable(current_node->x, current_node->y + 1)) 
		{ 
			exploreSub(current_node, current_node->x, current_node->y + 1, tx, ty, WEIGHT_VH_MOVE); 
		}

		if (isMovable(current_node->x - 1, current_node->y)) 
		{
			exploreSub(current_node, current_node->x - 1, current_node->y, tx, ty, WEIGHT_VH_MOVE);
		}

		if (isMovable(current_node->x, current_node->y - 1)) 
		{ 
			exploreSub(current_node, current_node->x, current_node->y - 1, tx, ty, WEIGHT_VH_MOVE);
		}	
	}
}

AStar_Node* JHAStar::findOpenedNode(int cx, int cy)
{
	AStar_Node* tmp = openedNodeList->next;

	while (tmp != NULL)
	{
		if ((tmp->x == cx) && (tmp->y == cy))
		{
			return tmp;
		}

		tmp = tmp->next;
	}

	return NULL;
}

AStar_Node* JHAStar::findClosedNode(int cx, int cy)
{
	AStar_Node* tmp = closedNodeList->next;

	while (tmp != NULL)
	{
		if ((tmp->x == cx) && (tmp->y == cy))
		{
			return tmp;
		}

		tmp = tmp->next;
	}

	return NULL;
}

void JHAStar::exploreSub(AStar_Node* current_node, int cx, int cy, int tx, int ty, int cost)
{
	int		i = 0;
	int		g = current_node->g + cost;
	AStar_Node*	existingNode = NULL;

	if ((existingNode = findOpenedNode(cx, cy)) != NULL)
	{
		for (i = 0 ; i < 8 ; i++)
		{
			if (current_node->child[i] == NULL)
			{
				current_node->child[i] = existingNode;
				break;
			}
		}

		if (g < existingNode->g)
		{
			existingNode->g = g;
			existingNode->f = existingNode->g + existingNode->h;
			existingNode->parent = current_node;
		}
	}
	else if ((existingNode = findClosedNode(cx, cy)) != NULL)
	{
		for (i = 0 ; i < 8 ; i++)
		{
			if (current_node->child[i] == NULL)
			{
				current_node->child[i] = existingNode;
				break;
			}
		}

		if (g < existingNode->g)
		{
			existingNode->g = g;
			existingNode->f = existingNode->g + existingNode->h;
			existingNode->parent = current_node;
		}
	}
	else
	{
		AStar_Node* newNode = new AStar_Node;

		for (i = 0 ; i < 8 ; i++)
		{
			newNode->child[i] = NULL;
		}

		newNode->parent = current_node;
		newNode->g = g;
		newNode->h = calcManhattan(cx, cy, tx, ty);
		newNode->f = newNode->g + newNode->h;
		newNode->x = cx;
		newNode->y = cy;

		for (i = 0 ; i < 8 ; i++)
		{
			if (current_node->child[i] == NULL)
			{
				current_node->child[i] = newNode;
				break;
			}
		}

		insertNode(newNode);
	}
}

void JHAStar::insertNode(AStar_Node* newNode)
{
	AStar_Node* tmp1 = NULL;
	AStar_Node* tmp2 = NULL;
	int f = 0;

	if (openedNodeList->next == NULL)
	{
		openedNodeList->next = newNode;
	}
	else
	{
		f = newNode->f;
		tmp1 = openedNodeList;
		tmp2 = openedNodeList->next;

		while ((tmp2 != NULL) && (tmp2->f < f))
		{
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}

		newNode->next = tmp2;
		tmp1->next = newNode;
	}
}

bool JHAStar::isMovable(int x, int y)
{
	bool bReturn = true;
	
	if ((x < 0) || (y < 0))
	{
		bReturn = false;
	}
	
	if ((x >= iMapWidth) || (y >= iMapHeight))
	{
		bReturn = false;
	}

	if (ppMap[y][x] == TILE_BLOCK)
	{
		bReturn = false;
	}

	return bReturn;
}

void JHAStar::printOut()
{
	for (int i = 0 ; i < iMapHeight ; i++)
	{
		for (int j = 0 ; j < iMapWidth ; j++)
		{
			if (ppMap[i][j] == TILE_PATH)
			{
				printf("  ");
			}
			else
			{
				printf("[]");
			}
		}
		
		printf("\n");
	}
}

