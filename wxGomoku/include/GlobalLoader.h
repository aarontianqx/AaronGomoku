/***************************************************************
 * Name:      GlobalLoader.h
 * Purpose:   Defines for Config/Resource Loading
 * Author:    Aaron Tian (aarontianqx@hotmail.com)
 * Created:   2017-10-28
 **************************************************************/


#ifndef GLOBALLOADER_H
#define GLOBALLOADER_H

#include <map>
#include <string>
#include <wx/bitmap.h>

class GlobalLoader
{
    public:
        GlobalLoader();

        static
        void loadConfig();
        static
        int32_t getConfig(const std::string& key);

        static
        void loadPic();
        static const
        wxBitmap* getPic(const std::string& key);

        virtual ~GlobalLoader();

    private:
        static wxJPEGHandler jpeg_handler;
        static wxPNGHandler png_handler;
        static std::map<std::string, int32_t> configs;
        static std::map<std::string, wxBitmap*> pictures;
};

#define GETCONFIG(S) GlobalLoader::getConfig(S)
#define GETPIC(S) GlobalLoader::getPic(S)

#endif // GLOBALLOADER_H
