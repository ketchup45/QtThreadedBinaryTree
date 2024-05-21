#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"binarytree.h"
#include<QInputDialog>
#include<QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void  paintEvent(QPaintEvent *);
private slots:
    void on_actionLevel_triggered();        //层次建树
    void on_instruction_triggered();        //建树说明
    void on_prethread_triggered();         //先序线索化
    void on_inthread_triggered();          //中序线索化
    void on_postthread_triggered();        //后序线索化

private:
    Ui::MainWindow *ui;
    BinaryTree * Tree;                   //树
};

#endif // MAINWINDOW_H
