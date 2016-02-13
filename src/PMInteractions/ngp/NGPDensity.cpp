
/*__________________________________________________
 * NGPDensity.cpp
 *__________________________________________________
 *
 * implementation of class NGPDensity
 *
 */

#ifndef NGPDENSITY_CPP
#define NGPDENSITY_CPP

#include "NGPDensity.h"
// floor
#include <math.h>
// indexRealField
#include "../../utils/indexing.h"

namespace PM
{

    NGPDensity::NGPDensity() :
        _nParticles(0),
        _nGrid(0),
        _realSize(0),
        _factor(0.0),
        _particleMass(1.0)
    {
    }

    NGPDensity::NGPDensity(double *xvParticles, double *densityField, int nParticles, int nGrid, double cubeLength) :
        _xvParticles(xvParticles),
        _densityField(densityField),
        _nParticles(nParticles),
        _nGrid(nGrid),
        _realSize(nGrid*nGrid*nGrid),
        _factor(nGrid/cubeLength),
        _particleMass(1.0/nParticles)
    {
    }

    void NGPDensity::operator()()
    {
        // Initialize densityField to zero
        for ( int i = 0 ; i < _realSize ; i++ )
        {
            _densityField[i] = 0.0 ;
        }

        // Fill density field
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            int i = floor( _xvParticles[6*np  ] * _factor ) ;
            int j = floor( _xvParticles[6*np+1] * _factor ) ;
            int k = floor( _xvParticles[6*np+2] * _factor ) ;

            _densityField[utils::indexRealField(i, j, k, _nGrid)] += _particleMass ;
        }
    }

}

#endif

