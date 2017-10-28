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

class wxGomokuFrame;

class GomokuAI: public wxThread
{
    public:
        /** Default constructor */
        GomokuAI(wxGomokuFrame *_frame, GomokuBoard *_board = nullptr, GomokuGame *_game = nullptr, int _difficulty=1);

        // bind gomoku game to bot
        void initiate(GomokuBoard *_board, GomokuGame *_game);

        // set AI level
        void setDifficulty(int _difficulty);

        // thread methods
        virtual ExitCode Entry();
        void WakeUp();

        /** Default destructor */
        virtual ~GomokuAI();



        PiecePosition searchBest();

    protected:

        void runThread();
        // return score under the ideal strategy
        int dfSearchScore(GomokuBoard *board, int ply, int alpha, int beta);

    private:
        int max_depth;
        wxGomokuFrame *main_frame;
        GomokuBoard *gomoku_board;
        GomokuGame *gomoku_game;
        int difficulty;

        wxMutex m;
        wxCondition *cond;
        uint32_t node;

};

#endif // GOMOKUAI_H
