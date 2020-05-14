#include<iostream>
#include<vector>
using namespace std;
void shellSort(int *array,int size){
    int temp;
    for(int dk=size/2;dk>=1;dk=dk/2){  //直到index为1为止
        for(int index=dk;index<size;index++){
            if(array[index]<array[index-dk]){ //如果后一个小于前一个，就需要进行插入
                temp=array[index];
                int coordinate;
                for(coordinate=index-dk;temp<array[coordinate]&&coordinate>=0;coordinate-=dk){//coordinate  坐标
                    array[coordinate+dk]=array[coordinate];
                }    
                array[coordinate+dk]=temp;
            }
        }
    }
}

//上面方法的间隔不是很好
vector<int> shellGap(int size){
    vector<int> gap;
    int h=1;
    while(h<n){
        gap.push_back(h);
        h=3*h+1;  //据研究这样得到的gap较好
    }
    
}
//通用插入方法
void insertionSort(int* array,int size,int gap){  //模块化更好一些
    int temp;
     for(int index=gap;index<size;index++){
            //如果后一个小于前一个，就需要进行插入
            temp=array[index];
            int coordinate=index-gap;
            while(coordinate>=0&&temp<array[coordinate]){
                array[coordinate+gap]=array[coordinate];
                coordinate-=gap;
            }
            array[coordinate+gap]=temp;
            
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
    shellSort(array,10);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}