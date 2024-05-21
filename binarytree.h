#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<QChar>
#include<QString>
#include<QPoint>
#include<QLine>

struct BinTreeNode
{
   QChar data;                 //数据
   BinTreeNode *Lchild, *Rchild;   //左孩子、右孩子
   bool LTag, RTag;  //标志
   QPoint point;               //结点的坐标

   BinTreeNode()               //默认构造函数
   {
       Lchild=NULL;
       Rchild=NULL;
       LTag=0;
       RTag=0;
       point=QPoint(0,0);
   }

   //构造函数
   BinTreeNode(QChar data)
   {
       this->data=data;
       Lchild=NULL;
       Rchild=NULL;
       LTag=0;
       RTag=0;
       point=QPoint(0,0);
   }

    //修改坐标的值
   void setpoint(QPoint p)
   {
        point=p;
   }
};


class BinaryTree
{
public:

    //构造函数、析构函数
    BinaryTree();
    BinaryTree(QString str);
    ~BinaryTree();

    //前序、中序、后序线索化
    void PreThread();
    void PostThread();
    void InThread();

    //清空之前的线索化
    void ClearThread();

    void AddPtrList(BinTreeNode* p);//把结点添加进去
    void SetLevelPtrList();//设定节点列表

    void setMyPoints();      //为坐标组设置应的坐标,以及得到相应的线段

    void clear();

    //获得前序、中序、后、层次遍历的字符串
    QString getPreStr();
    QString getInStr();
    QString getPostStr();
    QString getLevelStr();

    QPoint* getPoints();       //得到坐标
    QLine* getLines();         //得到线段

    int GetNodeNum();  //得到结点数量
    int GetHeight();   //得到树的高度

    BinTreeNode* getRoot(); //获得根节点
    QString GetLevelPtrList();//得到节点列表

    bool IfLegal;           //用于判断是否能够成功建树
    bool IfThread;          //是否进行过线索化

protected:
    BinTreeNode *root;      //树的根节点
    int NodeNum;           //树的结点个数

    QPoint *NodePoints;       //树各个结点坐标的集合 
    QLine *PointLines;        //线的条数

    QString preStr;         //前序遍历得到的字符串
    QString inStr;          //中序遍历得到的字符串
    QString postStr;        //后序遍历得到的字符串
    QString levelStr;       //层次遍历得到的字符串

    QString LevelPtrList;//层次遍历得到的节点列表

    int height(BinTreeNode *Node);  //得到树的高度

    void destroy(BinTreeNode *Node);                       //删除

    //前序、中序、后序遍历
    void preOrder(BinTreeNode *Node);
    void inOrder(BinTreeNode *Node);
    void postOrder(BinTreeNode *Node);
    void LevelOrder();
};

#endif // BINARYTREE_H
