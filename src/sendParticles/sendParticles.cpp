
/*__________________________________________________
 * sendParticles.cpp
 *__________________________________________________
 *
 */

#ifndef SENDPARTICLES_CPP
#define SENDPARTICLES_CPP

#include "sendParticles.h"
// modulus
#include "../patch/modulus.h"

namespace send
{

    ParticleSender::ParticleSender() :
        _nParticles(0),
        _cubeLength(0.0)
    {
    }

    ParticleSender::ParticleSender(double *xvParticles, int nParticles, double cubeLength) :
        _xvParticles(xvParticles),
        _nParticles(nParticles),
        _cubeLength(cubeLength)
    {
    }

    void ParticleSender::operator()()
    {
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            for ( int dim = 0 ; dim < 3 ; dim++ )
            {
                _xvParticles[6*np+dim] = patch::modulus(_xvParticles[6*np+dim], _cubeLength) ;
            }
        }
    }

}

#endif

