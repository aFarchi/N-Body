
/*__________________________________________________
 * NGPForce.cpp
 *__________________________________________________
 *
 * implementation of class NGPForce
 *
 */

#ifndef NGPFORCE_CPP
#define NGPFORCE_CPP

#include "NGPForce.h"
// floor
#include <math.h>
// indexRealField
#include "../../utils/indexing.h"

namespace PM
{

    template <typename IntegrationScheme>
        NGPForce<IntegrationScheme>::NGPForce() :
            _nParticles(0),
            _nGrid(0),
            _deltaT(0.0),
            _factor(1.0)
    {
    }

    template <typename IntegrationScheme>
        NGPForce<IntegrationScheme>::NGPForce(double *xvParticles, double *forceField, int nParticles, int nGrid, double cubeLength, double deltaT) :
            _xvParticles(xvParticles),
            _forceField(forceField),
            _nParticles(nParticles),
            _nGrid(nGrid),
            _deltaT(deltaT),
            _factor(nGrid/cubeLength)
    {
        _integrate = new IntegrationScheme() ;
    }

    template <typename IntegrationScheme>
        NGPForce<IntegrationScheme>::~NGPForce()
    {
        delete _integrate ;
    }

    template <typename IntegrationScheme>
        void NGPForce<IntegrationScheme>::operator()(int direction)
        {
            // Move particles 
            for ( int np = 0 ; np < _nParticles ; np++ )
            {
                int i        = floor( _xvParticles[6*np  ] * _factor ) ;
                int j        = floor( _xvParticles[6*np+1] * _factor ) ;
                int k        = floor( _xvParticles[6*np+2] * _factor ) ;
                double force = _forceField[utils::indexRealField(i, j, k, _nGrid)] ;

                (*_integrate)(&_xvParticles[6*np+direction], &_xvParticles[6*np+3+direction], force, _deltaT) ;
            }
        }


}

#endif

