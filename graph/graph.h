#include<iostream>
#include<algorithm>
#include<queue>
#include<limits>
using namespace std;
#define SIZE 20
#define MAX_VERTEX_NUM 20
struct vertex{
    int num;
    char name[SIZE];
};
struct edge{
    int fVex;
    int sVex;
    int weight=INT_MAX;
    friend bool operator<(edge a,edge b){//这样是从小到大排列,对于sort  对于优先队列，从小到达排列是反的
        return a.weight<b.weight;
    }
};
struct path{
    int vertex[SIZE];//路径的顶点集合
    path *next; //路径的指针
};
class graph{
private:
    int adjMatrix[SIZE][SIZE];//邻接矩阵 
    vertex vexs[SIZE];
    int vexNum;
    int edgeNum;
public:
    graph(int max=INT_MAX){//初始化
        for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
			}
		}
			vexs[SIZE] = {0};
			edgeNum = 0;
			vexNum = 0;
    };
    ~graph();
    bool insertVex(vertex vex);
	bool insertEdge(edge sedge);//插入边
    vertex getVex(int index);
	edge getEdge(int vex1, int vex2);//获得两个顶点的边

    void setVexNum(int);//设置当前图的顶点个数
	int getVexNum(void);//返回当前图的顶点个数
	int getEdgeNum(void);
	int getFirstNeighbor(int);
	int getNextNeighbor(int v, int w);
	int findAdjSpots(int index, edge *aEdge);//查询所有与指定顶点相连的边

	void DFSTraverse(int nVex);//深度搜索
	void DFSTraverse2(int nVex, path* &pList);//深度搜索
    void BFSTraverse(int vex);

    int* BFS_MIN_Distance(int level0);//最短路径   广度优先算法得到
	int Dijkstra(int start,int end,vector<int>& aPath);//找到最短路径 Dijkstra
	int prim(int first,vector<edge>&aPath);//找到最小生成树
    int Kruskal(vector<edge>&aPath);
private:
    void BFS(int vex,bool visited[],queue<int> &vexQueue);
    void DFS(int vex,bool bVisited[]);
    void DFS_2(int vex,bool bVisited[],int index,path* &pList);
};
/**
 * 生成树：一个连通图的生成树包含图的所有顶点，并且只含尽可能少的边。
 * 对于生成树来说，若砍去一条边，则会使生成树变成非连通图，若增加一条边，会形成一个回路
 * 最小生成树：边上权值之和最小的那棵生成树
 */