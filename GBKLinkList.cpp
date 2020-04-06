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
        //����this->Ҳ����
        return person.name==this->name&&person.age==this->age;
    }
    bool operator !=(const Person &person) const{
        return person.name!=name||person.age!=age;
    }
};
typedef struct Node{//������������
    Person person;
    struct Node *next;
}Node,*linkList;//����ṹ���ͣ�����

//�������
Node* GetElem(linkList list,int locate){
    // Node*ǿ�����ص���һ����㣬linkListǿ����һ��������
    int count=1; //�ӵ�һ����㿪ʼ
    Node*current=list->next; //ͷ������һ��  currentͷָ��
    if(locate==0){
        return list;//�����0��������ͷ���
    }
    if(locate<1)  return nullptr;//�����Ч�����ؿ�
    while(current&&count<locate){//���ҵ�locate�����
        current=current->next; //����ҵ��ǳ���length�Ľ�㣬current��Ϊ��
        count++;
    }
    return current;
}
//��ֵ����
Node * locateElem(linkList list,Person person){
    Node* current=list->next;
    while(current&&current->person!=person){
        current=current->next;
    }
    return current;
}

Person createPerson(){
    Person person;
    cout<<"������������";
    cin>>person.name;
    cout<<endl<<"���������䣺";
    cin>>person.age;
    return person;

}
//ͷ�巨������ͷ��������   ������  ���������õ�����
linkList list_headInsert(linkList &list){
    Node *current;
    char isContinue='y';
    Person person;
    list=new Node;//����ͷ���
    list->next=nullptr;// ��ʼΪ������  ��д���ܵ���β��㲻֪��ָ������
    while(isContinue=='y'){
        person=createPerson();
        //������  �ظ�����  InsertNextNode����
        current=new Node;
        current->person=person;
        current->next=list->next;
        list->next=current;
        listLength++;
        cout<<"������������?y/n"<<endl;
        cin>>isContinue;
    }
    return list;  //���������ͷ���
}
//��β�巨������ͷ��������  ����
linkList list_tailInsert(linkList &list){
    list=new Node;//����ͷ���
    char isContinue='y';
    //��ʹ��ָ��֮ǰҪ��ʼ��   ����listҪʹ�þ�Ҫ��ʼ��
    //���û�г�ʼ����ʹ�ã�tail����listδ��ʼ��ָ��ĵ�ַ��Ȼ��list�����ڴ��ʼ���󣬵�ַ�ͱ��ˣ���tail������
    Node *current,*tail=list;
    Person person;
    while(isContinue=='y'){
        person=createPerson();
        current=new Node;//(Node*)malloc(sizeof(Node));
        current->person=person;
        tail->next=current;
        tail=current;
        listLength++;
        cout<<"������������?y/n"<<endl;
        cin>>isContinue;
    }
    tail->next=nullptr;
    return list;
}
//��ʼ��һ����ͷ���ĵ�����  �����������ǰ����ͷ�巨��β�巨
bool InitList(linkList &list){
    list=new Node;//(Node*)malloc(sizeof(Node));//����ͷ���
    if(list) return false;  //�ڴ治�㴴��ʧ��
    list->next=nullptr; //��û��ͷָ��
    return true;
}


//ָ���ڵ������
bool InsertNextNode(Node *current,Person person){
    if(current==nullptr){//����Ķ�����ǿ�ָ��
        return false;
    }
    Node* newNode=new Node;//(Node*)malloc(sizeof(Node));
    if(newNode==nullptr){
        return false;//�������ʧ��
    }
    newNode->person=person;
    newNode->next=current->next;
    current->next=newNode;
    listLength++;
    return true;
}
//���������  ָ�������
bool ListInsert(linkList &list,int locate,Person person){
    Node *current;
    if(locate<1) return false; //locate����С��1
    current=GetElem(list,locate-1);//�ҵ�ǰһ�����
    listLength++;
    return InsertNextNode(current,person);//�ظ�����
    // if(current){ //locate���Ϸ�  ����
    //     return false;
    // }
    // newNode=(Node*)malloc(sizeof(Node));
    // newNode->person=person;
    // newNode->next=current->next;
    // current->next=newNode;
    // return true;
}
//ָ�����ǰ�����   �����󽻻����ݷ���  ������Ĳ������������
bool InsertPriorNode(Node* current,Person person){
    if(current==nullptr){
        return false;
    }
    Node* newNode=new Node;//(Node*)malloc(sizeof(Node));
    if(newNode==nullptr){
        return false;
    }
    newNode->next=current->next;
    current->next=newNode; //���������½ڵ����ӽ�������
    newNode->person=current->person;//�������ڵ������
    current->person=person;
    listLength++;
    return true;
}
//ָ�����ǰ�壬��ͨ����  ѭ������ǰ����㣬Ȼ����  ������

//ָ�����ɾ��  ���Ǻ��ͷ�
bool DeleteNode(Node* current){
    if(current==nullptr){
        return false;
    }
    //��Ҫɾ�����һ���ڵ�ʱ��bug  
    Node* nextNode; //��nextNode����ǰһ��Ȼ���ͷ�nextNode
    nextNode=current->next;
    //��ɾ�����һ���ڵ�ʱ��ֻ�ܴӱ�ͷ��ʼѰ��ǰ��������ɾ��
    if(nextNode==nullptr){
        //����Ӧ�õ���˳�����ɾ���ķ���
        return false;
    }
    current->person=nextNode->person;
    current->next=nextNode->next;
    delete nextNode;//free(nextNode);
    listLength--;
    return true;
}

//��λ��ɾ��  ��ͷ���  &person Ҫ����ɾ��������
bool ListDelete(linkList &list,int locate,Person &person){
    Node* current;
    if(locate<1) return false; //locate����С��1
    current=GetElem(list,locate-1);//�ҵ�ǰһ�����
    if(current==nullptr){
        return false;
    }
    //Ҫȷ��Ҫɾ�����Ǹ���㣬���ǿ�ָ��
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
        cout<<current->person.name<<"�������ǣ�"<<current->person.age<<endl;
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
    // //�����ѯ  ok����
    // current=GetElem(taillist,3);
    // cout<<current->person.name<<endl;
    // Person person;
    // person.age=4;
    // person.name="4";
    // //��ֵ��ѯ //ok ����
    // current=locateElem(taillist,person);
    // cout<<current->person.name<<endl;
    Person person;
    person.age=0;
    person.name="0";
    //ָ������Ĳ������
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