#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "err.h"
#include "graph.h"
#include "lqueue.h"

struct GraphRecord
{
      int adj[max][max];
      int visited[max];
      int nodes;
};

Graph CreateGraph(int NodesCount)
{
      Graph G;

      G = malloc(sizeof(struct GraphRecord));
      if(G == NULL) Error( "Out of space!!!" );

      G->nodes = NodesCount;

      return G;
}


void DisposeGraph(Graph G)
{
     free(G);
}


/* a function to build adjacency matrix of a graph */
void buildadjm(Graph G)
   {
     int i,j;
     for(i=0;i<G->nodes;i++)
         for(j=0;j<G->nodes;j++)
          {
           printf("enter 1 if there is an edge from %d to %d, otherwise enter 0 \n", i,j);
           scanf("%d",&(G->adj[i][j]));
           }
      }

void printadjm(Graph G)
{
     int i,j;
     for(i=0;i<G->nodes;i++)
     {
         for(j=0;j<G->nodes;j++)
          printf(" %d",G->adj[i][j]);
         putchar('\n');
     }
}

void ClearVisited(Graph G)
{
     int n;
     for(n=0; n<G->nodes; n++)
         G->visited[n] = 0;
}
// 3 stavy - 0 (not found), 1 (opened), 2 (closed)
void dfs(Graph G, int v0)
{
    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v0 < 0 || v0 >= G->nodes)
        Error("Failed\n");

    ClearVisited(G);

    int component = 0;

    for(int i = 0; i < G->nodes; ++i)
    {
        int start = (v0 + i) % G->nodes;

        if(G->visited[start] != 0)
            continue;

        ++component;
        printf("Component %d:", component);
        dfs2(G, start);
        printf("\n");
    }
}

void dfs2(Graph G, int v)
{
    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v < 0 || v >= G->nodes)
        Error("Failed\n");

    G->visited[v] = 1;
    printf(" %d", v);

    for(int w = 0; w < G->nodes; ++w)
    {
        if(G->adj[v][w] == 1 && G->visited[w] == 0)
            dfs2(G, w);
    }

    G->visited[v] = 2;
}

void dfsst(Graph G, int v0)
{
    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v0 < 0 || v0 >= G->nodes)
        Error("Failed\n");

    ClearVisited(G);

    int component = 0;

    for(int i = 0; i < G->nodes; ++i)
    {
        int start = (v0 + i) % G->nodes;

        if(G->visited[start] != 0)
            continue;

        ++component;
        printf("Component %d:\n", component);
        dfsst2(G, start);
        printf("\n");
    }
}

void dfsst2(Graph G, int v)
{
    int w;

    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v < 0 || v >= G->nodes)
        Error("Failed\n");

    G->visited[v] = 1;
    for(w = 0; w < G->nodes; ++w)
        if(G->adj[v][w] == 1 && G->visited[w] == 0)
        {
            printf("Edge: (%d,%d)\n", v, w);
            dfsst2(G, w);
        }
    G->visited[v] = 2;
}

void bfs(Graph G, int v0)
{
    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v0 < 0 || v0 >= G->nodes)
        Error("Failed\n");

    ClearVisited(G);

    int component = 0;

    for(int i = 0; i < G->nodes; ++i)
    {
        int start = (v0 + i) % G->nodes;

        if(G->visited[start] != 0)
            continue;

        LQueue queue = CreateQueue();
        if(queue == NULL)
            Error("Failed\n");

        ++component;
        printf("Component %d:", component);

        Enqueue(start, queue);
        G->visited[start] = 1;

        while(!IsEmptyQueue(queue))
        {
            int v = FrontAndDequeue(queue);

            if(v < 0 || v >= G->nodes)
                Error("Failed\n");

            printf(" %d", v);

            for(int w = 0; w < G->nodes; ++w)
            {
                if(G->adj[v][w] == 1 && G->visited[w] == 0)
                {
                    G->visited[w] = 1;
                    Enqueue(w, queue);
                }
            }

            G->visited[v] = 2;
        }

        RemoveQueue(&queue);
        printf("\n");
    }
}

void bfsst(Graph G, int v0)
{
    if(G == NULL)
        Error("Failed\n");
    if(G->nodes <= 0 || G->nodes > max)
        Error("Failed\n");
    if(v0 < 0 || v0 >= G->nodes)
        Error("Failed\n");

    ClearVisited(G);

    int component = 0;

    for(int i = 0; i < G->nodes; ++i)
    {
        int start = (v0 + i) % G->nodes;

        if(G->visited[start] != 0)
            continue;

        LQueue queue = CreateQueue();
        if(queue == NULL)
            Error("Failed\n");

        ++component;
        printf("Component %d:\n", component);

        Enqueue(start, queue);
        G->visited[start] = 1;

        while(!IsEmptyQueue(queue))
        {
            int v = FrontAndDequeue(queue);

            if(v < 0 || v >= G->nodes)
                Error("Failed\n");

            for(int w = 0; w < G->nodes; ++w)
            {
                if(G->adj[v][w] == 1 && G->visited[w] == 0)
                {
                    G->visited[w] = 1;
                    printf("Edge: (%d,%d)\n", v, w);
                    Enqueue(w, queue);
                }
            }

            G->visited[v] = 2;
        }

        RemoveQueue(&queue);
        printf("\n");
    }
}
