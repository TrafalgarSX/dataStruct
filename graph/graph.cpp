#include<iostream>
#include<queue>
#include<fstream>
#include<algorithm>
#include<vector>
#include<math.h>
#include"union.h"
#include"graph.h"
using namespace std;
graph::~graph(){
    delete adjMatrix;
    delete vexs;
}
bool graph::insertVex(vertex vex){
    if(vexNum==MAX_VERTEX_NUM) return false;
    vexs[vexNum++]=vex;
    return true;
}
bool graph::insertEdge(edge sedge){//插入边
    if(sedge.fVex<0||sedge.fVex>=vexNum||sedge.sVex<0||sedge.sVex>=vexNum){
        return false;
    }
    adjMatrix[sedge.fVex][sedge.sVex]=sedge.weight;
    adjMatrix[sedge.sVex][sedge.fVex]=sedge.weight;
    return true;
}
vertex graph::getVex(int index){
    return vexs[index];
}
void graph::setVexNum(int num){//设置当前图的顶点个数
	vexNum=num;
}	
int graph::getVexNum(void){//返回当前图的顶点个数
    return vexNum;
}
int graph::getEdgeNum(void){
        return edgeNum;
}
int graph::getFirstNeighbor(int row){
    for(int col=0;col<vexNum;col++){
        if(adjMatrix[row][col]!=INT_MAX&&row!=col){
            return col;
        }
    }
    return -1;//如果找不到
}
//adjoin 相邻 返回处adj外顶点row的下一个邻接顶点
int graph::getNextNeighbor(int row, int adj){
    for(int col=adj+1;col<vexNum;col++){
        if(adjMatrix[row][col]!=INT_MAX&&row!=col){
            return col;
        }
    }
    return -1;//如果找不到
}

edge graph::getEdge(int fVex, int sVex){//获得两个顶点的边
    edge redge;
    redge.fVex=fVex;
    redge.sVex=sVex;
    redge.weight=adjMatrix[fVex][sVex];
    return redge;
}
int graph::findAdjSpots(int row, edge *aEdge){//查询所有与指定顶点相连的边
    int pos=0;
    for(int col=0;col<vexNum;col++){
        if(adjMatrix[row][col]!=INT_MAX&&row!=col){
            aEdge[pos].weight=adjMatrix[row][col];
            aEdge[pos].fVex=row;
            aEdge[pos].sVex=col;
            pos++;
        }
    }
    return pos;//返回有多少条这样的边
}

void graph::DFSTraverse2(int nVex, path* &pList){//深度搜索接口

}    
/**
 * nPath参数的作用是存储start到各个顶点最短路径
 * 实现方式是通过存储路径上的前一个结点，然后通过下标访问某个结点的前驱
 * 然后不断的向前知道起始点
 */
