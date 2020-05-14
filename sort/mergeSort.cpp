#include<iostream>
using namespace std;
 int*temp=new int(10); //辅助数组 和原来的一样大
void Merge(int*array,int low,int high,int mid){
    for(int index=low;index<=high;index++){
        temp[index]=array[index];
    }
    int i,j,index;
    for(i=low,j=mid+1,index=i;i<=mid&&j<=high;index++){
        if(temp[i]<temp[j]){
            array[index]=temp[i];
            i++;
        }
        else{
            array[index]=temp[j];
            j++;
        }
    }
    while(i<=mid) array[index++]=temp[i++];
    while(j<=high) array[index++]=temp[j++];
}
//归并排序也是递归的 自顶向下二分  然后自顶向上归并
void mergeSort(int *array,int low,int high){
    //对于两个以上的才进行merge，两个及两个以下就不需要进行
    if(low <high){
        int mid=(low+high)/2;
        mergeSort(array ,low,mid);
        mergeSort(array,mid+1,high);
        Merge(array,low,high,mid);
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
    mergeSort(array,0,9);
    for(int index=0;index<10;index++){
        printf("%d ",array[index]);
    }
    return 0;
}