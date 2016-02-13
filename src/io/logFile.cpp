
/*__________________________________________________
 * logFile.cpp
 *__________________________________________________
 *
 * implementation of class LogFile
 *
 */

#ifndef LOGFILE_CPP
#define LOGFILE_CPP

#include "logfile.h"
// cout
#include <iostream>
// fopen, fclose
#include <stdio.h>

namespace io
{

    LogFile::LogFile() :
        _open(false)
    {
    }

    LogFile::LogFile(const std::string &fileName)
    {
        open(fileName.c_str()) ;
    }

    LogFile::~LogFile()
    {
        if ( _open )
        {
            fclose(_file) ;
            _open = false ;
        }
    }
    
    void LogFile::open(const char* fileName)
    {
        _file = fopen(fileName, "w") ;

        if ( _file )
        {
            _open = true ;
        }
        else
        {
            _open = false ;
            std::cout << "Could not open log file " << fileName << std::endl ;
        }
    }

    void LogFile::printMessage(const std::string &message, bool startNewLine, bool endLine)
    {
        if ( _open )
        {
            if ( startNewLine )
            {   
                newLine() ;
            }   

            fwrite(message.c_str(), sizeof(char), message.size(), _file) ;

            if ( endLine )
            {   
                newLine() ;
            }
        }
    } 
    
    void LogFile::newLine()
    {
        if ( _open )
        {
            fwrite("\n", sizeof(char), 1, _file) ;
        }
    }

    void LogFile::separator(int length, const char symbol, bool startNewLine, bool endLine)
    {   
        std::string message = "" ;

        for ( int i = 0 ; i < length ; i++ )
        {
            message += symbol ;
        }

        printMessage(message, startNewLine, endLine) ;
    }

    void LogFile::simpleSeparator(bool startNewLine, bool endLine)
    {
        separator(50, '_', startNewLine, endLine) ;
    }

    void LogFile::doubleSeparator(bool startNewLine, bool endLine)
    {
        separator(50, '=', startNewLine, endLine) ;
    }

}

#endif

