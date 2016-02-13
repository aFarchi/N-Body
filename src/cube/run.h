
/*__________________________________________________
 * run.h
 *__________________________________________________
 *
 * run class
 *
 */

#ifndef RUN_H
#define RUN_H

// string 
#include <string>

namespace run
{
    
    template <typename Cube, typename Log>
        class Run
        {
            public:
                Run() ;
                Run(Cube *cube, int nTStep, int nModPrint, int nModWrite, const std::string &logFile,
                        const std::string &prefixPL, const std::string &suffixPL) ;
                ~Run() ;
                void operator()() ;
                void initialize() ;

            private:
                Cube             *_cube ;
                Log              *_log ;

                const int         _nTStep ;
                const int         _nModPrint ;
                const int         _nModWrite ;

                const std::string _prefixPL ;
                const std::string _suffixPL ;
        };

}

#endif

