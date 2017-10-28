/***************************************************************
 * Name:      wxGomokuApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-15
 **************************************************************/

#include "wxGomokuApp.h"
#include "wxGomokuMain.h"
#include "GlobalLoader.h"

IMPLEMENT_APP(wxGomokuApp);

bool wxGomokuApp::OnInit()
{
    GlobalLoader::loadConfig();
    GlobalLoader::loadPic();
    wxGomokuFrame* frame = new wxGomokuFrame(0L);
    frame->Show();

    return true;
}
