/***************************************************************
 * Name:      GomokuAI.cpp
 * Purpose:   Code for Bot Thread
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-30
 **************************************************************/

#include "GomokuBot.h"
#include "Calculagraph.hpp"
#include "wxGomokuEvents.h"
#include "wxGomokuMain.h"

GomokuBot::GomokuBot(wxGomokuFrame *frame, GomokuBoard *board, GomokuGame *game, int _difficulty)
    : main_frame(frame), gomoku_board(board), gomoku_game(game), difficulty(_difficulty)
{
    cond = new wxCondition(m);
}

void GomokuBot::initiate(GomokuBoard *board, GomokuGame *game)
{
    assert(board != nullptr && game != nullptr);
    gomoku_board = board;
    gomoku_game = game;
}

void GomokuBot::setDifficulty(int _difficulty)
{
    difficulty = _difficulty;
}

void* GomokuBot::Entry()
{
    Calculagraph timer;
    m.Lock();

    while (!TestDestroy()){
        cond->Wait();

        uint32_t node;
        timer.initiate();
        timer.toggleStart();
        PiecePosition best = GomokuAI(gomoku_board, difficulty)(node);
        timer.toggleStop();

        wxAIEvent play_event(best, EVT_BOT_PLAY);
        play_event.setInfo(timer.get_msec(), node);

        main_frame->GetEventHandler()->ProcessThreadEvent(play_event);

    }
    return 0;
}

void GomokuBot::WakeUp()
{
    cond->Signal();
}

GomokuBot::~GomokuBot()
{
    delete cond;
}
