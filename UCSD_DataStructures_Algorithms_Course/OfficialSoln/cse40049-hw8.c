/******************************************************************************
 * CSE-40049 - Homework #8
 *
 * File:        cse40049-hw8.c
 * Author:      Ray Mitchell
 * Date:        5/25/2011
 * System:      Intel Core 2 Duo T9300 @ 2.50 GHz
 *              4.00 GB RAM
 *              64-bit Windows 7 Ultimate
 *
 * Program Description:  Search mazes to determine if exit is reachable from
 *              entrance.
 *
 * Program Output:
                Is exit reachable in Maze 1?  Yes
                Is exit reachable in Maze 2?  No
 */
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "graph.h"
#include "queue.h"

/*---------------------------------------------------------------------------
 * Types
 *---------------------------------------------------------------------------*/
typedef struct MazeVertex_ {

    char room;
    VertexColor color;

} MazeVertex;

/*---------------------------------------------------------------------------
 * Prototypes
 *---------------------------------------------------------------------------*/
int matchMazeVertices(const void *key1, const void *key2);
void addVertex(Graph *pMaze, MazeVertex *pVertex);
void addEdge(Graph *pMaze, MazeVertex *pV1, MazeVertex *pV2);
void populateMaze1(Graph *pMaze);
void populateMaze2(Graph *pMaze);
void fatalError(const char *pMessage);

/*---------------------------------------------------------------------------
 * main
 *---------------------------------------------------------------------------*/