int graph::Dijkstra(int start,int end,vector<int>&nPath){//找到最短路径
    bool visited[vexNum]={false};
    visited[start]=true;//起始点start加入顶点集合（已访问）
    //初始化部分
    int dist[vexNum];
    for(int pos=0;pos<vexNum;pos++){
        dist[pos]=adjMatrix[start][pos];
        //如果非起始点到起始点有路径，则将起始点作为到当前结点的前驱
        if(start!=pos&&dist[pos]<INT_MAX){
            nPath[pos]=start;
        }
    }
    //正式开始
    int min=INT_MAX;
    int temp;
    for(int time=0;time<vexNum;time++){//共循环vexNum-1次 就是把剩下的结点加入
        min=INT_MAX;
        for(int pos=0;pos<vexNum;pos++){//扎到dist中最小的，即找相邻的结点最近的路径
            if(!visited[pos]&&dist[pos]<min){
                min=dist[pos];
                temp=pos;//记忆找到的下一个最近结点
            }
        }
        visited[temp]=true;
        for(int pos=0;pos<vexNum;pos++){
            //防止溢出
           int overflow=adjMatrix[temp][pos]==INT_MAX? INT_MAX:(dist[temp]+adjMatrix[temp][pos]);
            if(visited[pos]==false&&overflow<dist[pos]){
                dist[pos]=dist[temp]+adjMatrix[temp][pos];
                nPath[pos]=temp;//更新前驱
            }
        }
    }
    return dist[end];
}
int graph::Kruskal(vector<edge>&aPath){
    int cost=0;
    uSet uset(vexNum);
    vector<edge> edges;
    edge eTemp;
    //预处理  得到所有的边，然后按从小到大排序
    edges.assign(vexNum,edge());
    for(int row=0;row<vexNum;row++){
        for(int col=getFirstNeighbor(row);col>=0&&col<row;col=getNextNeighbor(row,col)){
            eTemp=getEdge(row,col);
            edges.push_back(eTemp);
        }
    }
    sort(edges.begin(),edges.end());//按权值大小  从小到大排序
    //正式 Kruskal   并查集真的太爽了
    for(auto it=edges.begin();it!=edges.end();it++){
        int root1=uset.unionsearch(it->fVex);
        int root2=uset.unionsearch(it->sVex);
        if(root1!=root2){
            cost+=it->weight;
            aPath.push_back(*it);
            uset.pre[root1]=root2;
        }
    }
    return cost;
}
int graph::prim(int first,vector<edge>& aPath){//找到最小生成树
    int cost=0;//最小生成树的权值之和
    uSet uset(vexNum);//并查集   在这里visited数组其实可以起到相同的作用
    priority_queue<edge> queue;
    edge eTemp;
    //初始时从图中任取一顶点，并将这顶点相邻的边保存在优先队列中
   for(int col=getFirstNeighbor(first);col>=0;col=getNextNeighbor(first,col)){
        edge aedge=getEdge(first,col);  
        queue.push(aedge);
    }
    while(!queue.empty()){
        eTemp=queue.top();//到了最后连续pop出来不在生成树里的边
        queue.pop();
        //这条边的目的结点是否在生成树的结点集合里
        //若用visited数组则要判断目的结点是否访问过即可
        if(uset.unionsearch(eTemp.sVex)!=first){//若不在
            cost+=eTemp.weight;
            aPath.push_back(eTemp);
            uset.pre[eTemp.sVex]=eTemp.fVex;//加入集合  visited设为true
            //以加入边的目标点作为新的开始
            for(int col=getFirstNeighbor(eTemp.sVex);col>=0;col=getNextNeighbor(eTemp.sVex,col)){
               if(first!=uset.unionsearch(col)){
                edge aedge=getEdge(eTemp.sVex,col);  
                queue.push(aedge);
               }
             }
        }
    }
    return cost;
}
void graph::DFSTraverse(int nVex){//深度搜索接口
    bool visited[SIZE]={false};
    for(int row=0;row<vexNum;row++){
        if(!visited[row]){//如果不是连通图，则有些顶点一次访问不到
            DFS(row,visited);
            //若有连通分量，则多行输出每个连通分量
            cout<<endl;
            //如果想得到某个顶点开始的连通分量，则不需要循环与判断
        }
    }
}
void graph::DFS(int vex,bool visited[]){
    cout<<vex<<" ";
    visited[vex]=true;
    for(int col=getFirstNeighbor(vex);col>=0;col=getNextNeighbor(vex,col)){
        if(!visited[col]){
            DFS(col,visited);
        }
    }
}
void graph::DFS_2(int vex,bool visited[],int index,path* &pList){

}
void graph::BFSTraverse(int vex){
    bool visited[SIZE]={false};
    queue<int> vexQueue;
    for(int row=0;row<vexNum;row++){
        if(!visited[row]){
            BFS(row,visited,vexQueue);
            cout<<endl;//分行输出每个连通分量
        }
    }
}
void graph::BFS(int vex,bool visited[],queue<int>& vexQueue){
    cout<<vex<<" ";
    visited[vex]=true;
    vexQueue.push(vex);
    while(!vexQueue.empty()){
        vex=vexQueue.front();
        vexQueue.pop();
        for(int col=getFirstNeighbor(vex);col>=0;col=getNextNeighbor(vex,col)){
             if(!visited[col]){
                cout<<col<<" ";
                visited[col]=true;
                vexQueue.push(col);
             }
        }
    }
}
//一层一层的递进  广度优先求阶单源最短路径问题，广度优先可以找到与目标点的最少层数也就是最少的路径数
int* graph::BFS_MIN_Distance(int level0){
    int *path=new int[vexNum];
    for(int pos=0;pos<vexNum;pos++){
        path[pos]=INT_MAX;
    }
    bool visited[vexNum]={false};
    path[level0]=0,visited[level0]=true;
    queue<int> vexQueue;
    vexQueue.push(level0);
    while(!vexQueue.empty()){
        level0=vexQueue.front();
        vexQueue.pop();
         for(int col=getFirstNeighbor(level0);col>=0;col=getNextNeighbor(level0,col)){
             if(!visited[col]){
                visited[col]=true;
                path[col]=path[level0]+1;
                vexQueue.push(col);
             }
        }
    }
    return path;
}
void createGraph(graph &agraph){
    ifstream File;
	char buffer[100];
	int vexnum;

	//set the graph vex
	File.open("D:/Vex.txt", ios::in);
	if (File) {
		File >> vexnum;
	    vertex vex;
		for (int i = 0; i < vexnum; i++) {
			File >> vex.num>> vex.name;
			agraph.insertVex(vex);
		}
		agraph.setVexNum(vexnum);
	}
	else {
		cout << "点信息存储文件打开失败！" << endl;
	}
	File.close();

	//set the graph edge
	File.open("D:/Edge.txt", ios::in);
	if (File) {
		while (!File.eof()) {
			edge edges;
			File >> edges.fVex >> edges.sVex >> edges.weight;
			agraph.insertEdge(edges);

		}
	}
	else {
		cout << "边存储文件打开失败！" << endl;
	}
	File.close();
}
int main(){
    graph agraph;
    createGraph(agraph);
    // int *path=new int[agraph.getVexNum()];
    // path=agraph.BFS_MIN_Distance(0);
    // for(int pos=0;pos<agraph.getVexNum();pos++){
    //     cout<<path[pos]<<" ";
    // }
    // cout<<endl;
    // agraph.DFSTraverse(0);
    //最小生成树两个算法的测试
    // vector<edge> minTree;
    // cout<<agraph.prim(0,minTree);
    // cout<<endl;
    // for(auto it=minTree.begin();it!=minTree.end();it++){
    //     cout<<it->weight<<" ";
    // }
    // cout<<endl;
    // minTree.clear();
    // cout<<agraph.Kruskal(minTree);
    // cout<<endl;
    // for(auto it=minTree.begin();it!=minTree.end();it++){
    //     cout<<it->weight<<" ";
    // }
    vector<int> path;
    path.assign(agraph.getVexNum(),0) ;
    cout<<agraph.Dijkstra(0,5,path)<<endl;
    int end=5;
    cout<<end<<" ";
    while(path[end]!=0){
        cout<<path[end]<<" ";
        end=path[end];
    }
    cout<<0;
    return 0; 
}