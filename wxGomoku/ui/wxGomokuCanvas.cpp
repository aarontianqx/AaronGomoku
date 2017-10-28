/***************************************************************
 * Name:      wxGomokuCanvas.cpp
 * Purpose:   Code for Gomoku Board GUI
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-17
 **************************************************************/

#include <wx/geometry.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include "GlobalLoader.h"
#include "wxGomokuCanvas.h"
#include "wxGomokuMain.h"

BEGIN_EVENT_TABLE( wxGomokuCanvas, wxPanel )
    EVT_MOTION( wxGomokuCanvas::OnMouseMove )
    EVT_LEFT_DOWN( wxGomokuCanvas::OnMouseDown )
    EVT_ERASE_BACKGROUND( wxGomokuCanvas::OnEraseBackground )
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
    return wxPoint( GridStartPosition +_pos.x * GridSideLength - radius,
                    GridStartPosition +_pos.y * GridSideLength - radius);
}

PiecePosition wxGomokuCanvas::_PointtoPiecePosition(wxPoint _point)
{
    static int _half = GridSideLength / 2;
    static int _start = GridStartPosition - GridSideLength / 2;
    PiecePosition pos( (_point.x - _start) / GridSideLength,
                       (_point.y - _start) / GridSideLength );
    if (!pos.isLegal())
        return PiecePosition::InvalidPiece;
    wxPoint2DInt target_point(GridStartPosition + pos.x * GridSideLength,
                              GridStartPosition + pos.y * GridSideLength);
    double distance = target_point.GetDistance(wxPoint2DInt(_point));
    if (distance > _half)
        return PiecePosition::InvalidPiece;
    return pos;
}


void wxGomokuCanvas::OnMouseMove(wxMouseEvent &event)
{
    // turn canvas coord to piece position
    PiecePosition mouse_pos = _PointtoPiecePosition(event.GetPosition());
    if (mouse_pos == trace_piece || (mouse_pos.isLegal() && !board->at(mouse_pos).isBlank()))
        return;

    wxGomokuEvent motion_event(mouse_pos, EVT_CANVAS_MOTION);
    main_frame->ProcessWindowEvent(motion_event);
}

void wxGomokuCanvas::OnMouseDown(wxMouseEvent& event)
{
    // turn canvas coord to piece position
    PiecePosition mouse_pos = _PointtoPiecePosition(event.GetPosition());
    if (!mouse_pos.isLegal() || !board->at(mouse_pos).isBlank())
        return;

    wxGomokuEvent click_event(mouse_pos, EVT_CANVAS_CLICK);
    main_frame->ProcessWindowEvent(click_event);
}

void wxGomokuCanvas::OnEraseBackground(wxEraseEvent &event)
{
    wxDC *painter = event.GetDC();
    painter->DrawBitmap(*boardPic, 0, 0);
    painter->SetPen(wxPen(*wxBLACK, 2));
    for (auto i=GridStartPosition; i<=GridEndPosition; i+=GridSideLength){
        painter->DrawLine(GridStartPosition, i, GridEndPosition, i);
        painter->DrawLine(i, GridStartPosition, i, GridEndPosition);
    }
    painter->SetBrush(*wxBLACK_BRUSH);
    painter->DrawCircle(StarLeft, StarTop, StarRadius);
    painter->DrawCircle(StarRight, StarTop, StarRadius);
    painter->DrawCircle(StarMiddleX, StarMiddleY, StarRadius);
    painter->DrawCircle(StarLeft, StarDown, StarRadius);
    painter->DrawCircle(StarRight, StarDown, StarRadius);

    // for debugging
/*    wxSize panelSize = GetParent()->GetSize();
    wxPoint position = GetParent()->GetPosition();
    wxString status;
    status << "panel position: (" << position.x << ", " << position.y << ") ";
    status << "size: (" << panelSize.GetWidth() << ", " << panelSize.GetHeight() << ")";
    main_frame->GetStatusBar()->SetStatusText(status);*/
}

void wxGomokuCanvas::OnPaint(wxPaintEvent &event)
{
    wxClientDC painter(this);
    painter.SetBrush(*wxTRANSPARENT_BRUSH);

    for (int x=0; x<TABLESIZE; x++)
        for (int y=0; y<TABLESIZE; y++){
            PieceColor color = board->at(x, y);
            if (!color.isBlank())
                painter.DrawBitmap(color.isBlack()?*blackPic:*whitePic,
                                   _PiecePositiononCanvas(PiecePosition(x, y), PieceRadius));
        }
    if (trace_piece.isLegal() && board->at(trace_piece).isBlank())
        painter.DrawBitmap(board->nextColor().isBlack()?*blackPic:*whitePic,
                           _PiecePositiononCanvas(trace_piece, PieceRadius));
    painter.SetBrush(*wxGREY_BRUSH);
    if (last_piece.isLegal())
        painter.DrawCircle(_PiecePositiononCanvas(last_piece, 1), 4);
}
