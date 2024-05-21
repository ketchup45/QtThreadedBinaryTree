#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QDir>
#include<QPainter>
#include<QPen>
#include<QStack>
#include<QPoint>
#include<QMessageBox>
#include<iostream>
#include<string>

//构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BinaryTree");//命名
    Tree=nullptr;
}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
    delete Tree;
}

//重构的绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::SolidLine);
    pen.setWidth(5);

    //只有当树非空的时候才画图
    if(Tree != nullptr && Tree->IfLegal == true)
    {
        qDebug()<<Tree->GetLevelPtrList();

        for(int i=0;i<Tree->GetNodeNum();i++)
        {
            //画圆
            pen.setColor(Qt::blue);
            painter.setPen(pen);
            QPoint p = Tree->getPoints()[i];//得到各个节点的坐标
            painter.drawEllipse(p, 25, 25);//圆的半径为25


            if(Tree->IfThread){//需要显示线索化
                pen.setColor(Qt::red);
                painter.setPen(pen);
                painter.drawEllipse(QPoint(p.x()-40, p.y()), 20, 20);//左圆
                painter.drawEllipse(QPoint(p.x()+40, p.y()), 20, 20);//右圆
            }

            //写字符
            //ABC#DE#FG#H######
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(p, QString(Tree->getLevelStr()[i]));

            if(Tree->IfThread){//需要显示线索化
                painter.drawText(QPoint(p.x()-40, p.y()- 5), QString(Tree->GetLevelPtrList()[i*4+0]));//LTag
                painter.drawText(QPoint(p.x()-40, p.y()+15), QString(Tree->GetLevelPtrList()[i*4+1]));//Lchild
                painter.drawText(QPoint(p.x()+40, p.y()- 5), QString(Tree->GetLevelPtrList()[i*4+2]));//RTag
                painter.drawText(QPoint(p.x()+40, p.y()+15), QString(Tree->GetLevelPtrList()[i*4+3]));//Rchild
            }

            if(i!=0)
               painter.drawLine(Tree->getLines()[i-1]);//得到线段的坐标
        }

        //输出各种遍历
       pen.setColor(Qt::black);
       painter.setPen(pen);

       painter.drawText(10,70,"前序：");
       painter.drawText(10,100,Tree->getPreStr());

       painter.drawText(10,150,"中序：");
       painter.drawText(10,180,Tree->getInStr());

       painter.drawText(10,230,"后序：");
       painter.drawText(10,260,Tree->getPostStr());

       painter.drawText(10,310,"层次：");
       painter.drawText(10,340,Tree->getLevelStr());

       painter.drawText(10,390,"结点个数：");
       painter.drawText(10,420,QString::number(Tree->GetNodeNum()));
    }


}

//层次构造
void MainWindow::on_actionLevel_triggered()
{
    bool isOk;
    QString BuildText = QInputDialog::getText(this,QString("构造树"),QString("输入字符串"),
                                       QLineEdit::Normal, QDir::home().dirName(), &isOk);
    if(isOk && !BuildText.isEmpty())
    {
        int i=BuildText.count('#');

        //错误判断
        if((2*i-BuildText.size())!=1) {//不符合规则
            QMessageBox::information(nullptr, "层次构造", "层次构造输入错误", QMessageBox::Yes);
            return;
        }

        if(Tree!=nullptr)//已构建过树
            Tree->clear();

         Tree=new BinaryTree(BuildText);

         //如果生成树错误,则不刷新屏幕
         if(Tree->IfLegal)
             update();
         else
             QMessageBox::information(nullptr, "层次构造", "层次构造输入错误", QMessageBox::Yes);
    }
}

//显示建树说明
void MainWindow::on_instruction_triggered()
{

    QMessageBox instr;
    //设定大小
    instr.setStyleSheet("QLabel{"
                         "min-width: 400px;"
                         "min-height: 400px; "
                        "}");

    instr.setWindowTitle(tr("层次遍历：构建二叉树说明"));

    instr.setText(tr("本程序采用层次遍历来构造二叉树，\n"
                     "单个结点的名称为一个字符\n"
                     "由上至下、由左至右的顺序按层次输入各结点名称\n"
                     "叶子结点的左右子结点需要用‘#’虚拟表示出来\n"
                     "如图所示的二叉树，构建时应输入：ABC##D###"));
    instr.setIconPixmap(QPixmap(":/new/example.png"));
    instr.exec();//显示此消息框

    return;
}

//先序线索化
void MainWindow::on_prethread_triggered()
{
    if(Tree == nullptr)//树不存在
        QMessageBox::information(nullptr, "线索化失败", "不存在二叉树", QMessageBox::Yes);
    else if(Tree->IfLegal == false)//树不合理
        QMessageBox::information(nullptr, "线索化失败", "上一次构建的树不合法", QMessageBox::Yes);
    else {
        Tree->PreThread();//线索化
        Tree->SetLevelPtrList();
        update();
    }
}
//后序线索化
void MainWindow::on_postthread_triggered()
{
    if(Tree == nullptr)//树不存在
        QMessageBox::information(nullptr, "线索化失败", "不存在二叉树", QMessageBox::Yes);
    else if(Tree->IfLegal == false)//树不合理
        QMessageBox::information(nullptr, "线索化失败", "上一次构建的树不合法", QMessageBox::Yes);
    else {
        Tree->PostThread();//线索化
        Tree->SetLevelPtrList();
        update();
    }
}
//中序线索化
void MainWindow::on_inthread_triggered()
{
    if(Tree == nullptr)//树存在
        QMessageBox::information(nullptr, "线索化失败", "不存在二叉树", QMessageBox::Yes);
    else if(Tree->IfLegal == false)//树不合理
        QMessageBox::information(nullptr, "线索化失败", "上一次构建的树不合法", QMessageBox::Yes);
    else {
        Tree->InThread();//线索化
        Tree->SetLevelPtrList();
        update();
    }
}

