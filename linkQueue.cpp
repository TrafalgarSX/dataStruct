#include<iostream>
using namespace std;
//rear指向队列的最后一个元素  front就是队列的头结点
//因为不带头结点的队列比较麻烦
//出队操作，如果最后一个节点要将rear和front都置为空，否则摘除一个，front指向下一个
//入队操作不统一，如果空队列就创建一个节点即可，如果不是空，就要创建一个节点然后链接

/*
带了头结点的话
 出队：摘除头结点（front）后一个节点，如果最后一个节点将 rear=front
 入队：建立新节点往rear指针后链接就行了
*/

/*
  双端队列：只允许从两端插入，两端删除的线性表
  输入受限的双端队列：只允许从一端插入、两端删除的线性表
  输出受限的双端队列：只允许从两端插入、一端删除的线性表
  **在栈中合法的输出序列，在双端队列中必定合法
*/
struct linkNode{
    int elem=0;
    linkNode* next=nullptr;
};  
struct linkQueue{
    linkNode* front,*rear;
    linkQueue(){//带头结点初始化队列
        front=rear=new linkNode;//建立头结点
        front->next=nullptr;
    }
};
bool isEmpty(linkQueue queue){
    if(queue.front==queue.rear){
        return true;
    }
    return false;
}
void EnQueue(linkQueue &queue,int elem){
    linkNode* newNode=new linkNode;
    newNode->elem=elem;
    newNode->next=nullptr;
    queue.rear->next=newNode;
    queue.rear=newNode;//修改尾指针
}
bool DeQueue(linkQueue &queue,int &elem){
    if(queue.rear==queue.front){
        cout<<"queue is empty"<<endl;
        return false;
    }

    linkNode* temp;
    temp=queue.front->next;
    elem=temp->elem;
    queue.front->next=temp->next;
    if(queue.rear==temp){//如果出队的是尾结点 即出对后队列为空的话
        queue.rear=queue.front;
    }
    delete temp;
    return true;
}

void show(linkQueue queue){
    linkNode*temp=queue.front->next;
    while(temp!=nullptr){
        cout<<temp->elem<<" ";
        temp=temp->next;
    }
    cout<<endl;
}

int getHead(linkQueue queue){
       if(queue.front==queue.rear){
        cout<<"queue is underflow"<<endl;
        return false;
    }
    return queue.front->next->elem;
}

int main(){
    linkQueue queue;
    for(int i=0;i<20;i++){
        EnQueue(queue,i);
    }
    show(queue);
   // cout<<QueueSize(queue)<<endl;

   int elem;
    for(int i=0;i<10;i++){
        DeQueue(queue,elem);
        cout<<elem<<" ";
    }
    cout<<endl;
    show(queue);
    elem=getHead(queue);
    cout<<elem<<endl;

   // cout<<QueueSize(queue)<<endl;
    return 0;
}