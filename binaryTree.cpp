#include<iostream>
#include<stack>
#include<queue>
using namespace std;
struct treeNode
{
    /* data */
    char elem;
    treeNode *leftChild,*rightChild;    
    treeNode(){
        leftChild=nullptr;
        rightChild=nullptr;
        elem=' ';
    }
};
//二叉树的最大深度 也就是树的深度
int maxDepth(treeNode*root){
    if(root==nullptr){
        return 0;//空的话深度为0
    }
    else{
        int maxLeft=maxDepth(root->leftChild);
        int maxRight=maxDepth(root->rightChild);
        if(maxRight>maxLeft){
            return maxRight+1;
        }
        else{
            return maxLeft+1;
        }
    }
}
//求叶子节点的数量
int leafNodeNum(treeNode* root){
    if(root==nullptr){
        return 0;
    }
    if(root->leftChild==nullptr&&root->rightChild==nullptr){
        return 1;
    }
    return leafNodeNum(root->leftChild)+leafNodeNum(root->rightChild);
}
//树的结点的个数
int treeNodeNum(treeNode*root){
    if(root==nullptr){
        return 0;
    }
    return treeNodeNum(root->leftChild)+treeNodeNum(root->rightChild)+1;
}
//数组转换成二叉树
treeNode* arrayToBT(char *array,int pos,int arraySize ){
    treeNode* root=nullptr;
    if(pos<arraySize){
        root=new treeNode;//这个只能在这里面分配内存，否则会给叶节点的左右节点返回有实例化的节点
        root->elem=array[pos];
        root->leftChild=arrayToBT(array,pos*2+1,arraySize);
        root->rightChild=arrayToBT(array,pos*2+2,arraySize);
    }
    return root;
}

bool CreateTree(treeNode** root){
    char elem;
    cout<<"input character:";
    cin>>elem;
    if(elem=='!'){//递归停止的条件
        *root=nullptr;
        return false;
    }
    *root=new treeNode;
    if(!root){
        cout<<"failed to create a tree"<<endl;
    }
    if(elem!='!'){
        (*root)->elem=elem;
        CreateTree(&(*root)->leftChild);
        CreateTree(&(*root)->rightChild);
    }
    return true;
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
void postOrderTree(treeNode* root){
    if(root==nullptr){
        return ;
    }
    postOrderTree(root->leftChild);
    postOrderTree(root->rightChild);
    cout<<root->elem<<" ";
    
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
void postOrder(treeNode* root){
    if(root==nullptr) return ;
    stack<treeNode*> nodeStack;
    treeNode* visited;
    while(root!=nullptr||!nodeStack.empty()){
        if(root){
            nodeStack.push(root);
            root=root->leftChild;
        }
        else{
            root=nodeStack.top();
            if(root->rightChild&&root->rightChild!=visited){//若右子树存在并且未访问过 就进入右子树
                root=root->rightChild;
                nodeStack.push(root);  //压入栈后再次向左  其实这两句可以不写 和上面重复了
                root=root->leftChild;
            }
            else{//否则栈顶出栈并访问
                nodeStack.pop();
                cout<<root->elem<<" ";
                visited=root;
                //每次出栈访问完一个结点就相当于遍历完以该节点未根的子树，需要将root置NULL
                root=nullptr;//root会以栈顶为新的根结点（新的子树）进行处理
            }
        }
    }
    cout<<endl;
}
void BFS(treeNode* root){
        if(root==nullptr) return ;
        queue<treeNode*> nodeQueue;
        treeNode* temp=root;
        nodeQueue.push(temp);
        while(!nodeQueue.empty()){
            temp=nodeQueue.front();
            cout<<temp->elem<<" ";
            nodeQueue.pop();
            if(temp->leftChild){
                nodeQueue.push(temp->leftChild);
            }
            if(temp->rightChild){
                nodeQueue.push(temp->rightChild);
            }
        }
        cout<<endl;
}
//判断一棵二叉树是否为满二叉树
//原理：采用层次并遍历算法，将所有的结点加入队列（包括空结点）。
//遇到空结点时，查看其后是否有空结点
bool isComplete(treeNode* root){
    queue<treeNode*> nodeQueue;
    treeNode* temp=root;
    if(root==nullptr) return true;
    nodeQueue.push(temp);
    while(!nodeQueue.empty()){
        temp=nodeQueue.front();
        nodeQueue.pop();
        if(temp==nullptr){
            break;//如果遇到空结点就跳出，判断队列后面还有没有空结点
        }
        nodeQueue.push(temp->leftChild);
        nodeQueue.push(temp->rightChild);
    }
    //判断后面有没有空结点
    while(!nodeQueue.empty()){
        temp=nodeQueue.front();
        if(temp!=nullptr){
            return false;
        }
        nodeQueue.pop();

    }
    return true;
}
int main(){
    // treeNode* root=new treeNode;
    // CreateTree(&root);
    // cout<<"preOrder is :";
    // preOrderTree(root);
    // cout<<endl<<"inOrder is :";
    // inOrderTree(root);
    // cout<<endl<<"postOrder is :";
    // postOrderTree(root);
    int arraySize=5;
    char array[]={'a','b','c','d','e'};
    treeNode* root=arrayToBT(array,0,arraySize);
    cout<<maxDepth(root)<<endl;
    cout<<leafNodeNum(root)<<endl;
    inOrder(root);
    cout<<endl;
    preOrder(root);
    cout<<endl;
    cout<<treeNodeNum(root)<<endl;
    cout<<endl;
    postOrder(root);
    BFS(root);
    cout<<isComplete(root);
    return 0;
}