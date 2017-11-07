/***************************************************************
 * Name:      GomokuAI.h
 * Purpose:   Defines for Bot Thread
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-30
 **************************************************************/

#ifndef GOMOKUBOT_H
#define GOMOKUBOT_H

#include <wx/thread.h>
#include "GomokuAI.h"

class wxGomokuFrame;

class GomokuBot : public wxThread
{
    public:
        GomokuBot(wxGomokuFrame *frame, GomokuBoard *board = nullptr, GomokuGame *game = nullptr, int _difficulty=1);

        // bind gomoku game to bot
        void initiate(GomokuBoard *board, GomokuGame *game);

        // set AI level
        void setDifficulty(int _difficulty);

        // thread methods
        virtual ExitCode Entry();
        void WakeUp();

        virtual ~GomokuBot();

    private:
        wxGomokuFrame *main_frame;
        GomokuBoard *gomoku_board;
        GomokuGame *gomoku_game;
        int difficulty;

        wxMutex m;
        wxCondition *cond;
};

#endif // GOMOKUBOT_H
