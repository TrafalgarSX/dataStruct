#include<iostream>
using namespace std;
/**
 * 并查集的实现
 * 并查集由一个整型数组和两个函数组成。数组pre[]记录了每个点的前导点是什么
 * find函数是查找  join和合并
 */
#define SIZE 100
class uSet
{

public:
    int pre[SIZE];
    uSet(int num);
    ~uSet();
    int unionsearch(int root);
    void join(int root1,int root2);
};

uSet::uSet(int num)
{
    for(int pos=0;pos<num;pos++){
        pre[pos]=pos;
    }
}

uSet::~uSet()
{
}
int uSet::unionsearch(int root){//查找根结点，最上层的人
    int son,temp;
    son=root;
    while(root!=pre[root]){//如果自己不是最上级
       root=pre[root];//找到root的最上级
    }
    while ((son!=root))//
    {//路径压缩
        /* 先找到son的上级保存，然后将son的上级设为root，
        最后将son变为它的上级，知道son变成最上级
         */
        temp=pre[son];
        pre[son]=root;
        son=temp;
    }
    return root;
}
void uSet::join(int elem1,int elem2 ){
    int root1,root2;
    root1=unionsearch(elem1);//找到元素的父节点，顶头上司
    root2=unionsearch(elem2);
    if(root1!=root2){
        pre[root1]=root2;//将root1并入root2
    }
}
#undef SIZE