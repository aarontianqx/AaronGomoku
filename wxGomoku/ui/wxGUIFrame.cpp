///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////


#include "wxGUIFrame.h"


///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE( wxGUIFrame, wxFrame )
    EVT_CLOSE( wxGUIFrame::_wxFB_OnClose )
    EVT_MENU( idMenuQuit, wxGUIFrame::_wxFB_OnQuit )
    EVT_MENU( idMenuAbout, wxGUIFrame::_wxFB_OnAbout )
    EVT_MENU( idMenuVSBot, wxGUIFrame::_wxFB_OnPlayWithBot )
    EVT_MENU( idMenuVSPlayer, wxGUIFrame::_wxFB_OnPlayWithPlayer )
    EVT_MENU( idMenuDifficulty1, wxGUIFrame::_wxFB_OnSelectDifficulty1 )
    EVT_MENU( idMenuDifficulty2, wxGUIFrame::_wxFB_OnSelectDifficulty2 )
    EVT_MENU( idMenuDifficulty3, wxGUIFrame::_wxFB_OnSelectDifficulty3 )
    EVT_MENU( idMenuDifficulty4, wxGUIFrame::_wxFB_OnSelectDifficulty4 )
    EVT_TIMER( idTimer, wxGUIFrame::_wxFB_OnTimer )
END_EVENT_TABLE()


wxGUIFrame::wxGUIFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style )
    : wxFrame( parent, id, title, pos, size, style ),
      poller(this, idTimer)
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    mbar = new wxMenuBar( 0 );

    wxMenu* fileMenu;
    fileMenu = new wxMenu();
    wxMenuItem* menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
    fileMenu->Append( menuFileQuit );
    mbar->Append( fileMenu, wxT("&File") );

    wxMenu* gameMenu;
    gameMenu = new wxMenu();
    // vs Player/Bot
    wxMenuItem* menuVSBot = new wxMenuItem(gameMenu, idMenuVSBot, wxString( wxT("VS &Bot") ) + wxT('\t') + wxT("Ctrl+B"), wxT("Play with Computer"), wxITEM_NORMAL);
    gameMenu->Append(menuVSBot);
    wxMenuItem* menuVSPlayer = new wxMenuItem(gameMenu, idMenuVSPlayer, wxString( wxT("VS &Player") ) + wxT('\t') + wxT("Ctrl+P"), wxT("Play with Player"), wxITEM_NORMAL);
    gameMenu->Append(menuVSPlayer);
    // Choose Black/White
    menuPlayerFirst = new wxMenuItem(gameMenu, idMenuPlayerFirst, wxString( wxT("Player First")), wxEmptyString, wxITEM_CHECK);
    gameMenu->Append(menuPlayerFirst);
    menuPlayerFirst->Check(true);
    // Select Difficulty
    wxMenu* menuDifficulty = new wxMenu();
    menuDifficulty->AppendRadioItem(idMenuDifficulty1, wxString( wxT("Level 1") ));
    menuDifficulty->AppendRadioItem(idMenuDifficulty2, wxString( wxT("Level 2") ));
    menuDifficulty->AppendRadioItem(idMenuDifficulty3, wxString( wxT("Level 3") ));
    menuDifficulty->AppendRadioItem(idMenuDifficulty4, wxString( wxT("Level 4") ));
    gameMenu->AppendSubMenu(menuDifficulty, wxString( wxT("Select Difficulty")));
    menuDifficulty->Check(idMenuDifficulty3, true);
    mbar->Append(gameMenu, wxT("&Game"));

    wxMenu* helpMenu;
    helpMenu = new wxMenu();
    wxMenuItem* menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
    helpMenu->Append( menuHelpAbout );
    mbar->Append( helpMenu, wxT("&Help") );

    this->SetMenuBar( mbar );

    statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );

    mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), GetSize());
    canvas = new wxGomokuCanvas(mainPanel, this);

    CentreOnScreen();

    Bind(EVT_CANVAS_CLICK, &wxGUIFrame::_wxFB_OnCanvasClick, this, wxID_ANY);
    Bind(EVT_CANVAS_MOTION, &wxGUIFrame::_wxFB_OnCanvasMotion, this, wxID_ANY);
    Bind(EVT_BOT_PLAY, &wxGUIFrame::_wxFB_OnBotPlay, this, wxID_ANY);
}
