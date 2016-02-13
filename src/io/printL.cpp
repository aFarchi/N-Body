
/*__________________________________________________
 * printL.cpp
 *__________________________________________________
 *
 * implementation of the io functions
 *
 */

#ifndef PRINTL_CPP
#define PRINTL_CPP

#include "printL.h"
// cout
#include <iostream>

namespace io
{

    void printParticleList(double *xvParticles, int nParticles)
    {
        for ( int np = 0 ; np < nParticles ; np++ )
        {
            std::cout << "Particle #" << np << std::endl ;
            std::cout << "x  = " << xvParticles[6*np  ] << std::endl ;
            std::cout << "y  = " << xvParticles[6*np+1] << std::endl ;
            std::cout << "z  = " << xvParticles[6*np+2] << std::endl ;
            std::cout << "vx = " << xvParticles[6*np+3] << std::endl ;
            std::cout << "vy = " << xvParticles[6*np+4] << std::endl ;
            std::cout << "vz = " << xvParticles[6*np+5] << std::endl ;
            std::cout << "__________________________________________________" << std::endl ;
        }
    }

}

#endif

