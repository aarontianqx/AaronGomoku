/***************************************************************
 * Name:      wxGomokuMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-15
 **************************************************************/

#include <wx/msgdlg.h>
#include "wxGomokuMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


wxGomokuFrame::wxGomokuFrame(wxFrame *parent)
    : wxGUIFrame(parent), gomoku_game(&gomoku_board)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
    canvas->setBoard(&gomoku_board);
    gomoku_game.clear();
    gomoku_bot = new GomokuAI(this, &gomoku_board, &gomoku_game, 3);
    gomoku_bot->Run();
}

wxGomokuFrame::~wxGomokuFrame()
{
}


void wxGomokuFrame::terminateGame()
{
}

void wxGomokuFrame::pauseGame()
{

}


void wxGomokuFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void wxGomokuFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void wxGomokuFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxGomokuFrame::OnStartGame(bool with_bot)
{
    PlayerRole r1 = PlayerRole::HUMAN, r2 = PlayerRole::HUMAN;
    if (with_bot)
        menuPlayerFirst->IsChecked() ? (r2 = PlayerRole::BOT) : (r1 = PlayerRole::BOT);
    player[0].setInfo("Player1", r1, PieceColor::BLACK);
    player[1].setInfo("Player2", r2, PieceColor::WHITE);

    gomoku_game.initiate(player[0].role, player[1].role);
    canvas->setLastPiece(PiecePosition::InvalidPiece);
    canvas->Refresh(false);
    if (gomoku_game.nextRole() == PlayerRole::BOT)
        gomoku_bot->WakeUp();

}

void wxGomokuFrame::OnSelectDifficulty(int level)
{
    gomoku_bot->setDifficulty(level);
}

void wxGomokuFrame::OnTimer(wxTimerEvent& event)
{
    // to finish

}

void wxGomokuFrame::OnCanvasClick(wxGomokuEvent& event)
{
    PiecePosition pos = event.getPiecePosition();
    assert(pos.isLegal());

    if (!gomoku_game.isActive() ||gomoku_game.nextRole() == PlayerRole::BOT)
        return;
    if (gomoku_game.tryPut(pos, gomoku_board.nextColor())){
        canvas->setLastPiece(pos);
        canvas->Refresh(false);
        if (!gomoku_game.isActive())
            showGameOverMsg();
        else if (gomoku_game.nextRole() == PlayerRole::BOT)
            gomoku_bot->WakeUp();
    }
}

void wxGomokuFrame::OnCanvasMotion(wxGomokuEvent& event)
{
    PiecePosition pos = event.getPiecePosition();
    if (!gomoku_game.isActive() || gomoku_game.nextRole() != PlayerRole::HUMAN)
        return;
    if (pos != canvas->tracePiece()){
        canvas->setTracePiece(pos);
        canvas->Refresh(false);
    }
}

void wxGomokuFrame::OnBotPlay(wxAIEvent& event)
{
    PiecePosition pos = event.getPiecePosition();
    assert(pos.isLegal());

    if (!gomoku_game.isActive() ||gomoku_game.nextRole() != PlayerRole::BOT)
        return;
    if (gomoku_game.tryPut(pos, gomoku_board.nextColor())){
        canvas->setLastPiece(pos);
        wxString timestr("this step spent "), nodestr;
        timestr<< event.getTime() << " ms";
        nodestr<< event.getNode() << " nodes calculated";
        GetStatusBar()->SetStatusText(timestr, 0);
        GetStatusBar()->SetStatusText(nodestr, 1);
        canvas->Refresh(false);

        if (!gomoku_game.isActive())
            showGameOverMsg();
        else if (gomoku_game.nextRole() == PlayerRole::BOT)
            gomoku_bot->WakeUp();
    }
}


void wxGomokuFrame::showGameOverMsg()
{
    int winnerID = gomoku_game.getWinner().isBlack()?0:1;
    if (player[0].role != player[1].role){
        if (player[winnerID].role == PlayerRole::HUMAN)
            wxMessageBox("You win!", "Game Over");
        else
            wxMessageBox("You lose!", "Game Over");
    }
}
