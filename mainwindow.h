#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HWND hwdn;
    QTimer *timer;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void timerUpDate();

    void timeout();

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
