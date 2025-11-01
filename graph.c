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
      int parent[max];
      int nodes;
};

Graph CreateGraph(int NodesCount)
{
      Graph G;

      G = malloc(sizeof(struct GraphRecord));
      if(G == NULL) Error( "Out of space!!!" );

      G->nodes = NodesCount;

      for(int i = 0; i < max; ++i)
      {
          G->visited[i] = 0;
          G->parent[i] = -1;
          for(int j = 0; j < max; ++j)
              G->adj[i][j] = 0;
      }

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
     if(G == NULL) return;

     for(int n=0; n<G->nodes; n++)
     {
         G->visited[n] = 0;
         G->parent[n] = -1;
     }
}

static int NormalizeStart(Graph G, int v0)
{
    if(G == NULL || G->nodes == 0) return -1;
    if(v0 < 0 || v0 >= G->nodes) return 0;
    return v0;
}

static void PrintComponentHeader(int componentIndex)
{
    MyPrintf("Component %d:", componentIndex);
}

static void PrintComponentHeaderWithNewline(int componentIndex)
{
    MyPrintf("Component %d:\n", componentIndex);
}

static void PrintEmptyTreeNotice(void)
{
    MyPrintf("(no edges)\n");
}

static void PrintComponentSeparator(void)
{
    MyPrintf("\n");
}

static void dfs_component(Graph G, int start, int componentIndex)
{
    PrintComponentHeader(componentIndex);
    dfs2(G, start);
    PrintComponentSeparator();
}

void dfs(Graph G, int v0)
{
    if(G == NULL) return;

    ClearVisited(G);

    int start = NormalizeStart(G, v0);
    if(start == -1) return;

    int componentIndex = 1;

    if(G->visited[start] == 0)
    {
        dfs_component(G, start, componentIndex++);
    }

    for(int i = 0; i < G->nodes; ++i)
    {
        if(G->visited[i] == 0)
        {
            dfs_component(G, i, componentIndex++);
        }
    }
}

void dfs2(Graph G, int v)
{
    if(G == NULL) return;

    G->visited[v] = 1;
    MyPrintf(" %d", v);

    for(int w = 0; w < G->nodes; w++)
    {
        if(G->adj[v][w] == 1 && G->visited[w] == 0)
        {
            dfs2(G, w);
        }
    }

    G->visited[v] = 2;
}

static int componentHasEdges;

static void dfsst_component(Graph G, int start, int componentIndex)
{
    PrintComponentHeaderWithNewline(componentIndex);
    componentHasEdges = 0;
    G->parent[start] = -1;
    dfsst2(G, start);
    if(!componentHasEdges)
        PrintEmptyTreeNotice();
    PrintComponentSeparator();
}

void dfsst(Graph G, int v0)
{
    if(G == NULL) return;

    ClearVisited(G);

    int start = NormalizeStart(G, v0);
    if(start == -1) return;

    int componentIndex = 1;

    if(G->visited[start] == 0)
    {
        dfsst_component(G, start, componentIndex++);
    }

    for(int i = 0; i < G->nodes; ++i)
    {
        if(G->visited[i] == 0)
        {
            dfsst_component(G, i, componentIndex++);
        }
    }
}

void dfsst2(Graph G, int v)
{
    if(G == NULL) return;

    G->visited[v] = 1;

    for(int w = 0; w < G->nodes; ++w)
    {
        if(G->adj[v][w] == 1 && G->visited[w] == 0)
        {
            G->parent[w] = v;
            componentHasEdges = 1;
            MyPrintf("%d - %d\n", v, w);
            dfsst2(G, w);
        }
    }

    G->visited[v] = 2;
}

static void bfs_component(Graph G, int start, int componentIndex)
{
    LQueue queue = CreateQueue();

    PrintComponentHeader(componentIndex);

    G->visited[start] = 1;
    Enqueue(start, queue);

    while(!IsEmptyQueue(queue))
    {
        int v = FrontAndDequeue(queue);
        MyPrintf(" %d", v);

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
    PrintComponentSeparator();
}

void bfs(Graph G, int v0)
{
    if(G == NULL) return;

    ClearVisited(G);

    int start = NormalizeStart(G, v0);
    if(start == -1) return;

    int componentIndex = 1;

    if(G->visited[start] == 0)
    {
        bfs_component(G, start, componentIndex++);
    }

    for(int i = 0; i < G->nodes; ++i)
    {
        if(G->visited[i] == 0)
        {
            bfs_component(G, i, componentIndex++);
        }
    }
}

static void bfsst_component(Graph G, int start, int componentIndex)
{
    LQueue queue = CreateQueue();
    int hasEdges = 0;

    PrintComponentHeaderWithNewline(componentIndex);

    G->visited[start] = 1;
    Enqueue(start, queue);

    while(!IsEmptyQueue(queue))
    {
        int v = FrontAndDequeue(queue);

        for(int w = 0; w < G->nodes; ++w)
        {
            if(G->adj[v][w] == 1 && G->visited[w] == 0)
            {
                G->visited[w] = 1;
                Enqueue(w, queue);
                MyPrintf("%d - %d\n", v, w);
                hasEdges = 1;
            }
        }

        G->visited[v] = 2;
    }

    if(!hasEdges)
        PrintEmptyTreeNotice();

    RemoveQueue(&queue);
    PrintComponentSeparator();
}

void bfsst(Graph G, int v0)
{
    if(G == NULL) return;

    ClearVisited(G);

    int start = NormalizeStart(G, v0);
    if(start == -1) return;

    int componentIndex = 1;

    if(G->visited[start] == 0)
    {
        bfsst_component(G, start, componentIndex++);
    }

    for(int i = 0; i < G->nodes; ++i)
    {
        if(G->visited[i] == 0)
        {
            bfsst_component(G, i, componentIndex++);
        }
    }
}

void MyPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
