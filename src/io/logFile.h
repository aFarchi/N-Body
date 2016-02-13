
/*__________________________________________________
 * logFile.h
 *__________________________________________________
 *
 * class to handle a log file
 *
 */

#ifndef LOGFILE_H
#define LOGFILE_H

// string
#include <string>

namespace io
{

    class LogFile 
    {
        public:
            LogFile() ;
            LogFile(const std::string &fileName) ;
            ~LogFile() ;

            void printMessage(const std::string &message, bool startNewLine = false, bool endLine = true) ;
            void newLine() ;
            void simpleSeparator(bool startNewLine = false, bool endLine = true) ;
            void doubleSeparator(bool startNewLine = false, bool endLine = true) ;
            void separator(int length = 50, const char symbol = '_', bool startNewLine = false, bool endLine = true) ;

        private:
            void open(const char *fileName) ;
            bool _open ;
            FILE *_file ;
    } ;

}

#endif
