#include<iostream>
#include<assert.h>
using namespace std;
//c语言写法
// typedef struct LinkNode{
//     int val;
//     struct LinkNode *next;
// }*listStack;

struct linkNode{
    int val;
    linkNode* next;  //指针域
};

struct Stack{
    int count;
    linkNode* top;
    Stack(){
        count=0;
        top=nullptr;
    }
};

//Check empty stack
bool stackEmpty(Stack* stack){
    assert(stack);
   return stack->count==0;// true empty   false not empty
}

//Return size of the stack
int stackSize(Stack *stack){
    assert(stack);
    return stack->count;
}

//链头作为栈顶  添加删除都在栈顶
//将top后插到新的节点后面，然后将top指向头指针，top在头指针处
void push(Stack *stack,int elem){
    assert(stack);
    linkNode* newNode=new linkNode;

    newNode->val=elem;
    newNode->next=stack->top;
    stack->top=newNode;
    stack->count++;
}
//将top指向下一个节点，然后释放掉top即可
bool pop(Stack *stack,int &elem ){
    if(stack->count==0){
        cout<<"stack is empty,Underflow"<<endl;
        return false;
    }
    else{
        linkNode*del=stack->top;
        elem=stack->top->val;
        stack->top=stack->top->next;
        delete del;
        stack->count--;
        return true;
    }
}
int getTop(Stack* stack){
    return stack->top->val;
}
void show(Stack *stack){
    linkNode* temp=stack->top;
    while(temp!=nullptr){
        cout<<temp->val<<" ";
        temp=temp->next;
    }
    cout<<endl;
}


int main(){
    Stack stack;
    for(int i=0;i<20;i++){
        push(&stack,i);
    }
    show(&stack);
    cout<<stackSize(&stack)<<endl;

   int elem;
    for(int i=0;i<10;i++){
        pop(&stack,elem);
        cout<<elem<<" ";
    }
    cout<<endl;
    show(&stack);
    elem=getTop(&stack);
    cout<<elem<<endl;

    cout<<stackSize(&stack)<<endl;
    return 0;
}