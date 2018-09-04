#include "gamehelper.h"
GameHelper::GameHelper(){
    this->game_h = NULL;
    this->processId = NULL;
    this->chessWidth = 31;
    this->chessHeight = 35;
    this->firstChessPoint.x = 22;
    this->firstChessPoint.y = 187;
    this->startGameBtn.x = 129;
    this->startGameBtn.y = 57;
    this->nNumberX = 19;
    this->nNumberY = 11;
    this->chessBaseAddress = (LPCVOID) 0x00199F68;
}
GameHelper::GameHelper(LPCWSTR windowName)
{
    this->game_h = FindWindow(NULL,windowName);
    this->processId = GetWindowThreadProcessId(this->game_h,&(this->processId));
    this->chessWidth = 31;
    this->chessHeight = 35;
    this->firstChessPoint.x = 22;
    this->firstChessPoint.y = 187;
    this->startGameBtn.x = 129;
    this->startGameBtn.y = 57;
    this->nNumberX = 19;
    this->nNumberY = 11;
    this->chessBaseAddress = (LPCVOID) 0x00199F68;
    cout << "game_h = "<<game_h << " processId= "<<processId;
}
void GameHelper::GetWindowRect(){
    ::GetWindowRect(game_h,&(this->windowPositon));
}
void GameHelper::GetChessData(){
    HANDLE processH = OpenProcess(PROCESS_ALL_ACCESS,false,this->processId);
    //读取进程内存数据
    DWORD byread;

    ReadProcessMemory(processH,this->chessBaseAddress,(LPVOID)this->chessData,11*19,&byread);
    cout << "chessData = "<<chessData;

}
int GameHelper::GetValue(POINT point){
    return (*((PCHAR)this->chessBaseAddress + point.x +point.y * nNumberX));
}
//查看两个块是否可以直连
bool GameHelper::MatchBlock(POINT st1, POINT st2)
{
    if(!(st1.x==st2.x || st1.y==st2.y))
    {
        return false;
    }

    POINT stMin, stMax;

    //如果是竖线直连
    if(st1.x==st2.x)
    {
        //由于这里会被 一折连 递归调用 所以必须判断大小
        stMin=st1.y<st2.y?st1:st2;
        stMax=st1.y>st2.y?st1:st2;

        for(stMin.y++; stMin.y<stMax.y; stMin.y++)
        {
            if(GetValue(stMin)!=0)
            {
                return false;
            }
        }
    }
    //如果是横线直连
    else
    {
        stMin=st1.x<st2.x?st1:st2;
        stMax=st1.x>st2.x?st1:st2;

        for(stMin.x++; stMin.x<stMax.x; stMin.x++)
        {
            if(GetValue(stMin)!=0)
            {
                return false;
            }
        }
    }

    return true;
}

//查看两个块是否可以一折连
bool GameHelper::MatchBlockOne(POINT st1, POINT st2)
{
    //以st1 st2为矩形对角 寻找矩形另外2点
    POINT a1, a2;
    a1.x=st1.x;
    a1.y=st2.y;
    a2.x=st2.x;
    a2.y=st1.y;
    /*示意图如下：
    st1			a2
    a1			st2
    */

    //矩形另外2点都不会空 则跳过这种情况
    if((GetValue(a1)!=0) && (GetValue(a2)!=0))
    {
        return false;
    }

    //如果a1为空
    if(GetValue(a1)==0)
    {
        //测试 a1-st1直连 a1-st2直连
        if(!(MatchBlock(a1, st1) && MatchBlock(a1, st2)))
        {
            return false;
        }
    }
    //如果a2为空
    else
    {
        //测试 a2-st1直连 a2-st2直连
        if(!(MatchBlock(a2, st1) && MatchBlock(a2, st2)))
        {
            return false;
        }
    }

    return true;
}

//查看两个块是否可以两折连
bool GameHelper::MatchBlockTwo(POINT st1, POINT st2)
{
    /*同样把st1,st2想成一个矩形的两个对角, 依次从st1的X轴 Y轴每次+1/-1寻找为空的点C/D
    再由C/D和st2进行一折连判断 示意图如下:
    st1            C
    D                st2

    由于st1和st2的相对位置不确定所以 需要把st1分4种情况讨论
    */
    POINT stTmp;

    //判断st1的X轴+1
    if(st1.x!=nNumberX-1)
    {
        stTmp.x=st1.x+1;
        stTmp.y=st1.y;

        for(; stTmp.x<=nNumberX-1; stTmp.x++)
        {
            if(GetValue(stTmp)==0)
            {
                if(MatchBlockOne(stTmp, st2))
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }

    //判断st1的X轴-1
    if(st1.x!=0)
    {
        stTmp.x=st1.x-1;
        stTmp.y=st1.y;

        for(; stTmp.x>=0; stTmp.x--)
        {
            if(GetValue(stTmp)==0)
            {
                if(MatchBlockOne(stTmp, st2))
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }


    //判断st1的Y轴+1
    if(st1.y!=nNumberY-1)
    {
        stTmp.x=st1.x;
        stTmp.y=st1.y+1;

        for(; stTmp.y<=nNumberY-1; stTmp.y++)
        {
            if(GetValue(stTmp)==0)
            {
                if(MatchBlockOne(stTmp, st2))
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }


    //判断st1的Y轴-1
    if(st1.y!=0)
    {
        stTmp.x=st1.x;
        stTmp.y=st1.y-1;

        for(; stTmp.y>=0; stTmp.y--)
        {
            if(GetValue(stTmp)==0)
            {
                if(MatchBlockOne(stTmp, st2))
                {
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }

    return false;
}
//点击棋子
void GameHelper::ClickChess(POINT chess){
    cout << "x = "<<chess.x<<",y="<<chess.y;
    SendMessage(game_h,WM_LBUTTONDOWN,0,(chess.y<<16)+chess.x);
    SendMessage(game_h,WM_LBUTTONUP,0,(chess.y<<16)+chess.x);
}
//消除棋子
void GameHelper::ClearChess(){
    POINT st1;POINT st2;
    cout<<"nNumberY = " << nNumberY;
    //j *31+22,i*35+187
    for(int y1 = 0;y1<nNumberY;y1++){
        for(int x1=0;x1<nNumberX;x1++){
            for(int y2 = 0;y2<nNumberY;y2++){
                for(int x2 = 0;x2<nNumberX;x2++){
                    if(chessData[y1][x1] == chessData[y2][x2] &&chessData[y1][x1]!=0){
                        if(x1 == x2 && y1 == y2){
                            return;
                        }
                        st1.x = x1*31+22;
                        st1.y = y1*35+187;
                        st2.x = x2*31+22;
                        st2.y = y2*35+187;

                        if(MatchBlock(st1,st2) || MatchBlockOne(st1,st2) ||MatchBlockTwo(st1,st2) ){
                            cout << "findOne";
                            ClickChess(st1);
                            ClickChess(st2);
                            return ;
                        }

                    }
                }
            }
        }
    }
}
GameHelper::~GameHelper(){

}
