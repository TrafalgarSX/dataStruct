#include<iostream>
using namespace std;
void swap(int *array,int first,int second){
    int temp;
    temp=array[first];
    array[first]=array[second];
    array[second]=temp;
}
void selectSort_1(int *array,int size){
    int min,flag;
    for(int index=0;index<size;index++){
        min=INT_MAX;
        for(int coordinate=index;coordinate<size;coordinate++){
            if(array[coordinate]<min){
                min=array[coordinate];
                flag=coordinate;
            }
        }
        swap(array,flag,index);
    }
}
//上一个不是很简便 用了两个额外变量  这个只需要一个
void selectSort_2(int* array,int size){
    for(int index=0;index<size;index++){
        int min=index;
        for(int coordinate=index;coordinate<size;coordinate++){
            if(array[coordinate]<array[min]){
                min=coordinate;
            }
        }
        swap(array,index,min);
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
    selectSort_2(array,10);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}