/***************************************************************
 * Name:      GomokuElements.h
 * Purpose:   defines for Gomoku Board and Base Elements
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-16
 **************************************************************/

#ifndef GOMOKUELEMENTS_H_INCLUDED
#define GOMOKUELEMENTS_H_INCLUDED

#include <stdint.h>
#include "gomoku_global.h"

class PieceColor
{
public:
    static const PieceColor BLACK;
    static const PieceColor WHITE;
    static const PieceColor BLANK;

    PieceColor(const PieceColor& p): color(p.color) {};
    PieceColor(char _color=0): color(_color) {};
    bool operator==(const PieceColor& p) const;
    bool operator!=(const PieceColor& p) const;
    operator char() const { return color; }
    PieceColor opponent() const;

    bool isBlack() const;
    bool isWhite() const;
    bool isBlank() const;

private:
    char color;
};


enum Direction
{
    LEFTUP = 0,
    UP = 1,
    RIGHTUP = 2,
    LEFT = 4,
    RIGHT = 6,
    LEFTDOWN = 8,
    DOWN = 9,
    RIGHTDOWN = 10
};

inline
Direction opponentDir(Direction dir)
{
    return Direction(10 - int(dir));
}

class PiecePosition
{
public:
    PiecePosition():x(0), y(0) {}
    PiecePosition(int _x, int _y):x(_x), y(_y) {}

    static bool isLegal(int _x, int _y);
    bool isLegal() const;

    PiecePosition adjacent(Direction dir);
    void move(Direction dir);

    bool operator==(const PiecePosition& r) const
    {
        return isLegal()?(x==r.x && y==r.y):!r.isLegal();
    }

    bool operator!=(const PiecePosition& r) const
    {
        return isLegal()?(x!=r.x || y!=r.y):r.isLegal();
    }

    int8_t x;
    int8_t y;

    static const PiecePosition InvalidPiece;
};


class GomokuBoard
{
public:
    GomokuBoard() { reset(); }

    // getting methods
    PieceColor at(int x, int y) const;
    PieceColor at(const PiecePosition& pos) const;
    int pieceCount() const;
    PieceColor nextColor() const;

    bool checkWin(int x, int y, PieceColor p) const;

protected:
    // modifying methods
    void reset();

    // position unchecked
    // make sure to check validation before putting a piece
    void put(int x, int y);
    void put(const PiecePosition& pos);

    // withdraw one certain piece
    // make sure to check validation before withdrawing
    void withDraw(int x, int y);
    void withDraw(const PiecePosition& pos);

    friend class GomokuGame;
    friend class GomokuAI;

private:
    PieceColor board[TABLESIZE][TABLESIZE];
    PieceColor next_color;
    int piece_count;
};




/******
 * inline functions implementation of PieceColor
******/
inline
bool PieceColor::operator==(const PieceColor& p) const
{
    return color == p.color;
}

inline
bool PieceColor::operator!=(const PieceColor& p) const
{
    return color != p.color;
}

inline
PieceColor PieceColor::opponent() const
{
    assert(color > 0 && color < 3);
    return PieceColor(3 - color);
}

inline
bool PieceColor::isBlack() const
{
    return color == BLACK.color;
}
inline
bool PieceColor::isWhite() const
{
    return color == WHITE.color;
}
inline
bool PieceColor::isBlank() const
{
    return color == BLANK.color;
}


/******
 * inline functions implementation of PiecePosition
******/

inline
bool PiecePosition::isLegal(int _x, int _y)
{
    return _x >= 0 && _y >= 0 && _x < TABLESIZE && _y < TABLESIZE;
}

inline
bool PiecePosition::isLegal() const
{
    return isLegal(x, y);
}

inline
PiecePosition PiecePosition::adjacent(Direction dir)
{
    return PiecePosition(x + (int(dir) & 3) - 1, y + ((int(dir) >> 2) & 3) - 1);
}

inline
void PiecePosition::move(Direction dir)
{
    x += (int(dir) & 3) - 1;
    y += ((int(dir) >> 2) & 3) - 1;
}



/******
 * inline functions implementation of GomokuBoard
******/

inline
PieceColor GomokuBoard::at(int x, int y) const
{
    assert(PiecePosition::isLegal(x, y));
    return board[y][x];
}

inline
PieceColor GomokuBoard::at(const PiecePosition& pos) const
{
    assert(pos.isLegal());
    return board[pos.y][pos.x];
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


#endif // GOMOKUELEMENTS_H_INCLUDED
