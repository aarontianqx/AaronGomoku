/***************************************************************
 * Name:      wxGomokuEvents.cpp
 * Purpose:   Code for App Frame Events
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-25
 **************************************************************/

#include "wxGomokuEvents.h"


wxDEFINE_EVENT(EVT_CANVAS_CLICK, wxGomokuEvent);
wxDEFINE_EVENT(EVT_CANVAS_MOTION, wxGomokuEvent);
wxDEFINE_EVENT(EVT_BOT_PLAY, wxAIEvent);

wxGomokuEvent::wxGomokuEvent(PiecePosition _pos, wxEventType commandType)
    : wxEvent(0, commandType), piece_pos(_pos)
{
    //ctor
}

PiecePosition wxGomokuEvent::getPiecePosition() const
{
    return piece_pos;
}
/*
wxGomokuEvent::~wxGomokuEvent()
{
    //dtor
}
*/
wxAIEvent::wxAIEvent(PiecePosition _pos, wxEventType commandType)
    : wxThreadEvent(commandType), piece_pos(_pos)
{
    //ctor
}

PiecePosition wxAIEvent::getPiecePosition() const
{
    return piece_pos;
}
