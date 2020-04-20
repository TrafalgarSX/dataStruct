#include<iostream>
#include<stack>
using namespace std;
//二叉排序树  左子树上的所有结点均小于根结点的值
//右子树均大于
struct treeNode
{
    /* data */
    int elem;
    treeNode *leftChild,*rightChild;    
    treeNode(){
        leftChild=nullptr;
        rightChild=nullptr;
        elem=0;
    }
};

treeNode* BSTsearch(treeNode* root,int key){
    while(root&&key!=root->elem){
        if(root->elem>key){
            root=root->leftChild;
        }
        else{
            root=root->rightChild;
        }
    }
    return root;
}
bool BSTinsert(treeNode*& root,int key){
        if(root==nullptr){
            root=new treeNode;
            root->elem=key;
            return true;//插入成功
        }
        else if(root->elem==key){
            return false;
        }
        else if(root->elem>key){
            BSTinsert(root->leftChild,key);
        }
        else{
            BSTinsert(root->rightChild,key);
        }

}
void create_BST(treeNode*& root,int *array,int arraySize){
        root=nullptr;
        int pos=0;
        while(pos<arraySize){
            BSTinsert(root,array[pos]);
            pos++;
        }
}


void inOrder(treeNode* root){
    if(root==nullptr) return ;
    stack<treeNode*> nodeStack;
    while(root!=nullptr||!nodeStack.empty()){
        if(root){
            nodeStack.push(root);
            root=root->leftChild;
        }
        else{
            root=nodeStack.top();
            nodeStack.pop();
            cout<<root->elem<<" ";
            root=root->rightChild;
        }
    }
    cout<<endl;
}

void preOrder(treeNode* root){
    if(root==nullptr) return;
    stack<treeNode*> nodeStack;
    while(root!=nullptr||!nodeStack.empty()){
        if(root){
            nodeStack.push(root);
            cout<<root->elem<<" ";
            root=root->leftChild;
        }
        else{
            root=nodeStack.top();
            nodeStack.pop();
            root=root->rightChild;
        }
    }
    cout<<endl;
}
void deleteNode(treeNode*& root,int key){
    if(root==nullptr) return;
    else if(root->elem>key){
        root=root->leftChild;
    }
    else if(root->elem<key){
        root=root->rightChild;
    }
    else {//找到了
        if(root->leftChild==nullptr&&root->rightChild==nullptr){
            delete root;
            return;
        }
        else if(root->leftChild==nullptr){
            
        }
        else if(root->rightChild==nullptr){//如果结点只有一棵左子树或右子树

        }
        else{

        }
    
    }
}
int main(){
    int array[]={10,9,8,54,12,36};
    int arraySize=6;
    treeNode* root;
    create_BST(root,array,arraySize);
    inOrder(root);
    preOrder(root);
    cout<<leafNodeNum(root);
    return 0;
}