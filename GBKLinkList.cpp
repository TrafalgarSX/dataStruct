#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
int listLength=0;
class Person{
public:
    string name;
    int age=0;
    bool operator ==(const Person &person) const{
        //不用this->也可以
        return person.name==this->name&&person.age==this->age;
    }
    bool operator !=(const Person &person) const{
        return person.name!=name||person.age!=age;
    }
};
typedef struct Node{//单链表结点类型
    Person person;
    struct Node *next;
}Node,*linkList;//定义结构类型，别名

//按序查找
Node* GetElem(linkList list,int locate){
    // Node*强调返回的是一个结点，linkList强调是一个单链表
    int count=1; //从第一个结点开始
    Node*current=list->next; //头结点的下一个  current头指针
    if(locate==0){
        return list;//如果第0个，返回头结点
    }
    if(locate<1)  return nullptr;//如果无效，返回空
    while(current&&count<locate){//查找第locate个结点
        current=current->next; //如果找的是超过length的结点，current会为空
        count++;
    }
    return current;
}
//按值查找
Node * locateElem(linkList list,Person person){
    Node* current=list->next;
    while(current&&current->person!=person){
        current=current->next;
    }
    return current;
}

Person createPerson(){
    Person person;
    cout<<"请输入人名：";
    cin>>person.name;
    cout<<endl<<"请输入年龄：";
    cin>>person.age;
    return person;

}
//头插法创建带头结点的链表   逆向建立  可用来逆置单链表
linkList list_headInsert(linkList &list){
    Node *current;
    char isContinue='y';
    Person person;
    list=new Node;//创建头结点
    list->next=nullptr;// 初始为空链表  不写可能导致尾结点不知道指向哪里
    while(isContinue=='y'){
        person=createPerson();
        //后插操作  重复代码  InsertNextNode（）
        current=new Node;
        current->person=person;
        current->next=list->next;
        list->next=current;
        listLength++;
        cout<<"继续进行输入?y/n"<<endl;
        cin>>isContinue;
    }
    return list;  //返回链表的头结点
}
//用尾插法创建带头结点的链表  正向
linkList list_tailInsert(linkList &list){
    list=new Node;//创建头结点
    char isContinue='y';
    //在使用指针之前要初始化   比如list要使用就要初始化
    //如果没有初始化就使用，tail会是list未初始化指向的地址，然后list分配内存初始化后，地址就变了，而tail还不变
    Node *current,*tail=list;
    Person person;
    while(isContinue=='y'){
        person=createPerson();
        current=new Node;//(Node*)malloc(sizeof(Node));
        current->person=person;
        tail->next=current;
        tail=current;
        listLength++;
        cout<<"继续进行输入?y/n"<<endl;
        cin>>isContinue;
    }
    tail->next=nullptr;
    return list;
}
//初始化一个带头结点的单链表  用这个不能用前两个头插法和尾插法
bool InitList(linkList &list){
    list=new Node;//(Node*)malloc(sizeof(Node));//创建头结点
    if(list) return false;  //内存不足创建失败
    list->next=nullptr; //还没有头指针
    return true;
}


//指定节点后插操作
bool InsertNextNode(Node *current,Person person){
    if(current==nullptr){//传入的额可能是空指针
        return false;
    }
    Node* newNode=new Node;//(Node*)malloc(sizeof(Node));
    if(newNode==nullptr){
        return false;//如果分配失败
    }
    newNode->person=person;
    newNode->next=current->next;
    current->next=newNode;
    listLength++;
    return true;
}
//插入结点操作  指定结点后插
bool ListInsert(linkList &list,int locate,Person person){
    Node *current;
    if(locate<1) return false; //locate不能小于1
    current=GetElem(list,locate-1);//找到前一个结点
    listLength++;
    return InsertNextNode(current,person);//重复代码
    // if(current){ //locate不合法  过大
    //     return false;
    // }
    // newNode=(Node*)malloc(sizeof(Node));
    // newNode->person=person;
    // newNode->next=current->next;
    // current->next=newNode;
    // return true;
}
//指定结点前插操作   后插入后交换内容方法  王道书的参数是两个结点
bool InsertPriorNode(Node* current,Person person){
    if(current==nullptr){
        return false;
    }
    Node* newNode=new Node;//(Node*)malloc(sizeof(Node));
    if(newNode==nullptr){
        return false;
    }
    newNode->next=current->next;
    current->next=newNode; //这两步将新节点链接进入链表
    newNode->person=current->person;//交换两节点的内容
    current->person=person;
    listLength++;
    return true;
}
//指定结点前插，普通方法  循环查找前驱结点，然后后插  代码略

//指定结点删除  覆盖后释放
bool DeleteNode(Node* current){
    if(current==nullptr){
        return false;
    }
    //当要删除最后一个节点时有bug  
    Node* nextNode; //用nextNode覆盖前一个然后释放nextNode
    nextNode=current->next;
    //当删除最后一个节点时，只能从表头开始寻找前驱结点进行删除
    if(nextNode==nullptr){
        //这里应该调用顺序查找删除的方法
        return false;
    }
    current->person=nextNode->person;
    current->next=nextNode->next;
    delete nextNode;//free(nextNode);
    listLength--;
    return true;
}

//按位序删除  带头结点  &person 要返回删除的数据
bool ListDelete(linkList &list,int locate,Person &person){
    Node* current;
    if(locate<1) return false; //locate不能小于1
    current=GetElem(list,locate-1);//找到前一个结点
    if(current==nullptr){
        return false;
    }
    //要确保要删除的是个结点，不是空指针
    if(current->next==nullptr){
        return false;
    }
    Node* deleteNode=current->next;
    person=deleteNode->person;
    current->next=deleteNode->next;
    delete deleteNode;// free(deleteNode);
    listLength--;
    return true;
}
void printList(linkList list){
    Node* current=list->next;
    while(current){
        cout<<current->person.name<<"的年龄是："<<current->person.age<<endl;
        current=current->next;
    }
}
int main(){
    linkList headlist,taillist;
    //list_headInsert(headlist);
    list_tailInsert(taillist);
    //printList(headlist);
    cout<<endl;
    printList(taillist);
    Node* current;
    // //按序查询  ok好了
    // current=GetElem(taillist,3);
    // cout<<current->person.name<<endl;
    // Person person;
    // person.age=4;
    // person.name="4";
    // //按值查询 //ok 好了
    // current=locateElem(taillist,person);
    // cout<<current->person.name<<endl;
    Person person;
    person.age=0;
    person.name="0";
    //指定结点后的插入操作
    InsertNextNode(taillist,person);
    person.age=5;
    person.name="5";
    ListInsert(taillist,6,person);
    person.age=1.5;
    person.name="1.5";
    InsertPriorNode(taillist->next->next,person);
    cout<<endl;
    printList(taillist);
    cout<<endl;
    
    ListDelete(taillist,3,person);
    cout<<person.name<<person.age<<endl;
    DeleteNode(taillist->next->next->next);
    printList(taillist);
    return 0;
}