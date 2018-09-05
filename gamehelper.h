#ifndef GAMEHELPER_H
#define GAMEHELPER_H
#include<windows.h>
#include<QDebug>
#include<QMessageBox>
#define cout qDebug()
class GameHelper
{
public:
    int chessWidth;//棋子宽度
    int chessHeight;//棋子高度
    POINT firstChessPoint;//第一个棋子的中心坐标
    LPCVOID chessBaseAddress;//棋盘首地址
    POINT startGameBtn;//开始按钮坐标
    HWND game_h;//窗口句柄
    RECT windowPositon;//窗口位置
    DWORD processId;//进程id
    byte chessData[11][19];//棋盘数据数组
    int nNumberX;//棋盘X轴数量
    int nNumberY;//棋盘y轴数量
    int leftChessNum;//剩余棋子数
    LPCVOID leftChessAddr;//剩余棋子数量基址
    GameHelper();
    GameHelper(LPCWSTR windowName);
    void GetWindowRect();
    void GetChessData();
    int GetValue(POINT point);
    bool MatchBlock(POINT st1, POINT st2);
    bool MatchBlockOne(POINT st1, POINT st2);
    bool MatchBlockTwo(POINT st1, POINT st2);
    void ClickChess(POINT chess);
    bool ClearChess();
    void ClearAll();
    void GetLeftChessNum();
    ~GameHelper();
};

#endif // GAMEHELPER_H
