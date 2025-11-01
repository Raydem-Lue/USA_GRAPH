#include <stdio.h>
#include "graph.h"
#include "err.h"

int main()
   {
    int n;
    Graph G;
    printf("enter the number of nodes in graph maximum = %d\n",max);
    scanf("%d",&n);
    G = CreateGraph(n);
    buildadjm(G);

    printf("\nAdjacency matrix:\n");
    printadjm(G);

    printf("\nDepth first search - DFS:\n");
    dfs(G, 0);

    DisposeGraph(G);
    putchar('\n');
    return 0;
   }
