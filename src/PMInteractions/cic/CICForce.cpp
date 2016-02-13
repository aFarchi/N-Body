
/*__________________________________________________
 * CICForce.cpp
 *__________________________________________________
 *
 * implementation of class CICForce
 *
 */

#ifndef CICFORCE_CPP
#define CICFORCE_CPP

#include "CICForce.h"
// floor
#include <math.h>
// indexMRealField
#include "../../utils/indexing.h"

namespace PM
{

    template <typename IntegrationScheme>
        CICForce<IntegrationScheme>::CICForce() :
            _nParticles(0),
            _nGrid(0),
            _deltaT(0.0),
            _factor(1.0)
    {
    }

    template <typename IntegrationScheme>
        CICForce<IntegrationScheme>::CICForce(double *xvParticles, double *forceField, int nParticles, int nGrid, double cubeLength, double deltaT) :
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
        CICForce<IntegrationScheme>::~CICForce()
    {
        delete _integrate ;
    }

    template <typename IntegrationScheme>
        void CICForce<IntegrationScheme>::operator()(int direction)
        {
            // Move particles 
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

                double force(0.0) ;

                force += _forceField[utils::indexMRealField(i1, j1, k1, _nGrid)] * ( 1 - dx ) * ( 1 - dy ) * ( 1 - dz ) ;
                force += _forceField[utils::indexMRealField(i1, j1, k2, _nGrid)] * ( 1 - dx ) * ( 1 - dy ) *       dz   ;
                force += _forceField[utils::indexMRealField(i1, j2, k1, _nGrid)] * ( 1 - dx ) *       dy   * ( 1 - dz ) ;
                force += _forceField[utils::indexMRealField(i1, j2, k2, _nGrid)] * ( 1 - dx ) *       dy   *       dz   ;

                force += _forceField[utils::indexMRealField(i2, j1, k1, _nGrid)] *       dx   * ( 1 - dy ) * ( 1 - dz ) ;
                force += _forceField[utils::indexMRealField(i2, j1, k2, _nGrid)] *       dx   * ( 1 - dy ) *       dz   ;
                force += _forceField[utils::indexMRealField(i2, j2, k1, _nGrid)] *       dx   *       dy   * ( 1 - dz ) ;
                force += _forceField[utils::indexMRealField(i2, j2, k2, _nGrid)] *       dx   *       dy   *       dz   ;

                (*_integrate)(&_xvParticles[6*np+direction], &_xvParticles[6*np+3+direction], force, _deltaT) ;
            }
        }

}

#endif

