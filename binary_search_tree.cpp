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
treeNode* minValue(treeNode* root){
    if(root==nullptr) return nullptr;
    while(root->leftChild){
        root=root->leftChild;
    }
    return root;
}
//可以找到父节点
treeNode* BSTsearch_2(treeNode*root,int key,treeNode*&parent){
    while(root&&key!=root->elem){
        parent=root;
        if(key<root->elem){
            root=root->leftChild;
        }
        else{
            root=root->rightChild;
        }
    }
    return root;
}
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
/*书上的原理不太适合代码实现，需要找到父节点 （已实现）
 还需要找到中序的直接后继（前驱）代替要删除的结点，
 然后将问题转化为删除直接后继（前驱）结点
*/
void deleteNode(treeNode*& root,int key){
    
}
//参考github 递归删除算法
treeNode* deleteNode_2(treeNode* root,int key){
    if(root==nullptr) return nullptr;
    if(key<root->elem){
        root->leftChild=deleteNode_2(root->leftChild,key);
    }
    else if(key>root->elem){
        root->rightChild=deleteNode_2(root->rightChild,key);
    }
    else{//==  找到相等的了  递归思想 父节点在上一层函数调用里
        //Node to be deleted is leaf node or only one Child
        if(!root->rightChild){//右子树为空
           treeNode* temp=root->leftChild;
            delete root;
            root=nullptr;
            return temp;
        }
        else if(!root->leftChild){//左子树为空
            treeNode* temp=root->rightChild;
            delete root;
            root=nullptr;
            return temp;
        }
        //Node to be deleted is both left and right subtrees;
        treeNode* temp=minValue(root->rightChild);//中序直接后继,右子树的第一个结点也就是最小的结点
        root->elem=temp->elem;
        //删除右子树的这个结点（右子树的第一个结点）,重新确定右子树结点
        root->rightChild=deleteNode_2(root->rightChild,temp->elem);
    }
    return root;
}
int main(){
    int array[]={10,9,8,54,12,36};
    int arraySize=6;
    treeNode* root;
    create_BST(root,array,arraySize);
    inOrder(root);
    preOrder(root);
<<<<<<< HEAD
    //cout<<leafNodeNum(root);
    treeNode* temp=minValue(root);
    cout<<temp->elem;
=======
    cout<<leafNodeNum(root);
>>>>>>> c35e5c710ac0878f01a8e4f9c56e12f8644be977
    return 0;
}