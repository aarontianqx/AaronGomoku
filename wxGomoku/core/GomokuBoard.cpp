/***************************************************************
 * Name:      GomokuBoard.cpp
 * Purpose:   Code for Gomoku Board
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-16
 **************************************************************/


#include "GomokuElements.h"

const PieceColor PieceColor::BLACK(1);
const PieceColor PieceColor::WHITE(2);
const PieceColor PieceColor::BLANK(0);
const PiecePosition PiecePosition::InvalidPiece(-1, -1);


void GomokuBoard::reset()
{
    for (int i=0; i<TABLESIZE; i++)
        for (int j=0; j<TABLESIZE; j++)
            board[i][j] = PieceColor::BLANK;
    piece_count = 0;
    next_color = PieceColor::BLACK;
}

void GomokuBoard::put(int x, int y)
{
    assert(PiecePosition::isLegal(x, y) && at(x, y).isBlank());
    board[y][x] = next_color;
    next_color = next_color.opponent();
    piece_count++;
}

void GomokuBoard::put(const PiecePosition& pos)
{
    put(pos.x, pos.y);
}

void GomokuBoard::withDraw(int x, int y)
{
    assert(PiecePosition::isLegal(x, y) && at(x, y) == next_color.opponent());
    board[y][x] =  PieceColor::BLANK;
    next_color = next_color.opponent();
    piece_count--;
}

void GomokuBoard::withDraw(const PiecePosition& pos)
{
    withDraw(pos.x, pos.y);
}

bool GomokuBoard::checkWin(int x, int y, PieceColor p) const
{
    assert(PiecePosition::isLegal(x, y) && (p.isBlack() || p.isWhite()));

    int num = 0;
    for (int i=x+1; i<TABLESIZE && at(i, y)==p; i++)
        num++;
    for (int i=x; i>=0 && at(i, y)==p; i--)
        num++;
    if (num >= 5)
        return true;

    num = 0;
    for (int i=y+1; i<TABLESIZE && at(x, i)==p; i++)
        num++;
    for (int i=y; i>=0 && at(x, i)==p; i--)
        num++;
    if (num >= 5)
        return true;

    num = 0;
    for (int i=x+1, j=y+1; i<TABLESIZE && j<TABLESIZE && at(i, j)==p; i++, j++)
        num++;
    for (int i=x, j=y; i>=0 && j>=0 && at(i, j)==p; i--, j--)
        num++;
    if (num >= 5)
        return true;

    num = 0;
    for (int i=x, j=y; i>=0 && j<TABLESIZE && at(i, j)==p; i--, j++)
		num++;
	for (int i=x+1,j=y-1; i<TABLESIZE && j>=0 && at(i, j)==p; i++, j--)
		num++;
	if (num >= 5)
		return true;

    return false;
}
