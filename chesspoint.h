#ifndef CHESSPOINT_H
#define CHESSPOINT_H
#include <windows.h>

class ChessPoint
{
    public:
    POINT p;
    POINT up;
    POINT down;
    POINT left;
    POINT right;
    ChessPoint(POINT pxy);
    virtual ~ChessPoint();
};


#endif // CHESSPOINT_H