int main()
{
    Graph maze;

    /* Maze 1 */
    populateMaze1(&maze);
    printf("Is exit reachable in Maze 1?  %s\n",
        isExitReachable(&maze, 'A', 'G') ? "Yes" : "No");

    /* Maze 2 */
    populateMaze2(&maze);
    printf("Is exit reachable in Maze 2?  %s\n",
        isExitReachable(&maze, 'A', 'G') ? "Yes" : "No");

    graph_destroy(&maze);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------------------
 * Part a - Return whether exit is reachable from entrance (using a
 *          breadth-first search)
 *---------------------------------------------------------------------------*/
int isExitReachable(Graph *pMaze, char entrance, char exit)
{
    MazeVertex  startVertex = { entrance, white };
    Queue       queue;
    AdjList     *adjlist,
                *clr_adjlist;
    MazeVertex  *start = &startVertex,
                *clr_vertex,
                *adj_vertex;
    ListElmt    *element,
                *member;

    /* Initialize all of the vertices in the graph. */
    for (element = list_head(&graph_adjlists(pMaze)); element != NULL; element
            = list_next(element)) {

        clr_vertex = (MazeVertex *)((AdjList *) list_data(element))->vertex;

        if (pMaze->match(clr_vertex, start)) {

            /* Initialize the start vertex. */
            clr_vertex->color = gray;
        }
        else {

            /* Initialize vertices other than the start vertex. */
            clr_vertex->color = white;
        }
    }

    /* Initialize the queue with the adjacency list of the start vertex. */
    queue_init(&queue, NULL);
    if (graph_adjlist(pMaze, start, &clr_adjlist) != 0) {
        
        queue_destroy(&queue);
        return 0;
    }
    if (queue_enqueue(&queue, clr_adjlist) != 0) {
        
        queue_destroy(&queue);
        return 0;
    }

    /* Perform breadth-first search. */
    while (queue_size(&queue) > 0) {

        adjlist = (AdjList *)queue_peek(&queue);

        /* Traverse each vertex in the current adjacency list. */
        for (member = list_head(&adjlist->adjacent); member != NULL; member
                = list_next(member)) {

            adj_vertex = (MazeVertex *)list_data(member);

            /* If next adjacent vertex is the exit, return exit reachable */
            if (adj_vertex->room == exit) {
                
                queue_destroy(&queue);
                return 1;
            }

            /* Determine the color of the next adjacent vertex. */
            if (graph_adjlist(pMaze, adj_vertex, &clr_adjlist) != 0) {

                queue_destroy(&queue);
                return 0;
            }
            clr_vertex = (MazeVertex *)clr_adjlist->vertex;

            /* Color each white vertex gray and enqueue its adjacency list. */
            if (clr_vertex->color == white) {

                clr_vertex->color = gray;

                if (queue_enqueue(&queue, clr_adjlist) != 0) {

                    queue_destroy(&queue);
                    return 0;
                }
            }
        }

        /* Dequeue the current adjacency list and color its vertex black. */
        if (queue_dequeue(&queue, (void **) &adjlist) == 0) {

            ((MazeVertex *) adjlist->vertex)->color = black;
        }
        else {

            queue_destroy(&queue);
            return 0;
        }
    }

    queue_destroy(&queue);

    /* Exit wasn't reachable */
    return 0;
}

/*---------------------------------------------------------------------------
 * Helper functions
 *---------------------------------------------------------------------------*/
int matchMazeVertices(const void *key1, const void *key2)
{
    MazeVertex *pV1 = (MazeVertex *)key1;
    MazeVertex *pV2 = (MazeVertex *)key2;

    return pV1->room == pV2->room;
}

void addVertex(Graph *pMaze, MazeVertex *pVertex)
{
    if (graph_ins_vertex(pMaze, pVertex) != 0)
        fatalError("Failed to add vertex");
}

void addEdge(Graph *pMaze, MazeVertex *pV1, MazeVertex *pV2)
{
    if (graph_ins_edge(pMaze, pV1, pV2) != 0)
        fatalError("Failed to add edge");
    if (graph_ins_edge(pMaze, pV2, pV1) != 0)
        fatalError("Failed to add edge");
}

void populateMaze1(Graph *pMaze)
{
    static MazeVertex vertices[] = {
        { 'A', white },
        { 'B', white },
        { 'C', white },
        { 'D', white },
        { 'E', white },
        { 'F', white },
        { 'G', white }
    };
    int i;

    /* Initialize maze */
    graph_destroy(pMaze);
    graph_init(pMaze, matchMazeVertices, NULL);

    /* Add vertices */
    for (i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
        addVertex(pMaze, &vertices[i]);

    /* Add edges */
    addEdge(pMaze, &vertices[0], &vertices[2]);   /* A-C */
    addEdge(pMaze, &vertices[0], &vertices[3]);   /* A-D */
    addEdge(pMaze, &vertices[1], &vertices[3]);   /* B-D */
    addEdge(pMaze, &vertices[2], &vertices[5]);   /* C-F */
    addEdge(pMaze, &vertices[3], &vertices[4]);   /* D-E */
    addEdge(pMaze, &vertices[3], &vertices[6]);   /* D-G */
    addEdge(pMaze, &vertices[4], &vertices[6]);   /* E-G */
    addEdge(pMaze, &vertices[5], &vertices[6]);   /* F-G */
}

void populateMaze2(Graph *pMaze)
{
    static MazeVertex vertices[] = {
        { 'A', white },
        { 'B', white },
        { 'C', white },
        { 'D', white },
        { 'E', white },
        { 'F', white },
        { 'G', white }
    };
    int i;

    /* Initialize maze */
    graph_destroy(pMaze);
    graph_init(pMaze, matchMazeVertices, NULL);

    /* Add vertices */
    for (i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i)
        addVertex(pMaze, &vertices[i]);

    /* Add edges */
    addEdge(pMaze, &vertices[0], &vertices[2]);   /* A-C */
    addEdge(pMaze, &vertices[0], &vertices[3]);   /* A-D */
    addEdge(pMaze, &vertices[1], &vertices[3]);   /* B-D */
    addEdge(pMaze, &vertices[2], &vertices[5]);   /* C-F */
    addEdge(pMaze, &vertices[4], &vertices[6]);   /* E-G */
}

void fatalError(const char *pMessage)
{
    fprintf(stderr, pMessage);
    exit(EXIT_FAILURE);
}