#include<iostream>
using namespace std;
//c++知识  
//int(*p)[MaxSize]  这是数组指针 即一个指针指向一个一维数组  也称为行指针

//顺序栈的实现
//操作有 判空  进栈  出栈  读栈顶元素
//初始top=0 则 top==size判断是否栈满  top==0栈空
//push stack[top++]=x     pop stack[--top]
#define MaxSize 50
// typedef struct{
//     int data[MaxSize];//栈
//     int top;//栈顶指针
// }SqStack;

struct SqStack{
    int *data;//栈   指针数组
    int top;//栈顶指针
    SqStack(){
        data=new int[MaxSize];   //不会初始化
        top=-1;
    }
};
//判栈空
bool StackEmpty(SqStack stack){
    if(stack.top==-1){
        return true; //isEmpty   是空的
    }
    return false;//not empty
}

//进栈
bool push(SqStack &stack,int elem){
    if(stack.top==MaxSize-1){
        cout<<"StackOverflow"<<endl;
        return false;  //
    }
    stack.data[++stack.top]=elem;
    return true;
}
bool pop(SqStack &stack,int &popElem){
    if(stack.top==-1){
        cout<<"stack is empty"<<endl;
        return false;
    }
    popElem=stack.data[stack.top--];
    return true;
}
bool getTop(SqStack stack,int &topElem){
    if(stack.top==-1){
        cout<<"stack is empty"<<endl;
        return false;
    }
    topElem=stack.data[stack.top];
    return true;
}
void show(SqStack stack){
    for(int i=0;i<stack.top+1;i++){
        cout<<stack.data[i]<<" ";
    }
    cout<<endl;
}

int main(){
    SqStack stack;
    for(int i=0;i<MaxSize;i++){
        push(stack,i);
    }
   //show(stack);
   int elem;
    for(int i=0;i<10;i++){
        pop(stack,elem);
        cout<<elem<<" ";
    }
    cout<<endl;
    show(stack);
    getTop(stack,elem);
    cout<<elem;
    return 0;
}