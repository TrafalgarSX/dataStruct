#include<iostream>
using namespace std;

void BubbleSort(int *array,int size){
    for(int i=0;i<size;i++){ //这个其实没什么用，就是循环够n-1次就可以了
        for(int j=size-1;j>i;j--){ //j>i 这个条件可以减少比较次数 也可以用j>0
            if(array[j-1]>array[j]){  //把最小给冒上去
                int temp;
                temp=array[j];
                array[j]=array[j-1];
                array[j-1]=temp;
            }
        }
    }
}

int main(){
    int *array=new int(10);
    int count=10;
    for(int index=0;index<10;index++){
        array[index]=count--;
        printf("%d ",array[index]);
    }
    cout<<endl;
    BubbleSort(array,10);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}