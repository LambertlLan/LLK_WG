#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamehelper.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
GameHelper *gameHelper = NULL;
/**
 * @brief MainWindow::on_pushButton_2_clicked
 * 开启游戏后
 * 初始化类
 */
void MainWindow::on_pushButton_2_clicked()
{
    gameHelper = new GameHelper(L"QQ游戏 - 连连看角色版");
    if(gameHelper!=NULL){
        QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes, QMessageBox::Yes);
    }
}
/**
 * @brief MainWindow::on_pushButton_clicked
 * 消除一次
 */
void MainWindow::on_pushButton_clicked()
{
    if(gameHelper != NULL){
        gameHelper->GetChessData();
        gameHelper->ClearChess();
    }else{
        QMessageBox::information(NULL, "Title", "请先初始化类", QMessageBox::Yes, QMessageBox::Yes);
    }


}


