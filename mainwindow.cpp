#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamehelper.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->timer = new QTimer(this);
    this->hwdn = (HWND)QWidget::winId();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    ui->setupUi(this);
    QMessageBox::information(NULL, "作者提示", "本软件仅供交流,严禁用于商业用途", QMessageBox::Yes, QMessageBox::Yes);
//    ::MoveWindow(this->hwdn,0,0,100,200,true);
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
        QMessageBox::information(NULL, "系统提示", "初始化类成功", QMessageBox::Yes, QMessageBox::Yes);
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
        QMessageBox::information(NULL, "系统提示", "请先初始化类", QMessageBox::Yes, QMessageBox::Yes);
    }


}


/**
 * @brief MainWindow::timerUpDate
 * 定时器回调
 */
void MainWindow::timerUpDate(){
    gameHelper->GetChessData();
    gameHelper->ClearChess();
}
/**
 * @brief MainWindow::timeout
 * 超时处理
 */
void MainWindow::timeout(){
    cout << "2222";
}

/**
 * @brief MainWindow::on_checkBox_2_stateChanged
 * @param arg1
 * 自动消除
 */
int sliderTime = 1000;
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(gameHelper){
        if(arg1){
            if(ui->checkBox->isChecked()){
                timer->start(sliderTime);
            }else{
                timer->start(1000);
            }

        }else{
            timer->stop();
        }
    }else{
        QMessageBox::information(NULL, "系统提示", "请先初始化类", QMessageBox::Yes, QMessageBox::Yes);
    }

}
/**
 * @brief MainWindow::on_pushButton_3_clicked
 * 秒杀
 */

void MainWindow::on_pushButton_3_clicked()
{
    if(gameHelper){

        gameHelper->ClearAll();
    }else{
        QMessageBox::information(NULL, "系统提示", "请先初始化类", QMessageBox::Yes, QMessageBox::Yes);
    }

}
void MainWindow::on_checkBox_stateChanged(int arg1)
{



}

void MainWindow::on_slider_sliderMoved(int position)
{
    ui->label->setText(QString::number(position,10));
    sliderTime = position;
}
