
/*__________________________________________________
 * initializeRandom.cpp
 *__________________________________________________
 *
 * implementation of class InitializeRandom
 *
 */

#ifndef INITIALIZERANDOM_CPP
#define INITIALIZERANDOM_CPP

#include "initializeRandom.h"
// srand, rand, RAND_MAX
#include <stdlib.h>
// time
#include <time.h>
// cout 
#include <iostream>

namespace initialize
{

    InitializeRandom::InitializeRandom() :
        _nParticles(0),
        _cubeLength(0.0)
    {
    }

    InitializeRandom::InitializeRandom(double *xvParticles, int nParticles, double cubeLength) :
        _xvParticles(xvParticles),
        _nParticles(nParticles),
        _cubeLength(cubeLength)
    {
    }

    void InitializeRandom::operator()()
    {
        srand(time(NULL)) ;

        //std::cout << "Starting initialization... " << std::endl ;
        //std::cout << "nParticles = " << _nParticles << std::endl ;

        for ( int np = 0 ; np < _nParticles ; np++ )
        {   
            for ( int dim = 0 ; dim < 3 ; dim ++ )
            {   
                _xvParticles[6*np+dim]   = _cubeLength * ( (double) rand() / (RAND_MAX) ) ; 
                _xvParticles[6*np+3+dim] = 0.0 ;
                //std::cout << _xvParticles[6*np+dim] << std::endl ;
            }   
        }
    }

}

#endif

