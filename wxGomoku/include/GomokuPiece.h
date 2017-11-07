/***************************************************************
 * Name:      GomokuPiece.h
 * Purpose:   defines and codes for Base Elements
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-16
 **************************************************************/

#ifndef GOMOKUPIECE_H_INCLUDED
#define GOMOKUPIECE_H_INCLUDED

#include <stdint.h>
#include <cassert>

class PieceColor
{
public:
    static const PieceColor BLACK;
    static const PieceColor WHITE;
    static const PieceColor BLANK;
    static const PieceColor INVALID;

    PieceColor(const PieceColor& p): color(p.color) {};
    PieceColor(char _color=0): color(_color) {};

    bool operator==(const PieceColor& p) const;
    bool operator!=(const PieceColor& p) const;
    operator char() const { return color; }
    PieceColor opponent() const;

    bool isBlack() const;
    bool isWhite() const;
    bool isBlank() const;
    bool isInvalid() const;
    bool isValid() const;

private:
    char color;
};



class PiecePosition
{
public:
    PiecePosition(uint8_t _xy = 0):xy(_xy) {}
    // parameter unchecked, make sure 0<=x,y<=15
    PiecePosition(int x, int y);
    uint8_t getX() const;
    uint8_t getY() const;

    static bool isLegal(int x, int y);
    bool isLegal() const;

    PiecePosition operator+(uint8_t direction) const;
    PiecePosition operator-(uint8_t direction) const;
    PiecePosition& operator+=(uint8_t direction);
    PiecePosition& operator-=(uint8_t direction);
    bool operator==(const PiecePosition& r) const;
    bool operator!=(const PiecePosition& r) const;


    uint8_t xy;

    static const uint8_t XMASK;
    static const uint8_t YMASK;
    static const PiecePosition InvalidPiece;
    static const uint8_t LeftUp;
    static const uint8_t Up;
    static const uint8_t RightUp;
    static const uint8_t Left;
    static const uint8_t Right;
    static const uint8_t LeftDown;
    static const uint8_t Down;
    static const uint8_t RightDown;
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
inline
bool PieceColor::isInvalid()const
{
    return color == INVALID.color;
}
inline
bool PieceColor::isValid() const
{
    return color != INVALID.color;
}


/******
 * inline functions implementation of PiecePosition
******/

inline
PiecePosition::PiecePosition(int x, int y)
{
    xy = (x | (y << 4));
}

inline
uint8_t PiecePosition::getX() const
{
    return xy & XMASK;
}

inline
uint8_t PiecePosition::getY() const
{
    return (xy & YMASK) >> 4;
}

inline
bool PiecePosition::isLegal(int x, int y)
{
    return x >= 0 && y >= 0 && x < 15 && y < 15;
}

inline
bool PiecePosition::isLegal() const
{
    return (xy & XMASK) != XMASK && (xy & YMASK) != YMASK;
}

inline
PiecePosition PiecePosition::operator+(uint8_t direction) const
{
    assert(isLegal());
    return xy + direction;
}

inline
PiecePosition PiecePosition::operator-(uint8_t direction) const
{
    assert(isLegal());
    return xy - direction;
}

inline
PiecePosition& PiecePosition::operator+=(uint8_t direction)
{   assert(isLegal());
    xy += direction;
    return (*this);
}

inline
PiecePosition& PiecePosition::operator-=(uint8_t direction)
{
    assert(isLegal());
    xy -= direction;
    return (*this);
}

inline
bool PiecePosition::operator==(const PiecePosition& r) const
{
    return isLegal()?(xy == r.xy):!r.isLegal();
}

inline
bool PiecePosition::operator!=(const PiecePosition& r) const
{
    return isLegal()?(xy != r.xy):r.isLegal();
}


#endif // GOMOKUPIECE_H_INCLUDED
