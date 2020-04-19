#include<iostream>
#include<stdio.h>
using namespace std;
//循环队列 操作受限的线性表  一端删除一端添加
//操作  入队  出队  读对头元素  判空队列  销毁队列
//队头删除  队尾添加

/*循环队列知识总结：
前提 ：rear指向的是队尾元素的下一个
    若牺牲一个存储单元： 
     判定队满的条件是 (queue.rear+1)%MaxSize==queue.front
     判定队空的条件是 rear==front
    这种情况队列元素个数为(rear+MaxSize-front)%MaxSize
     个数的算法其实就是rear-front  
    但是循环队列有可能rear-front<0所以加了个MaxSize取余

    若要求不能牺牲空间：
    1.加一个队列的大小的变量   queue.size 初始为0
    队 满条件  size==MaxSize   
    队空条件  size=0

    队列元素个数(rear+MaxSize-front)%MaxSize
    tag初始化0
    删除成功时 tag=0  插入成功时  tag=1
    队满条件front==rear&& tag=1
    队空条件front==rear&&tag=0

前提：若队尾指针指向队尾元素
    **两者初始化不同，该前提下rear=MaxSize-1 front=0

     当入队时（入队操作有差异）
     先指针后移 rear=(rear+1)%maxsize 后赋值  data[rear]=elem
    当出队时 elem=data[front]  front=front+1)%MaxSize (这个和上面一样)

    两种方案；
    方案一：牺牲一个存储单元
    判断队空(rear+1)%MaxSize==front
    判断队满  (rear+2)%MaxSize==front
    方案二：增加一个tag
    判断队空 (rear+1)%MaxSize==front&&tag=0
    判断队满 (rear+1)%MaxSize==front&&tag=0
*/
#define MaxSize 50
struct SqQueue{
    int *data;  //数组
    int front,rear;//头尾指针
    int tag;//辅助标记  辅助判断队列是否空/满
    SqQueue(){
        data=new int[MaxSize];
        front=rear=0;//rear 后方的 rear指向队尾元素或者指向队尾元素的下一个
    }
};

bool isEmpty(SqQueue queue){
    if(queue.rear==queue.front&&queue.tag==0){
        return true;
    }
    return false;
}

bool EnQueue(SqQueue &queue,int elem){
    if(queue.rear==queue.front&&queue.tag==1){
        cout<<"queue is overflow"<<endl;
        return false;
    }
    queue.data[queue.rear]=elem;
    queue.rear=(queue.rear+1)%MaxSize;//循环队列  队尾指针加一取模
    queue.tag=1;
    return true;
}

bool DeQueue(SqQueue& queue,int &elem){
    if(queue.rear==queue.front&&queue.tag==0){//  is empty
        cout<<"Queue is empty"<<endl;
        return false;
    }
    elem=queue.data[queue.front];
    queue.front=(queue.front+1)%MaxSize;//对头指针后移
    queue.tag=0;
    return true;
}

int getHead(SqQueue queue){
    if(queue.front==queue.rear&&queue.tag==0){
        cout<<"queue is underflow"<<endl;
        return false;
    }
    return queue.data[queue.front];
}

void show(SqQueue queue){
    for(int i=queue.front;i<queue.rear;i=(i+1)%MaxSize){
        cout<<queue.data[i]<<" ";
    }
    cout<<endl;
}

int QueueSize(SqQueue queue){
    return (queue.rear-queue.front+MaxSize)%MaxSize;
}

int main(){
    SqQueue queue;
    for(int i=0;i<20;i++){
        EnQueue(queue,i);
    }
    show(queue);
    cout<<QueueSize(queue)<<endl;

   int elem;
    for(int i=0;i<10;i++){
        DeQueue(queue,elem);
        cout<<elem<<" ";
    }
    cout<<endl;
    show(queue);
    elem=getHead(queue);
    cout<<elem<<endl;

    cout<<QueueSize(queue)<<endl;
    return 0;
}


