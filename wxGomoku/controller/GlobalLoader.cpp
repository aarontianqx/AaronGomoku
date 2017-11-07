/***************************************************************
 * Name:      GlobalLoader.cpp
 * Purpose:   Code for Config/Resource Loading
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-28
 **************************************************************/

#include "GlobalLoader.h"

wxJPEGHandler GlobalLoader::jpeg_handler;
wxPNGHandler GlobalLoader::png_handler;
std::map<std::string, int32_t> GlobalLoader::configs;
std::map<std::string, wxBitmap*> GlobalLoader::pictures;

const int32_t CANVAS_PANEL_LEFT = 0;
const int32_t CANVAS_PANEL_TOP = 0;
const int32_t CANVAS_PANEL_WIDTH = 600;
const int32_t CANVAS_PANEL_HEIGHT = 600;
const int32_t PIECE_RADIUS = 16;
const int32_t GRID_START_POSITION = 48;
const int32_t GRID_END_POSITION = 552;
const int32_t GRID_SIDE_LENGTH = 36;
const int32_t STAR_LEFT = 156;
const int32_t STAR_TOP = 156;
const int32_t STAR_MIDDLE_X = 300;
const int32_t STAR_MIDDLE_Y = 300;
const int32_t STAR_RIGHT = 444;
const int32_t STAR_DOWN = 444;
const int32_t STAR_RADIUS = 4;
const int32_t MAIN_WINDOW_LEFT = -1;
const int32_t MAIN_WINDOW_TOP = -1;
const int32_t MAIN_WINDOW_WIDTH = 600;
const int32_t MAIN_WINDOW_HEIGHT = 622;

const int32_t PATTERN_SCORE_WIN = 10000000;
const int32_t PATTERN_SCORE_L4 = 300000;
const int32_t PATTERN_SCORE_S4 = 3000;
const int32_t PATTERN_SCORE_CL3 = 2500;
const int32_t PATTERN_SCORE_JL3 = 1500;
const int32_t PATTERN_SCORE_S3 = 600;
const int32_t PATTERN_SCORE_L2 = 700;
const int32_t PATTERN_SCORE_S2A = 300;
const int32_t PATTERN_SCORE_S2B = 200;
const int32_t PATTERN_SCORE_S2C = 100;
const int32_t PATTERN_SCORE_ONE = 10;
const int32_t PATTERN_SCORE_NONE = 0;

const int32_t PATTERN_SCORE_D44 = 300000;
const int32_t PATTERN_SCORE_D43 = 200000;
const int32_t PATTERN_SCORE_D33 = 100000;
const int32_t PATTERN_SCORE_ML2 = 300;

GlobalLoader::GlobalLoader()
{
    //ctor
}

void GlobalLoader::loadConfig()
{
    configs["CanvasPanelLeft"] = CANVAS_PANEL_LEFT;
    configs["CanvasPanelTop"] = CANVAS_PANEL_TOP;
    configs["CanvasPanelWidth"] = CANVAS_PANEL_WIDTH;
    configs["CanvasPanelHeight"] = CANVAS_PANEL_HEIGHT;
    configs["PieceRadius"] = PIECE_RADIUS;
    configs["GridStartPosition"] = GRID_START_POSITION;
    configs["GridEndPosition"] = GRID_END_POSITION;
    configs["GridSideLength"] = GRID_SIDE_LENGTH;
    configs["StarLeft"] = STAR_LEFT;
    configs["StarTop"] = STAR_TOP;
    configs["StarMiddleX"] = STAR_MIDDLE_X;
    configs["StarMiddleY"] = STAR_MIDDLE_Y;
    configs["StarRight"] = STAR_RIGHT;
    configs["StarDown"] = STAR_DOWN;
    configs["StarRadius"] = STAR_RADIUS;
    configs["MainWindowLeft"] = MAIN_WINDOW_LEFT;
    configs["MainWindowTop"] = MAIN_WINDOW_TOP;
    configs["MainWindowWidth"] = MAIN_WINDOW_WIDTH;
    configs["MainWindowHeight"] = MAIN_WINDOW_HEIGHT;

    configs["PatternScoreWin"] = PATTERN_SCORE_WIN;
    configs["PatternScoreL4"] = PATTERN_SCORE_L4;
    configs["PatternScoreS4"] = PATTERN_SCORE_S4;
    configs["PatternScoreCL3"] = PATTERN_SCORE_CL3;
    configs["PatternScoreJL3"] = PATTERN_SCORE_JL3;
    configs["PatternScoreS3"] = PATTERN_SCORE_S3;
    configs["PatternScoreL2"] = PATTERN_SCORE_L2;
    configs["PatternScoreS2A"] = PATTERN_SCORE_S2A;
    configs["PatternScoreS2B"] = PATTERN_SCORE_S2B;
    configs["PatternScoreS2C"] = PATTERN_SCORE_S2C;
    configs["PatternScoreOne"] = PATTERN_SCORE_ONE;
    configs["PatternScoreNone"] = PATTERN_SCORE_NONE;
    configs["PatternScoreD44"] = PATTERN_SCORE_D44;
    configs["PatternScoreD43"] = PATTERN_SCORE_D43;
    configs["PatternScoreD33"] = PATTERN_SCORE_D33;
    configs["PatternScoreML2"] = PATTERN_SCORE_ML2;
}

void GlobalLoader::loadPic()
{
    wxImage::AddHandler(&jpeg_handler);
    wxImage::AddHandler(&png_handler);
    pictures["GomokuBoard"] = new wxBitmap(wxString("resource/board.jpg"), wxBITMAP_TYPE_JPEG);
    pictures["BlackPiece"] = new wxBitmap(wxString("resource/black.png"), wxBITMAP_TYPE_PNG);
    pictures["WhitePiece"] = new wxBitmap(wxString("resource/white.png"), wxBITMAP_TYPE_PNG);
}

const wxBitmap* GlobalLoader::getPic(const std::string& key)
{
    return pictures.at(key);
}

int32_t GlobalLoader::getConfig(const std::string& key)
{
    return configs.at(key);
}
GlobalLoader::~GlobalLoader()
{
    //dtor
}
