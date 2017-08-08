#define MAX_VERTEX_NUM 20
#define MAX_WEIGHT 9999
typedef float WeightType;
typedef char VertexType;
typedef struct ArcNode{
	int adjvex;
	WeightType weight;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VertexNode{
	VertexType data;
	ArcNode *firstarc;
}VertexNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
	int kind;
}ALGraph;
void CreateGraph(ALGraph &G);
int LocateVex(ALGraph G,VertexType v);
