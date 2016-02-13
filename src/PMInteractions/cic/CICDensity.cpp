
/*__________________________________________________
 * CICDensity.cpp
 *__________________________________________________
 *
 * implementation of class CICDensity
 *
 */

#ifndef CICDENSITY_CPP
#define CICDENSITY_CPP

#include "CICDensity.h"
// floor
#include <math.h>
// indexMRealField
#include "../../utils/indexing.h"

namespace PM
{

    CICDensity::CICDensity() :
        _nParticles(0),
        _nGrid(0),
        _realSize(0),
        _factor(0.0),
        _particleMass(1.0)
    {   
    }  

    CICDensity::CICDensity(double *xvParticles, double *densityField, int nParticles, int nGrid, double cubeLength) :
        _xvParticles(xvParticles),
        _densityField(densityField),
        _nParticles(nParticles),
        _nGrid(nGrid),
        _realSize(nGrid*nGrid*nGrid),
        _factor(nGrid/cubeLength),
        _particleMass(1.0/nParticles)
    {   
    }  

    void CICDensity::operator()()
    {
        // Initialize densityField to zero
        for ( int i = 0 ; i < _realSize ; i++ )
        {
            _densityField[i] = 0.0 ;
        }

        // Fill density field
        for ( int np = 0 ; np < _nParticles ; np++ )
        {
            int i1    = floor( _xvParticles[6*np  ] * _factor ) ;
            int j1    = floor( _xvParticles[6*np+1] * _factor ) ;
            int k1    = floor( _xvParticles[6*np+2] * _factor ) ;

            int i2    = i1 + 1 ;
            int j2    = j1 + 1 ; 
            int k2    = k1 + 1 ;

            double dx = ( _xvParticles[6*np  ] * _factor ) - i1 ;
            double dy = ( _xvParticles[6*np+1] * _factor ) - j1 ;
            double dz = ( _xvParticles[6*np+2] * _factor ) - k1 ;
           
            _densityField[utils::indexMRealField(i1, j1, k1, _nGrid)] += _particleMass * ( 1 - dx ) * ( 1 - dy ) * ( 1 - dz ) ;
            _densityField[utils::indexMRealField(i1, j1, k2, _nGrid)] += _particleMass * ( 1 - dx ) * ( 1 - dy ) *       dz   ;
            _densityField[utils::indexMRealField(i1, j2, k1, _nGrid)] += _particleMass * ( 1 - dx ) *       dy   * ( 1 - dz ) ;
            _densityField[utils::indexMRealField(i1, j2, k2, _nGrid)] += _particleMass * ( 1 - dx ) *       dy   *       dz   ;

            _densityField[utils::indexMRealField(i2, j1, k1, _nGrid)] += _particleMass *       dx   * ( 1 - dy ) * ( 1 - dz ) ;
            _densityField[utils::indexMRealField(i2, j1, k2, _nGrid)] += _particleMass *       dx   * ( 1 - dy ) *       dz   ;
            _densityField[utils::indexMRealField(i2, j2, k1, _nGrid)] += _particleMass *       dx   *       dy   * ( 1 - dz ) ;
            _densityField[utils::indexMRealField(i2, j2, k2, _nGrid)] += _particleMass *       dx   *       dy   *       dz   ;
        }
    }

}

#endif

