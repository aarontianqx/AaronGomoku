/***************************************************************
 * Name:      wxGomokuCanvas.cpp
 * Purpose:   Code for Gomoku Board GUI
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-17
 **************************************************************/

#include <wx/geometry.h>
#include <wx/dcbuffer.h>
#include "GlobalLoader.h"
#include "wxGomokuCanvas.h"
#include "wxGomokuMain.h"

BEGIN_EVENT_TABLE( wxGomokuCanvas, wxPanel )
    EVT_MOTION( wxGomokuCanvas::OnMouseMove )
    EVT_LEFT_DOWN( wxGomokuCanvas::OnMouseDown )
    EVT_PAINT( wxGomokuCanvas::OnPaint )
END_EVENT_TABLE()

wxGomokuCanvas::wxGomokuCanvas(wxWindow *parent, wxGUIFrame *_main_frame)
    : wxPanel(parent, wxID_ANY, wxPoint(GETCONFIG("CanvasPanelLeft"), GETCONFIG("CanvasPanelTop")),
              wxSize(GETCONFIG("CanvasPanelWidth"), GETCONFIG("CanvasPanelHeight")), wxTAB_TRAVERSAL|wxNO_BORDER),
      main_frame(_main_frame), trace_piece(PiecePosition::InvalidPiece), last_piece(PiecePosition::InvalidPiece)
{
    PieceRadius = GETCONFIG("PieceRadius");
    GridStartPosition = GETCONFIG("GridStartPosition");
    GridEndPosition = GETCONFIG("GridEndPosition");
    GridSideLength = GETCONFIG("GridSideLength");
    StarLeft = GETCONFIG("StarLeft");
    StarTop = GETCONFIG("StarTop");
    StarMiddleX = GETCONFIG("StarMiddleX");
    StarMiddleY = GETCONFIG("StarMiddleY");
    StarRight = GETCONFIG("StarRight");
    StarDown = GETCONFIG("StarDown");
    StarRadius = GETCONFIG("StarRadius");
    boardPic = GETPIC("GomokuBoard");
    blackPic = GETPIC("BlackPiece");
    whitePic = GETPIC("WhitePiece");
}

void wxGomokuCanvas::setBoard(const GomokuBoard *_board)
{
    board = _board;
}

wxGomokuCanvas::~wxGomokuCanvas()
{

}

wxPoint wxGomokuCanvas::_PiecePositiononCanvas(PiecePosition _pos, int radius)
{
    assert(_pos.isLegal());
    return wxPoint( GridStartPosition +_pos.getX() * GridSideLength - radius,
                    GridStartPosition +_pos.getY() * GridSideLength - radius);
}

PiecePosition wxGomokuCanvas::_PointtoPiecePosition(wxPoint _point)
{
    static int _half = GridSideLength / 2;
    static int _start = GridStartPosition - GridSideLength / 2;
    PiecePosition pos( (_point.x - _start) / GridSideLength,
                       (_point.y - _start) / GridSideLength );
    if (!pos.isLegal())
        return PiecePosition::InvalidPiece;
    wxPoint2DInt target_point(GridStartPosition + pos.getX() * GridSideLength,
                              GridStartPosition + pos.getY() * GridSideLength);
    double distance = target_point.GetDistance(wxPoint2DInt(_point));
    if (distance > _half)
        return PiecePosition::InvalidPiece;
    return pos;
}


void wxGomokuCanvas::OnMouseMove(wxMouseEvent &event)
{
    // turn canvas coord to piece position
    PiecePosition mouse_pos = _PointtoPiecePosition(event.GetPosition());
    if (mouse_pos == trace_piece || board->at(mouse_pos).isInvalid())
        return;

    wxGomokuEvent motion_event(mouse_pos, EVT_CANVAS_MOTION);
    main_frame->ProcessWindowEvent(motion_event);
}

void wxGomokuCanvas::OnMouseDown(wxMouseEvent& event)
{
    // turn canvas coord to piece position
    PiecePosition mouse_pos = _PointtoPiecePosition(event.GetPosition());
    if (!board->at(mouse_pos).isBlank())
        return;

    wxGomokuEvent click_event(mouse_pos, EVT_CANVAS_CLICK);
    main_frame->ProcessWindowEvent(click_event);
}

void wxGomokuCanvas::OnPaint(wxPaintEvent &event)
{
    wxBufferedPaintDC painter(this);

    // draw background
    painter.DrawBitmap(*boardPic, 0, 0);
    painter.SetPen(wxPen(*wxBLACK, 2));
    for (auto i=GridStartPosition; i<=GridEndPosition; i+=GridSideLength){
        painter.DrawLine(GridStartPosition, i, GridEndPosition, i);
        painter.DrawLine(i, GridStartPosition, i, GridEndPosition);
    }
    painter.SetBrush(*wxBLACK_BRUSH);
    painter.DrawCircle(StarLeft, StarTop, StarRadius);
    painter.DrawCircle(StarRight, StarTop, StarRadius);
    painter.DrawCircle(StarMiddleX, StarMiddleY, StarRadius);
    painter.DrawCircle(StarLeft, StarDown, StarRadius);
    painter.DrawCircle(StarRight, StarDown, StarRadius);

    // draw pieces
    painter.SetBrush(*wxTRANSPARENT_BRUSH);
    for(PiecePosition pos: GomokuBoard::validPoints()){
        PieceColor color = board->at(pos);
        if (color.isBlack())
            painter.DrawBitmap(*blackPic, _PiecePositiononCanvas(pos, PieceRadius));
        else if (color.isWhite())
            painter.DrawBitmap(*whitePic, _PiecePositiononCanvas(pos, PieceRadius));
    }

    // draw trace piece
    if (trace_piece.isLegal() && board->at(trace_piece).isBlank())
        painter.DrawBitmap(board->nextColor().isBlack()?*blackPic:*whitePic,
                           _PiecePositiononCanvas(trace_piece, PieceRadius));

    // mark last piece
    painter.SetBrush(*wxGREY_BRUSH);
    if (last_piece.isLegal())
        painter.DrawCircle(_PiecePositiononCanvas(last_piece, 1), 4);
}
