
/*__________________________________________________
 * ngp.cpp
 *__________________________________________________
 *
 * implementation of class NGPDensity
 *
 */

#ifndef NGPDENSITY_CPP
#define NGPDENSITY_CPP

#include "ngp.h"
#include <math.h>

namespace cube
{

    NGPDensity::NGPDensity(int nGrid, double cubeLength) :
        _nGrid(nGrid),
        _cubeLength(cubeLength)
    {
    }

    void NGPDensity::computeDensityField(double *xvParticles, double *densityField, int nParticles)
    {
        // Initialize densityField to zero
        for ( int i = 0 ; i < _nGrid * _nGrid * _nGrid ; i++ )
        {
            densityField[i] = 0.0 ;
        }

        // Scaling factors
        double factor       = _nGrid / _cubeLength ;
        double particleMass = 1.0    / nParticles ; 

        // Fill density field
        for ( int np = 0 ; np < nParticles ; np++ )
        {
            int i = floor( xvParticles[6*np]   * factor ) ;
            int j = floor( xvParticles[6*np+1] * factor ) ;
            int k = floor( xvParticles[6*np+2] * factor ) ;

            densityField[i*_nGrid*_nGrid+j*_nGrid+k] += particleMass ;
        }

        return ;
    }

}

#endif

