/***************************************************************
 * Name:      GomokuBoard.h
 * Purpose:   defines for Gomoku Board
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-30
 **************************************************************/

#ifndef GOMOKUBOARD_H_INCLUDED
#define GOMOKUBOARD_H_INCLUDED

#include "GomokuPiece.h"
#include <vector>

class GomokuBoard
{
public:
    GomokuBoard() { reset(); }

    // getting methods
    PieceColor at(PiecePosition pos) const;
    PieceColor at(int x, int y) const;
    int pieceCount() const;
    PieceColor nextColor() const;

    bool checkWin(PiecePosition pos, PieceColor p) const;
    bool checkWin(int x, int y, PieceColor p) const;

    static const std::vector<PiecePosition>& validPoints();
    std::vector<PiecePosition> blankPoints() const;

protected:
    // modifying methods
    void reset();

    // position unchecked
    // make sure to check validation before putting a piece
    void put(PiecePosition pos);
    void put(int x, int y);

    // withdraw one certain piece
    // make sure to check validation before withdrawing
    void withDraw(PiecePosition pos);
    void withDraw(int x, int y);

    friend class GomokuGame;
    friend class GomokuAI;

private:
    PieceColor board[256];
    PieceColor next_color;
    int piece_count;
};


/******
 * inline functions implementation of GomokuBoard
******/

inline
PieceColor GomokuBoard::at(int x, int y) const
{
    assert(PiecePosition::isLegal(x, y));
    return board[x | (y << 4)];
}

inline
PieceColor GomokuBoard::at(PiecePosition pos) const
{
    return board[pos.xy];
}

inline
int GomokuBoard::pieceCount() const
{
    return piece_count;
}

inline
PieceColor GomokuBoard::nextColor() const
{
    return next_color;
}

#endif // GOMOKUBOARD_H_INCLUDED
