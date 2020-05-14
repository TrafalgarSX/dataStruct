#include<iostream>
using namespace std;
/*
  插入类排序的思想是通过构建有序序列，对未排序数据进行
折半查找，并找到相应的位置插入。
*/
void binaryInsertionSort(int*array,int size){
    int low,high,mid,temp;
    for(int index=1;index<size;index++){
        low=0;
        high=index-1;
        temp=array[index];
        while(low<=high){ //二分查找，查找适合的插入位置
        /*
        最后都会回到low=high时，该元素（array[low]）与temp的大小关系
        然后就是low=mid+1：temp大，所以
        high-1：temp小，所以low以后往后移
        最终low标识插入位置
        */
            mid=(low+high)/2;
            if(array[index]<array[mid]){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        for(int coordinate=index;coordinate>low;coordinate--){
            array[coordinate]=array[coordinate-1];
        }
        array[low]=temp;
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
    binaryInsertionSort(array,10);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}