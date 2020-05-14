#include<iostream>
using namespace std;
void heapAdjust(int *array,int root,int size);
void swap(int *array,int first,int second){
    int temp;
    temp=array[first];
    array[first]=array[second];
    array[second]=temp;
}
//建立大根堆
void buildHeap(int *array,int size){
    for(int index=size/2;index>=0;index--){//从最后一个有孩子的结点到根节点，反复调整堆
        heapAdjust(array,index,size);
    }
}
//调整堆
void heapAdjust(int *array,int root,int size){
    int temp=array[root];
    for(int index=root*2+1;index<size;index=index*2+1){
        if(index<size-1&&array[index]<array[index+1]){
            index++;//取值比较大的子节点的下标
        }
        if(temp>=array[index]){
            break;
        }
        else{
            array[root]=array[index]; //将array[index]调整到父节点上
            root=index;  //继续向下调整  因为第一次调整后，temp还是要和下面的比较大小
        }
    }
    array[root]=temp; //上面都调整了。
}
void heapSort(int *array,int size){
    buildHeap(array,size);
    for(int index=size-1;index>=0;index--){
        cout<<array[0]<<" "; //先输出堆顶元素
        swap(array,index,0); //堆顶和堆低元素交换
        heapAdjust(array,0,index);//调整堆 ** 每次的size减小  所以用index  
    }
}
int main(){
    int array[8]={53,17,78,9,45,65,87,32};
    for(int index=0;index<8;index++){
        printf("%d ",array[index]);
    }
    cout<<endl;
    heapSort(array,8);
    //buildHeap(array,8);
    cout<<endl;
    for(int index=0;index<8;index++){
        printf("%d ",array[index]);
    }
    return 0;
}