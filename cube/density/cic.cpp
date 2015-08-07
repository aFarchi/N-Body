
/*__________________________________________________
 * cic.cpp
 *__________________________________________________
 *
 * implementation of class CICDensity
 *
 */

#ifndef CICDENSITY_CPP
#define CICDENSITY_CPP

#include "cic.h"
#include <math.h>

namespace cube
{

    CICDensity::CICDensity(int nGrid, double cubeLength) :
        _nGrid(nGrid),
        _cubeLength(cubeLength)
    {
    }

    void CICDensity::computeDensityField(double *xvParticles, double *densityField, int nParticles)
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
            int i1 = floor( xvParticles[6*np]   * factor ) ;
            int j1 = floor( xvParticles[6*np+1] * factor ) ;
            int k1 = floor( xvParticles[6*np+2] * factor ) ;

            int i2 = i1 + 1 ;
            int j2 = j1 + 1 ; 
            int k2 = k1 + 1 ;

            if ( i2 >= _nGrid )
            {
                i2 = 0 ;
            }

            if ( j2 >= _nGrid )
            {
                j2 = 0 ;
            }

            if ( k2 >= _nGrid )
            {
                k2 = 0 ;
            }
            
            double dx = ( xvParticles[6*np]   * factor ) - i1 ;
            double dy = ( xvParticles[6*np+1] * factor ) - j1 ;
            double dz = ( xvParticles[6*np+2] * factor ) - k1 ;
            
            densityField[i1*_nGrid*_nGrid+j1*_nGrid+k1] += particleMass * ( 1 - dx ) * ( 1 - dy ) * ( 1 - dz ) ;
            densityField[i1*_nGrid*_nGrid+j1*_nGrid+k2] += particleMass * ( 1 - dx ) * ( 1 - dy ) *     dz ;
            densityField[i1*_nGrid*_nGrid+j2*_nGrid+k1] += particleMass * ( 1 - dx ) *     dy     * ( 1 - dz ) ;
            densityField[i1*_nGrid*_nGrid+j2*_nGrid+k2] += particleMass * ( 1 - dx ) *     dy     *     dz ;
        
            densityField[i2*_nGrid*_nGrid+j1*_nGrid+k1] += particleMass *     dx     * ( 1 - dy ) * ( 1 - dz ) ;
            densityField[i2*_nGrid*_nGrid+j1*_nGrid+k2] += particleMass *     dx     * ( 1 - dy ) *     dz ;
            densityField[i2*_nGrid*_nGrid+j2*_nGrid+k1] += particleMass *     dx     *     dy     * ( 1 - dz ) ;
            densityField[i2*_nGrid*_nGrid+j2*_nGrid+k2] += particleMass *     dx     *     dy     *     dz ;
        }

        return ;
    }

}

#endif

