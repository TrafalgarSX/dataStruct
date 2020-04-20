#include<iostream>
#include<string>
#include<vector>
using namespace std;

/**
 *@param text Any string that might contain the pattern 
 *@param pattern String that we are searching the pattern
 */
int brute_force(string text,string pattern){
    size_t patSize=pattern.length();
    size_t textSize=text.length();
    int  index=-1;
    if(patSize<=textSize){
        for(int i=0;i<textSize-patSize+1;i++){
            string temp=text.substr(i,patSize);
            if(pattern==temp){
                index=i;
                break;
            }
        }
    }
    return index;
}
int brute_force_2(string text,string pattern){
    size_t patSize=pattern.length();
    size_t textSize=text.length();
    int pati=0,textj=0;
    //如果匹配成功 pati==patsize,textj会在匹配字串的后一位
    //如果匹配失败，textj==textSize
    while(pati<patSize&&textj<textSize){
        if(text[textj]==pattern[pati]){
            pati++;textj++;
        }
        else{
            pati=0;
            textj=textj-pati+1;
        }
    }
    if(pati==patSize){
        return textj-patSize;
    }
    return -1;
}
int main(){
    string text="this is china";
    string pattern="china";
    cout<<brute_force(text,pattern)<<endl;
    cout<<brute_force_2(text,pattern)<<endl;
    return 0;
}