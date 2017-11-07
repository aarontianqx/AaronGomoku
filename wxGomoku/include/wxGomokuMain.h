/***************************************************************
 * Name:      wxGomokuMain.h
 * Purpose:   Defines Application Frame
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-15
 **************************************************************/

#ifndef WXGOMOKUMAIN_H
#define WXGOMOKUMAIN_H



#include "wxGomokuApp.h"
#include "wxGUIFrame.h"
#include "wxGomokuCanvas.h"
#include "GomokuGame.h"
#include "PlayerInfo.h"
#include "GomokuBot.h"


class wxGomokuFrame: public wxGUIFrame
{
    public:
        wxGomokuFrame(wxFrame *parent);
        ~wxGomokuFrame();

        void terminateGame();
        void pauseGame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnStartGame(bool with_bot = true);
        virtual void OnSelectDifficulty(int level);


        virtual void OnTimer(wxTimerEvent& event);
        virtual void OnCanvasClick(wxGomokuEvent& event);
        virtual void OnCanvasMotion(wxGomokuEvent& event);
        virtual void OnBotPlay(wxAIEvent& event);

        void showGameOverMsg();

        GomokuBoard gomoku_board;
        GomokuGame gomoku_game;
        PlayerInfo player[2];
        GomokuBot *gomoku_bot;
};

#endif // WXGOMOKUMAIN_H
