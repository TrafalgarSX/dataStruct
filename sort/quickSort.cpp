#include<iostream>
using namespace std;
int Partition(int*array,int low,int high){
    int pivot=array[low];//第一个作为基准
    while(low<high){
        while(array[high]>=pivot&&high>low) high--; 
        array[low]=array[high];
        while(array[low]<=pivot&&high>low) low++;
        array[high]=array[low];
    }
    array[low]=pivot;
    return low;
}
//快速排序算法是递归的，是基于分治法的
void quickSort(int *array,int low,int high){
    if(low<high){
        int pivot=Partition(array,low,high);
        quickSort(array,low,pivot-1);
        quickSort(array,pivot+1,high);
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
    quickSort(array,0,9);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}