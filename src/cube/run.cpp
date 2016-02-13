
/*__________________________________________________
 * run.cpp
 *__________________________________________________
 *
 */

#ifndef RUN_CPP
#define RUN_CPP

#include "run.h"

// to string
#include "../patch/toString.cpp"

namespace run
{

    template <typename Cube, typename Log>
        Run<Cube, Log>::Run() :
            _nTStep(0),
            _nModPrint(1),
            _nModWrite(1),
            _prefixPL(),
            _suffixPL()
        {
        }

    template <typename Cube, typename Log>
        Run<Cube, Log>::Run(Cube *cube, int nTStep, int nModPrint, int nModWrite, const std::string &logFile,
                const std::string &prefixPL, const std::string &suffixPL) :
            _cube(cube),
            _nTStep(nTStep),
            _nModPrint(nModPrint),
            _nModWrite(nModWrite),
            _prefixPL(prefixPL),
            _suffixPL(suffixPL)
        {
            _log = new Log(logFile) ;
        }

    template <typename Cube, typename Log>
        Run<Cube, Log>::~Run()
        {
            delete _log ;
        }

    template <typename Cube, typename Log>
        void Run<Cube, Log>::operator()()
        {
            _log->printMessage(std::string("Starting simulation...")) ;
            _log->printMessage(std::string("nTStep    = ")+patch::to_string(_nTStep)) ;
            _log->printMessage(std::string("nModPrint = ")+patch::to_string(_nModPrint)) ;
            _log->printMessage(std::string("nModWrite = ")+patch::to_string(_nModWrite)) ;

            for ( int t = 0 ; t < _nTStep ; t++ )
            {
                if ( t % _nModPrint == 0 )
                {
                    _log->printMessage(std::string("Step ")+patch::to_string(t)) ;
                }

                _cube->stepForward() ;

                if ( t % _nModWrite == 0 )
                {
                    _cube->writeParticleList(_prefixPL+patch::to_string(t+1)+_suffixPL) ;
                }
            }
        }

    template <typename Cube, typename Log>
        void Run<Cube, Log>::initialize()
        {
            _log->doubleSeparator() ;
            _log->printMessage(_cube->printParameters()) ;
            _log->doubleSeparator() ;
            _log->printMessage(std::string("Initializing Cube...")) ;
            _cube->initialize() ;
            _cube->writeParticleList(_prefixPL+patch::to_string(0)+_suffixPL) ;
        }

}

#endif

