
/*__________________________________________________
 * logFile.h
 *__________________________________________________
 *
 * class to handle a log file
 *
 */

#ifndef LOGFILE
#define LOGFILE

#include <stdio.h>
#include <string>

namespace output
{
    class LogFile 
    {
        public:
            LogFile(const std::string &fileName) ;
            ~LogFile() ;

            void printMessage(const std::string &message, bool endLine = false) ;
            void newLine() ;
            void separator(int length = 50, const char symbol = '_', bool endLine = false) ;

        private:
            void open(const char *fileName) ;
            bool _open ;
            FILE *_file ;
    } ;
}

#endif
