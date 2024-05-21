#include "binarytree.h"
#include<QDebug>
#include<QStack>
#include<QQueue>

//获得前序、中序、后、层次遍历的字符串
QString BinaryTree::getPreStr()
{
   return preStr;
}

QString BinaryTree::getInStr()
{
   return inStr;
}

QString BinaryTree::getPostStr()
{
   return postStr;
}

QString BinaryTree::getLevelStr()
{
   return levelStr;
}

QPoint *BinaryTree::getPoints()
{
   return NodePoints;
}

QLine *BinaryTree::getLines()
{
   return PointLines;
}

QString BinaryTree::GetLevelPtrList()
{
   return LevelPtrList;
}

BinTreeNode *BinaryTree::getRoot()
{
   return root;
}

int BinaryTree::GetNodeNum()
{
   return NodeNum;
}

int BinaryTree::GetHeight()
{
   return height(root);
}

int BinaryTree::height(BinTreeNode *Node)
{
     if(Node==nullptr)
         return 0;
     else
     {
         int i=height(Node->Lchild);
         int j=height(Node->Rchild);
         return (i<j)? j+1:i+1;
     }
}

//默认构造函数
BinaryTree::BinaryTree()
{
    root=nullptr;
    NodeNum=0;
    NodePoints=nullptr;
    IfLegal=true;
    IfThread=0;
}

//构造函数
BinaryTree::BinaryTree(QString str)
{
    int j=0;
    NodeNum=0;
    IfThread=0;
    QQueue<BinTreeNode *> NodeQ;
    BinTreeNode *p = nullptr;

    if(str[j]=='#') {  //空树
        NodeNum=0;
        return;
    }

    root=new BinTreeNode(str[j]);//根节点
    NodeNum++;  //结点数量加一
    NodeQ.enqueue(root);
    j++;

    //ABC ##D# ##
    while(j<(str.size()-1)){
        if(NodeQ.isEmpty())
            break;
         else
            p=NodeQ.dequeue();

        if(str[j]!='#') {  //如果字符不为‘#’，创建左结点
            p->Lchild=new BinTreeNode(str[j]);
            NodeNum++;
            NodeQ.enqueue(p->Lchild);
        }
         j++;

        if(str[j]!='#') {  //如果字符不为‘#’，创建右结点
            p->Rchild=new BinTreeNode(str[j]);
            NodeNum++;
            NodeQ.enqueue(p->Rchild);
        }
         j++;
    }

    if(str.size()!=j) {//没有用到所有节点说明树生成错误
        IfLegal=false;
        return;
    }
    else
        IfLegal=true;

    //进行遍历
    this->setMyPoints();
    this->preOrder(root);
    this->inOrder(root);
    this->postOrder(root);
    this->LevelOrder();
}

//析构函数
BinaryTree::~BinaryTree()
{
   this->clear();
}

 //中序遍历
void BinaryTree::LevelOrder()
{
    QQueue<BinTreeNode *>Q;         //调用队列
    BinTreeNode *p=root;
    Q.enqueue(root);
    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        levelStr.append(p->data);
        if(p->Lchild!=nullptr)
            Q.enqueue(p->Lchild);
        if(p->Rchild!=nullptr)
            Q.enqueue(p->Rchild);
    }
}

//添加结点
void BinaryTree::AddPtrList(BinTreeNode* p)
{
    LevelPtrList.append(QString::number(p->LTag));
    if(p->Lchild!=nullptr)
        LevelPtrList.append(p->Lchild->data);
    else
        LevelPtrList.append('^');

    LevelPtrList.append(QString::number(p->LTag));
    if(p->Rchild!=nullptr)
        LevelPtrList.append(p->Rchild->data);
    else
        LevelPtrList.append('^');
}
void BinaryTree::SetLevelPtrList()
{
    QQueue<BinTreeNode *>Q;         //调用队列
    BinTreeNode *p=root;
    Q.enqueue(root);

    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        AddPtrList(p);
        if(p->Lchild!=nullptr && p->LTag==0)
            Q.enqueue(p->Lchild);
        if(p->Rchild!=nullptr && p->RTag==0)
            Q.enqueue(p->Rchild);
    }
}
//为坐标组设置应的坐标,以及得到相应的线段
void BinaryTree::setMyPoints()
{
      //设置父节点和子节点间横坐标相差的距离

    int i=0;

    NodePoints = new QPoint[NodeNum];  //动态分配空间
    PointLines = new QLine[NodeNum-1];

    QQueue<BinTreeNode *> Q;         //调用队列
    BinTreeNode *p = root;
    root->setpoint(QPoint(500,75));  //为根节点设置坐标
    Q.enqueue(root);
    NodePoints[i]=root->point;


    //通过层次遍历，完成各个坐标的匹配
    while(!Q.isEmpty())
    {
        p=Q.dequeue();
        if(p->Lchild!=nullptr)//和左子树连线
        {
            i++;
            int h=height(p);
            p->Lchild->setpoint(p->point-QPoint(45*h,-100));
            NodePoints[i]=p->Lchild->point;
            PointLines[i-1].setP1(p->point+QPoint(0,25));
            PointLines[i-1].setP2(p->Lchild->point-QPoint(0,25));
            Q.enqueue(p->Lchild);
        }

        if(p->Rchild!=nullptr)//和右子树连线
        {
            i++;
            int h=height(p);
            p->Rchild->setpoint(p->point+QPoint(45*h,100));
            NodePoints[i]=p->Rchild->point;
            PointLines[i-1].setP1(p->point+QPoint(0,25));
            PointLines[i-1].setP2(p->Rchild->point-QPoint(0,25));
            Q.enqueue(p->Rchild);
            h--;
        }

    }

}

