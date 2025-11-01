#include <stdio.h>
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
    ClearVisited(G);
    dfs2(G,v0);
}

void dfs2(Graph G, int v)
{
    int w;

    printf("The node opened: %d\n",v);
    for(w = 0; w<G->nodes; w++)
        if(G->adj[v][w] == 1 && G->visited[w] == 0)
            dfs2(G,w);
    G->visited[v] = 2;
}
