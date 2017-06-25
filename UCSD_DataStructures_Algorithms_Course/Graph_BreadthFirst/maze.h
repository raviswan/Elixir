#ifndef MAZE_H_
#define MAZE_H_

#include "graph.h"
#include "list.h"

typedef struct _RoomVertex{
	void* data;
	VertexColor color;
} RoomVertex;

int isExitReachable(Graph *pMaze, char entrance, char exit); 


#endif
