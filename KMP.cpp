#include<iostream>
using namespace std;
//**部分匹配值：字符串的前缀和后缀的最长相等前后缀长度
/*knuth_morris_pratt算法的重点在于 如何得到部分匹配值的表
* 这个表是子串匹配回退的坐标。
*/
//变量要有实际意义，没有实际意义的变量都是屎，屎一样的代码
int* get_nextval(string pattern){
    size_t patSize=pattern.size();
    int *nextval=new int[patSize];

    nextval[0]=-1;
    int pre=-1,suf=0;
    while(suf<patSize-1){
        if(pre==-1||pattern[pre]==pattern[suf]){
           ++pre;
           ++suf;
           if(pattern[pre]!=pattern[suf]){
               nextval[suf]=pre;
           }
            else{
                nextval[suf]=nextval[pre];
            }
        }
        else{
            pre=nextval[pre];
        }
    }
    return nextval;
}
int* get_next(string pattern){
   size_t patSize=pattern.size();
    int *next=new int[patSize];

    next[0]=-1;
    int pre=-1,suf=0; //前缀  后缀 suffix 初始前缀在后缀的前一个位置
    while(suf<patSize-1){//第一个已经填过了，所以减一（数组长度-1）
        //pattern[pre]表示前缀   pattern[suf]表示后缀

        //***自我匹配，对自己进行匹配（主串、子串都是自己）就是寻找相同前后缀最长（部分匹配串） 
        //**suf是作为主串的后缀，逐渐增加
        //**pre作为前缀，来寻找和主串后缀相等的，若相等，pre进一步增加，不等就回到前面找短一点的相同前缀后缀
        if(pre==-1||pattern[pre]==pattern[suf]){
           ++pre;
           ++suf;
           next[suf]=pre;//这个=pre就是 pre最长相等前后缀 没有加一是因为数组从0开始 
        }
        else{
            pre=next[pre];
        }
    }
    return next;
}
int Index_KMP(string text,string pattern,int *nextval){
    int patSize=pattern.length();
    int textSize=text.length();
    int patp=0,textp=0;
    while(textp<textSize&& (patp<patSize)){
        if(patp==-1||text[textp]==pattern[patp]){
            textp++;
            patp++;
        }
        else{
            patp=nextval[patp];
        }
    }
    if(patp==patSize){
        return textp-patSize;
    }
    return -1;
}

int main(){
    string text="this is china";
    string pattern="a";
    int *next=new int[pattern.size()];
    next=get_next(pattern);
    for(int i=0;i<pattern.size();i++){
        cout<<next[i]<<" ";
    }
    cout<<endl;
    cout<<Index_KMP(text,pattern,next);
    return 0;
}