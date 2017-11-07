/***************************************************************
 * Name:      GomokuGame.cpp
 * Purpose:   Code for Gomoku Game
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-17
 **************************************************************/

#include "GomokuGame.h"


GomokuGame::GomokuGame(GomokuBoard *_pboard)
    :pboard(_pboard), game_active(false)
{ }

void GomokuGame::initiate(PlayerRole _black_player, PlayerRole _white_player)
{
    clear(_black_player, _white_player);
    game_active = true;
}

void GomokuGame::clear(PlayerRole _black_player, PlayerRole _white_player)
{
    LockGuard_T lock(m);
    pboard->reset();
    game_active = false;
    black_side = _black_player;
    white_side = _white_player;
    winner = PieceColor::BLANK;
}

bool GomokuGame::isActive() const
{
    return game_active;
}

PieceColor GomokuGame::getWinner() const
{
    return winner;
}

PlayerRole GomokuGame::nextRole() const
{
    return pboard->nextColor().isBlack()?black_side:white_side;
}

auto GomokuGame::tryAcquireLock()
    ->GomokuGame::TryLock_T
{
    return TryLock_T(m, std::chrono::milliseconds(10));
}

bool GomokuGame::tryPut(PiecePosition pos, PieceColor color)
{
    if (!pboard->at(pos).isBlank() || color != pboard->nextColor())
        return false;
    pboard->put(pos);
    if (pboard->pieceCount() == 225){
        winner = PieceColor::WHITE;
        game_active = false;
    }
    else if (pboard->checkWin(pos, color)){
        winner = color;
        game_active = false;
    }
    return true;
}

bool GomokuGame::tryPut(int x, int y, PieceColor color)
{
    return tryPut(PiecePosition(x, y), color);
}

bool GomokuGame::tryWithdraw()
{
    // to finish
    return false;
}
