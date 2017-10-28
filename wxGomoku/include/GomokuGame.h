/***************************************************************
 * Name:      GomokuGame.h
 * Purpose:   Defines for Gomoku Game
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-17
 **************************************************************/

#ifndef GOMOKUGAME_H_INCLUDED
#define GOMOKUGAME_H_INCLUDED

#include <mutex>
#include "GomokuElements.h"


enum PlayerRole
{
    HUMAN,
    BOT,
};

class GomokuGame
{
public:
    typedef std::timed_mutex Mutex_T;
    typedef std::lock_guard<Mutex_T> LockGuard_T;
    typedef std::unique_lock<Mutex_T> TryLock_T;

    GomokuGame(GomokuBoard *_pboard);
    void clear(PlayerRole _black_player = HUMAN, PlayerRole _white_player = BOT);
    void initiate(PlayerRole _black_player = HUMAN, PlayerRole _white_player = BOT);
    bool isActive() const;
    PieceColor getWinner() const;
    PlayerRole blackSide() const { return black_side; }
    PlayerRole whiteSide() const { return white_side; }
    PlayerRole nextRole() const;
    TryLock_T tryAcquireLock();

    // all these functions must be called under lock
    bool tryPut(int x, int y, PieceColor color);
    bool tryPut(PiecePosition p, PieceColor color);
    bool tryWithdraw();

private:
    GomokuBoard *pboard;
    bool game_active;
    PlayerRole black_side;
    PlayerRole white_side;
    PieceColor winner;
    Mutex_T m;
};

#endif // GOMOKUGAME_H_INCLUDED
