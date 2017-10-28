/***************************************************************
 * Name:      PlayerInfo.h
 * Purpose:   defines for Player Info
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-23
 **************************************************************/

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "GomokuGame.h"

class PlayerInfo
{
    public:
        void setInfo(wxString _name, PlayerRole _role, PieceColor _color)
        {
            name = _name;
            role = _role;
            color = _color;
        }

        wxString name;
        PlayerRole role;
        PieceColor color;
};

#endif // PLAYERINFO_H