void BinaryTree::clear()
{
    this->destroy(root);
    NodeNum=0;
    delete[] NodePoints;
    delete[] PointLines;
    preStr.clear();
    inStr.clear();
    postStr.clear();
    levelStr.clear();
    LevelPtrList.clear();
}



//删除函数
void BinaryTree::destroy(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        this->destroy(Node->Lchild);
        this->destroy(Node->Rchild);
        delete Node;
    }
}


//前序、中序、后序遍历
void BinaryTree::preOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        preStr.append(Node->data);
        preOrder(Node->Lchild);
        preOrder(Node->Rchild);
    }
}

void BinaryTree::inOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        inOrder(Node->Lchild);
        inStr.append(Node->data);
        inOrder(Node->Rchild);
    }
}

void BinaryTree::postOrder(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        postOrder(Node->Lchild);
        postOrder(Node->Rchild);
        postStr.append(Node->data);
    }
}

//清空线索化
void ClearThreading(BinTreeNode *Node)
{
    if(Node!=nullptr)
    {
        if(Node->LTag==1){
            Node->LTag=0;
            Node->Lchild=nullptr;
        }
        if(Node->RTag==1){
            Node->RTag=0;
            Node->Rchild=nullptr;
        }
        ClearThreading(Node->Lchild);
        ClearThreading(Node->Rchild);
    }
}
void BinaryTree::ClearThread()
{
    ClearThreading(root);
    LevelPtrList.clear();
}

//先序线索化
void PreThreading(BinTreeNode* P, BinTreeNode* &pre)
{
    if(P){
        if(!P->Lchild){//不存在左子树
            P->LTag=1;
            P->Lchild=pre;
        }
        if(!P->Rchild)//不存在右子树
            P->RTag=1;
        if(pre && pre->RTag==1)
            pre->Rchild=P;
        pre = P;//令pre为前驱结点

        if(P->LTag==0)
            PreThreading(P->Lchild, pre);
        if(P->RTag==0)
            PreThreading(P->Rchild, pre);
    }
}
void BinaryTree::PreThread()
{
    if(IfThread==0)
        IfThread=1;
    else
        ClearThread();
    BinTreeNode* pre = NULL;
    PreThreading(root, pre);
}

//中序线索化
void InThreading(BinTreeNode* P, BinTreeNode* &pre)
{
    if(P){
        InThreading(P->Lchild, pre);

        if(!P->Lchild){//不存在左子树
            P->LTag=1;
            P->Lchild=pre;
        }
        if(!P->Rchild)//不存在右子树
            P->RTag=1;
        if(pre && pre->RTag==1)
            pre->Rchild=P;
        pre = P;//令pre为前驱结点

        InThreading(P->Rchild, pre);
    }
}
void BinaryTree::InThread()
{
    if(IfThread==0)
        IfThread=1;
    else
        ClearThread();
    BinTreeNode* pre= NULL;
    InThreading(root, pre);
}

//后序线索化
void PostThreading(BinTreeNode* P, BinTreeNode* &pre)
{
    if(P){
        PostThreading(P->Lchild, pre);
        PostThreading(P->Rchild, pre);

        if(!P->Lchild){//不存在左子树
            P->LTag=1;
            P->Lchild=pre;
        }
        if(!P->Rchild)//不存在右子树
            P->RTag=1;
        if(pre && pre->RTag==1)
            pre->Rchild=P;
        pre = P;//令pre为前驱结点
    }
}
void BinaryTree::PostThread()
{
    if(IfThread==0)
        IfThread=1;
    else
        ClearThread();
    BinTreeNode* pre= NULL;
    PostThreading(root, pre);
}

