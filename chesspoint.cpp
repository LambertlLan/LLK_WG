#include "chesspoint.h"

ChessPoint::ChessPoint(POINT pxy)
{
    this->p = pxy;
    this->up = pxy;
    this->down = pxy;
    this->left = pxy;
    this->right = pxy;
    this->up.y = pxy.y-1;
    this->down.y = pxy.y+1;
    this->left.x = pxy.x-1;
    this->right.x = pxy.x+1;
}

ChessPoint::~ChessPoint(){}
