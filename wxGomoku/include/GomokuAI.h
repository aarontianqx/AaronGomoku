/***************************************************************
 * Name:      GomokuAI.h
 * Purpose:   Defines for AI Algorithm and Bot Thread
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-20
 **************************************************************/

#ifndef GOMOKUAI_H
#define GOMOKUAI_H

#include "GomokuGame.h"
#include <vector>
#include <wx/thread.h>

class PieceScore
{
public:
    PiecePosition pos;
    short score;

    PieceScore(PiecePosition _pos=PiecePosition::InvalidPiece, int _score=0)
        : pos(_pos), score(_score)
    {}

    bool operator <(const PieceScore& r) const
    {
        return score < r.score;
    }

    bool operator >(const PieceScore& r) const
    {
        return score > r.score;
    }
};

class GomokuAI
{
    public:
        GomokuAI(GomokuBoard *board, int difficulty);

        PiecePosition operator()(uint32_t& _node);

    protected:
        // generate posible points in a limit number
        // blank_points have been calculated previously
        std::vector<PieceScore> generatePoints(GomokuBoard *board, uint32_t limit);
        // evaluate the whole situation (for leaf node)
        int evaluateSituation(GomokuBoard *board, int alpha, int beta);
        // return score under the ideal strategy
        int dfSearchScore(GomokuBoard *board, int ply, int alpha, int beta);

    private:
        int max_depth;
        GomokuBoard *gomoku_board;
        uint32_t node;
        std::vector<PiecePosition> blank_points;
};

#endif // GOMOKUAI_H
