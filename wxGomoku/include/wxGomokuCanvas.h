/***************************************************************
 * Name:      wxGomokuCanvas.h
 * Purpose:   Defines for Gomoku Board GUI
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-17
 **************************************************************/

#ifndef WXGOMOKUCANVAS_H
#define WXGOMOKUCANVAS_H

#include "GomokuGame.h"
#include <wx/panel.h>
#include <wx/bitmap.h>

class wxGUIFrame;

class wxGomokuCanvas: public wxPanel
{
    DECLARE_EVENT_TABLE()

    public:
        wxGomokuCanvas(wxWindow *parent, wxGUIFrame *_main_frame);
        void setBoard(const GomokuBoard *_board);
        virtual ~wxGomokuCanvas();

        void setTracePiece(PiecePosition _trace_piece) { trace_piece = _trace_piece; }
        void setLastPiece(PiecePosition _last_piece) { last_piece = _last_piece; }
        PiecePosition tracePiece() const { return trace_piece; }
        PiecePosition lastPiece() const { return last_piece; }
    protected:
        void OnMouseMove(wxMouseEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnMouseDown(wxMouseEvent& event);

        wxPoint _PiecePositiononCanvas(PiecePosition _pos, int radius);
        PiecePosition _PointtoPiecePosition(wxPoint _point);

    private:
        wxGUIFrame *main_frame;
        const GomokuBoard *board;

        int32_t PieceRadius;
        int32_t GridStartPosition;
        int32_t GridEndPosition;
        int32_t GridSideLength;
        int32_t StarLeft;
        int32_t StarTop;
        int32_t StarMiddleX;
        int32_t StarMiddleY;
        int32_t StarRight;
        int32_t StarDown;
        int32_t StarRadius;
        const wxBitmap *boardPic;
        const wxBitmap *blackPic;
        const wxBitmap *whitePic;

        PiecePosition trace_piece;
        PiecePosition last_piece;
};

#endif // WXGOMOKUCANVAS_H
