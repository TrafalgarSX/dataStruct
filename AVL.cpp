#include<iostream>
#include<string>
using namespace std;

struct treeNode
{
    /* data */
    int elem;
    int height;
    treeNode *leftChild,*rightChild;    
    treeNode(){
        leftChild=nullptr;
        rightChild=nullptr;
        elem=0;
        height=1; //单个结点高度为1
    }
};
int max(int a, int b){
    return a>b?a:b;
}
//求单个结点的高度
int height(treeNode* root){
    if(root==nullptr) return 0;
    return max(height(root->leftChild),height(root->rightChild))+1;
}
//求中序下某一二叉树的最小值
treeNode* minValue(treeNode* root){
    if(root==nullptr) return nullptr;
    while(root->leftChild){
        root=root->leftChild;
    }
    return root;
}
//求中序下某一二叉树的最大值
treeNode* maxValue(treeNode* root){
    if(root==nullptr) return nullptr;
    while(root->rightChild){
        root=root->rightChild;
    }
    return root;
}
int nodeHeight(treeNode* node){
    //空结点的高度为0  github上的实现空结点的高度是-1
    if(node==nullptr) return 0;
    return node->height;
}
int heightDiff(treeNode* root){
    if(root==nullptr) return 0;
    return nodeHeight(root->leftChild)-nodeHeight(root->rightChild);
}
//这个和height函数配套，功能和nodeHeight和heightDiff重合了
int getBalance(treeNode* root){
    //平衡因子，结点的左右子树高度差（的绝对值不超过1）
    return height(root->leftChild)-height(root->rightChild);
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
//右单旋转（LL）
treeNode* rightRotate(treeNode* root){
    treeNode* left=root->leftChild;
    root->leftChild=left->rightChild;
    left->rightChild=root;

    root->height=(max(nodeHeight(root->leftChild),nodeHeight(root->rightChild))+1);
    left->height=(max(nodeHeight(left->leftChild),nodeHeight(left->rightChild))+1);
    return left;
}
//左单旋转(RR)
treeNode* leftRotate(treeNode* root){
    treeNode* right=root->rightChild;
    root->rightChild=right->leftChild;
    right->leftChild=root;

    root->height=(max(nodeHeight(root->leftChild),nodeHeight(root->rightChild))+1);
    right->height=(max(nodeHeight(right->leftChild),nodeHeight(right->rightChild))+1);
  
    return right;
}
//这次不用引用了，用另一种方式修改树
treeNode* insertNode(treeNode*root,int elem){
    treeNode* newNode=new treeNode;
    newNode->elem=elem;
    if(root==nullptr){
        return newNode;
    }
    else if(elem<root->elem){
        root->leftChild=insertNode(root->leftChild,elem);
    }
    else if(elem>root->elem){
        root->rightChild=insertNode(root->rightChild,elem);
    }
    /*Node height as per the AVL formula*/
    //root->height=height(root);  这个是递归的求，没有用到结点的height成员
    //下面这个利用了height成员，在插入的递归中就不断的更新height,不用每次都递归
    root->height=(max(nodeHeight(root->leftChild),nodeHeight(root->rightChild))+1);

    int bal =heightDiff(root);
    //int bal=getBalance(root);
    if(bal>1){
        if(heightDiff(root->leftChild)<0){
            root->leftChild=leftRotate(root->leftChild);//LR
        }
        return rightRotate(root);//LL右单旋转
    }
    else if(bal<-1){
        if(heightDiff(root->rightChild)>0){
            root->rightChild=rightRotate(root->rightChild);//RL
        }
        return leftRotate(root);//RR左单旋转
    }
    return root;
}
//参考github 递归删除算法
treeNode* deleteNode(treeNode* root,int key){
    if(root==nullptr) return nullptr;
    if(key<root->elem){
        root->leftChild=deleteNode(root->leftChild,key);
    }
    else if(key>root->elem){
        root->rightChild=deleteNode(root->rightChild,key);
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
        root->rightChild=deleteNode(root->rightChild,temp->elem);
    }
    //删除后要记得重新平衡
    //single node in tree and deleted
    if(root==nullptr){
        return root;
    }
    /*update height*/
    root->height=(max(nodeHeight(root->leftChild),nodeHeight(root->rightChild))+1);

    int bal=heightDiff(root);
    if(bal>1){
        if(heightDiff(root->leftChild)<0){
            root->leftChild=leftRotate(root->leftChild);//LR
        }
        return rightRotate(root);//LL右单旋转
    }
    else if(bal<-1){
        if(heightDiff(root->rightChild)>0){
            root->rightChild=rightRotate(root->rightChild);//RL
        }
        return leftRotate(root);//RR左单旋转
    }
    return root;
}
void preOrderTree(treeNode* root){
    if(root==nullptr){
        return ;
    }
    cout<<root->elem<<" ";
    preOrderTree(root->leftChild);
    preOrderTree(root->rightChild);

}
void inOrderTree(treeNode* root){
    if(root==nullptr){
        return ;
    }
    inOrderTree(root->leftChild);
    cout<<root->elem<<" ";
    inOrderTree(root->rightChild);

}

int main(){
    treeNode* root=nullptr;//要记得初始化
    int array[]={10,9,8,54,12,36};
    for(int i=0;i<5;i++){
        root=insertNode(root,array[i]);
    }
    preOrderTree(root);
    cout<<endl;
    inOrderTree(root); 
    cout<<endl;
    root=deleteNode(root,8);
    preOrderTree(root);
    cout<<endl;
    inOrderTree(root);
}