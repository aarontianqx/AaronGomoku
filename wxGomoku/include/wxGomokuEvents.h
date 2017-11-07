/***************************************************************
 * Name:      wxGomokuEvents.h
 * Purpose:   Defines for App Frame Events
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-25
 **************************************************************/

#ifndef WXGOMOKUEVENTS_H
#define WXGOMOKUEVENTS_H

#include <wx/event.h>
#include "GomokuPiece.h"

class wxGomokuEvent : public wxEvent
{
    public:
        wxGomokuEvent(PiecePosition _pos, wxEventType commandType);

        virtual wxEvent *Clone() const { return new wxGomokuEvent(*this); }
        PiecePosition getPiecePosition() const;
/*
        virtual ~wxGomokuEvent();
*/
    protected:

    private:
        PiecePosition piece_pos;

};

class wxAIEvent: public wxThreadEvent
{
    public:
        wxAIEvent(PiecePosition _pos, wxEventType commandType);

        virtual wxEvent *Clone() const { return new wxAIEvent(*this); }
        PiecePosition getPiecePosition() const;

        void setInfo(uint32_t time, uint32_t node) { time_spent = time, nodes_calculated = node; }
        uint32_t getTime() const { return time_spent; }
        uint32_t getNode() const { return nodes_calculated; }
    private:
        PiecePosition piece_pos;
        uint32_t time_spent;
        uint32_t nodes_calculated;
};

wxDECLARE_EVENT(EVT_CANVAS_CLICK, wxGomokuEvent);
wxDECLARE_EVENT(EVT_CANVAS_MOTION, wxGomokuEvent);
wxDECLARE_EVENT(EVT_BOT_PLAY, wxAIEvent);

#endif // WXGOMOKUEVENTS_H
