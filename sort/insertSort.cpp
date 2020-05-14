#include<iostream>
using namespace std;
/**
 * 插入排序
 */ 
void insertSort(int* array,int size){
    int temp;
    for(int index=1;index<size;index++){
        if(array[index]<array[index-1]){  //如果后一个小于前一个就要插入，否则就是正序的
            temp=array[index];
            int coordinate;
            for(coordinate=index-1;temp<array[coordinate]&&coordinate>=0;coordinate--){//coordinate  坐标
                   array[coordinate+1]=array[coordinate];
            }    
            array[coordinate+1]=temp;
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
    insertSort(array,10);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}