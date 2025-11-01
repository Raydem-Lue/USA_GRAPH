#define max 10

struct GraphRecord;
typedef struct GraphRecord *Graph;

Graph CreateGraph(int NodesCount);
void DisposeGraph(Graph G);
void buildadjm(Graph G);
void printadjm(Graph G);
void ClearVisited(Graph G);

void bfs(Graph G, int v0);
void bfsst(Graph G, int v0);
void dfs(Graph G, int v0);
void dfs2(Graph G, int v);
void dfsst(Graph G, int v0);
void dfsst2(Graph G, int v);

void MyPrintf(const char *format, ...);
