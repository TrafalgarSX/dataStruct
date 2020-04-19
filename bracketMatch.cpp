#include<iostream>
#include<stack>
#include<string>
using namespace std;
bool bracketMatch(char bracket[],int length){
    stack<char>  assist;//辅助的意思
    for(int i=0;i<length;i++){
        if(bracket[i]=='('||bracket[i]=='['||bracket[i]=='{'){
            assist.push(bracket[i]);
        }
        else{
            if(assist.empty()){
                return false;
            }
            char topElem;
            topElem=assist.top();
            assist.pop();
           if(bracket[i]==')'&&topElem!='('){
               return false;
           }
           if(bracket[i]==']'&&topElem!='['){
               return false;
           }
           if(bracket[i]=='}'&&topElem!='{'){
               return false;
           }
        }
    }
    return assist.empty();//assist.empty();//若栈空则成功匹配，否则失败
}

int main(){
    char bracket[]="(((({{[{}]}})))";
    cout<<bracketMatch(bracket,15);
    return 0;
}