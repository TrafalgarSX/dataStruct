#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
#define MaxSize 50
class Person{
public:
    string name;
    int age=0;
    bool operator ==(const Person &person) const{
        //不用this->也可以
        return person.name==this->name&&person.age==this->age;
    }
};

typedef struct{
    Person data[MaxSize];
    int length=0;//如果不初始化不会赋值
}SqlList;//静态分配
typedef struct{
    Person *data;
    int maxSize,length;
}SeqList;//动态分配   以下是两种动态分配语句
//L.data=(Person*)malloc(sizeof(Person)*InitSize)
//L.data=new Person[InitSize];

//插入操作   locate 是位序
bool ListInsert(SqlList &list,int locate,Person person){
    //因为这是插入操作，所以 可插入位置是1--list.length+1
    if(locate<1||locate>list.length+1){
        return false;
    }
    if(list.length>=MaxSize){//必须有可以插入的位置所以length<MaxSize
        return false;
    }
    //locate是位序  比数组相应位置的坐标要大 1 所以是i>=locate 可以等于
    for(int i=list.length;i>=locate;i--){
        list.data[i]=list.data[i-1];//往后移动一位
    }
    list.data[locate-1]=person;
    list.length++;
    return true;
}
//person是引用类型是因为要将被删除的数据返回
bool ListDelete(SqlList &list,int locate,Person &person){
    //删除必须在有的位置种删除
    if(locate<1||locate>list.length){
        return false;
    }
    person=list.data[locate-1];//将被删除的元素返回
    for(int i=locate-1;i<list.length;i++){
        list.data[i]=list.data[i+1];//往前移动一位
    }
    list.length--;
    return true;
}
//查找  返回位序
int LocateElem(SqlList list,Person person){
    for(int i=0;i<list.length;i++){
        if(list.data[i]==person){
            return i+1;//返回的是位序，所以要加一
        }
    }
    return 0;
}
//根据位序查找数据
Person GetElem(SqlList list,int locate){
    if(locate<1||locate>list.length){
        printf("顺序表中没有此位序");
        Person person;
        person.name="没有";
        person.age=0;
        return person;
    }
    return list.data[locate-1];
}
//打印
void printList(SqlList list){
    for(int i=0;i<list.length;i++){
        printf("%s 的年龄是： %d\n",list.data[i].name.c_str(),list.data[i].age);
    }
}

int main(){
    SqlList list;
    Person person;
    person.age=21;
    person.name="boss-guo";
    ListInsert(list,1,person);
    person.name="张超杰";
    ListInsert(list,2,person);
    person.name="吴涛";
    ListInsert(list,3,person);

    printList(list);
    person.name="褚志刚";
    ListInsert(list,1,person);
    printList(list);
    cout<<endl;

    ListDelete(list,2,person);
    ListDelete(list,1,person);
    cout<<person.name<<"的年龄是"<<person.age<<endl<<endl;
    printList(list);
    cout<<GetElem(list,2).name<<endl;
    person.name="吴涛";
    cout<<LocateElem(list,person);
    return 0;

}