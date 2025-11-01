#include <stdio.h>
#include <stdlib.h>
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
    if (G == NULL)
        Error("Out of space!!!");

    G->nodes = NodesCount;
    return G;
}

void DisposeGraph(Graph G)
{
    free(G);
}

/* построение матрицы смежности */
void buildadjm(Graph G)
{
    int i, j;
    for (i = 0; i < G->nodes; i++)
        for (j = 0; j < G->nodes; j++)
            scanf("%d", &(G->adj[i][j]));
}

void printadjm(Graph G)
{
    int i, j;
    for (i = 0; i < G->nodes; i++)
    {
        for (j = 0; j < G->nodes; j++)
            printf(" %d", G->adj[i][j]);
        putchar('\n');
    }
}

void ClearVisited(Graph G)
{
    int n;
    for (n = 0; n < G->nodes; n++)
        G->visited[n] = 0;
}

/* --------------------- DFS --------------------- */

void dfs2(Graph G, int v)
{
    int w;
    G->visited[v] = 1; // исправлено — теперь помечаем вершину как посещённую при входе
    printf("%d ", v);

    for (w = 0; w < G->nodes; w++)
        if (G->adj[v][w] == 1 && G->visited[w] == 0)
            dfs2(G, w);

    G->visited[v] = 2;
}

void dfs(Graph G, int v0)
{
    ClearVisited(G);
    int i;

    for (i = v0; i < G->nodes; i++)
    {
        if (G->visited[i] == 0)
        {
            dfs2(G, i);
            printf("\n");
        }
    }

    for (i = 0; i < v0; i++)
    {
        if (G->visited[i] == 0)
        {
            dfs2(G, i);
            printf("\n");
        }
    }
}

/* --------------------- DFSSPANNING TREE --------------------- */

void dfs2st(Graph G, int v)
{
    int w;
    G->visited[v] = 1;

    for (w = 0; w < G->nodes; w++)
        if (G->adj[v][w] == 1 && G->visited[w] == 0)
        {
            printf("(%d, %d)\n", v, w);
            dfs2st(G, w);
        }

    G->visited[v] = 2;
}

void dfsst(Graph G, int v0)
{
    ClearVisited(G);
    int i;

    for (i = v0; i < G->nodes; i++)
    {
        if (G->visited[i] == 0)
        {
            dfs2st(G, i);
            printf("\n");
        }
    }

    for (i = 0; i < v0; i++)
    {
        if (G->visited[i] == 0)
        {
            dfs2st(G, i);
            printf("\n");
        }
    }
}

/* --------------------- BFS --------------------- */

void bfs(Graph G, int v0)
{
    ClearVisited(G);
    Queue *q = CreateQ();
    int i;

    for (i = v0; i < G->nodes; i++)
    {
        if (G->visited[i] == 0)
        {
            Enqueue(q, i);
            G->visited[i] = 1;

            while (!EmptyQ(q))
            {
                int v = Dequeue(q);
                printf("%d ", v);

                for (int w = 0; w < G->nodes; w++)
                {
                    if (G->adj[v][w] == 1 && G->visited[w] == 0)
                    {
                        Enqueue(q, w);
                        G->visited[w] = 1;
                    }
                }
            }
            printf("\n");
        }
    }

    for (i = 0; i < v0; i++)
    {
        if (G->visited[i] == 0)
        {
            Enqueue(q, i);
            G->visited[i] = 1;

            while (!EmptyQ(q))
            {
                int v = Dequeue(q);
                printf("%d ", v);

                for (int w = 0; w < G->nodes; w++)
                {
                    if (G->adj[v][w] == 1 && G->visited[w] == 0)
                    {
                        Enqueue(q, w);
                        G->visited[w] = 1;
                    }
                }
            }
            printf("\n");
        }
    }
}

/* --------------------- BFS SPANNING TREE --------------------- */

void bfsst(Graph G, int v0)
{
    ClearVisited(G);
    Queue *q = CreateQ();
    int i;

    for (i = v0; i < G->nodes; i++)
    {
        if (G->visited[i] == 0)
        {
            Enqueue(q, i);
            G->visited[i] = 1;

            while (!EmptyQ(q))
            {
                int v = Dequeue(q);

                for (int w = 0; w < G->nodes; w++)
                {
                    if (G->adj[v][w] == 1 && G->visited[w] == 0)
                    {
                        printf("(%d, %d)\n", v, w);
                        Enqueue(q, w);
                        G->visited[w] = 1;
                    }
                }
            }
            printf("\n");
        }
    }

    for (i = 0; i < v0; i++)
    {
        if (G->visited[i] == 0)
        {
            Enqueue(q, i);
            G->visited[i] = 1;

            while (!EmptyQ(q))
            {
                int v = Dequeue(q);

                for (int w = 0; w < G->nodes; w++)
                {
                    if (G->adj[v][w] == 1 && G->visited[w] == 0)
                    {
                        printf("(%d, %d)\n", v, w);
                        Enqueue(q, w);
                        G->visited[w] = 1;
                    }
                }
            }
            printf("\n");
        }
    }
}
