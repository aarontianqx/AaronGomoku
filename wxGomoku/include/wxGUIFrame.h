///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXGUIFrame__
#define __WXGUIFrame__


#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/event.h>
#include <wx/timer.h>
#include "GlobalLoader.h"
#include "wxGomokuEvents.h"
#include "wxGomokuCanvas.h"
///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001
#define idMenuVSBot 1010
#define idMenuVSPlayer 1011
#define idMenuPlayerFirst 1012
#define idMenuDifficulty1 1013
#define idMenuDifficulty2 1014
#define idMenuDifficulty3 1015
#define idMenuDifficulty4 1016
#define idTimer  1100


///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class wxGUIFrame : public wxFrame
{
    DECLARE_EVENT_TABLE()
    private:

        // Private event handlers
        void _wxFB_OnClose( wxCloseEvent& event ){ OnClose(event); }
        void _wxFB_OnQuit( wxCommandEvent& event ){ OnQuit(event); }
        void _wxFB_OnAbout( wxCommandEvent& event ){ OnAbout(event); }
        void _wxFB_OnPlayWithBot( wxCommandEvent& event ){ OnStartGame(true); }
        void _wxFB_OnPlayWithPlayer( wxCommandEvent& event ){ OnStartGame(false); }
        void _wxFB_OnSelectDifficulty1( wxCommandEvent& event ) { OnSelectDifficulty(1); }
        void _wxFB_OnSelectDifficulty2( wxCommandEvent& event ) { OnSelectDifficulty(2); }
        void _wxFB_OnSelectDifficulty3( wxCommandEvent& event ) { OnSelectDifficulty(3); }
        void _wxFB_OnSelectDifficulty4( wxCommandEvent& event ) { OnSelectDifficulty(4); }

        void _wxFB_OnTimer( wxTimerEvent& event ){ OnTimer( event ); }
        void _wxFB_OnCanvasClick( wxGomokuEvent& event ) { OnCanvasClick(event); }
        void _wxFB_OnCanvasMotion(wxGomokuEvent& event) { OnCanvasMotion(event); }
        void _wxFB_OnBotPlay(wxAIEvent& event) { OnBotPlay(event); }


    protected:
        wxMenuBar* mbar;
        wxMenuItem* menuPlayerFirst;
        wxStatusBar* statusBar;

        wxPanel* mainPanel;
        wxGomokuCanvas *canvas;

        wxTimer poller;

        // Virtual event handlers, overide them in your derived class
        virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
        virtual void OnQuit( wxCommandEvent& event ){ event.Skip(); }
        virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
        virtual void OnStartGame(bool with_bot = true){}
        virtual void OnSelectDifficulty(int level) {}


        virtual void OnTimer( wxTimerEvent& event ){ event.Skip(); }
        virtual void OnCanvasClick( wxGomokuEvent& event ) { event.Skip(); }
        virtual void OnCanvasMotion(wxGomokuEvent& event) { event.Skip(); }
        virtual void OnBotPlay(wxAIEvent& event) { event.Skip(); }

    public:
        wxGUIFrame( wxWindow* parent, int id = wxID_ANY, wxString title = _("Gomoku") + " by Aaron Tian",
                    wxPoint pos = wxPoint(GETCONFIG("MainWindowLeft"), GETCONFIG("MainWindowTop")),
                    wxSize size = wxSize(GETCONFIG("MainWindowWidth"), GETCONFIG("MainWindowHeight")),
                    int style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

};


#endif //__WXGUIFrame__
