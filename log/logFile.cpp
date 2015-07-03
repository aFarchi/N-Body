#include "logfile.h"
#include <iostream>

namespace output
{
    LogFile::LogFile(const std::string &fileName)
    {
        if (fileName=="screen")
        {
            _file = NULL ;
            _open = false ;
        }
        else
        {
            open(fileName.c_str()) ;
        }
    }

    void LogFile::open(const char* fileName)
    {
        _file = fopen(fileName, "w") ;

        if (_file)
        {
            _open = true ;
        }
        else
        {
            _open = false ;
            std::cout << "Could not open log file " << fileName << std::endl ;
            std::cout << "Using screen instead" << std::endl ;
        }
    }

    LogFile::~LogFile()
    {
        if (_open)
        {
            fclose(_file) ;
            _open = false ;
        }
    }

    void LogFile::printMessage(const std::string &message, bool endLine)
    {
        if (_open)
        {
            fwrite(message.c_str(), sizeof(char), message.size(), _file) ;

            if (endLine)
            {
                fwrite("\n", sizeof(char), 1, _file) ;
            }
        }
        else
        {
            std::cout << message ;
            if (endLine)
            {
                std::cout << std::endl ;
            }
        }
    }
}

