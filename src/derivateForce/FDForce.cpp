
/*__________________________________________________
 * FDForce.cpp
 *__________________________________________________
 *
 * class that computes the force field from the potential field 
 * and that moves the particles using a ParticleMover
 *
 */

#ifndef FDFORCE_CPP
#define FDFORCE_CPP

#include "FDForce.h"
// gradients
#include "../utils/gradient.h"

namespace force
{

    template <typename ParticleMover>
        FDForce<ParticleMover>::FDForce() :
            _backwardFT(),
            _nGrid(0)
        {
        }

    template <typename ParticleMover>
        FDForce<ParticleMover>::FDForce(double *potentialField, fftw_complex *potentialFourierField, int nGrid, double *xvParticles,
                int nParticles, double cubeLength, double deltaT, unsigned flags) :
            _potentialField(potentialField),
            _potentialFourierField(potentialFourierField), 
            _nGrid(nGrid)
        {
             _backwardFT = fftw_plan_dft_c2r_3d(_nGrid, _nGrid, _nGrid, _potentialFourierField, _potentialField, flags) ;
             _forceField = new double[_nGrid*_nGrid*_nGrid] ;
             _move       = new ParticleMover(xvParticles, _forceField, nParticles, _nGrid, cubeLength, deltaT) ;
        }

    template <typename ParticleMover>
        FDForce<ParticleMover>::~FDForce()
        {
            fftw_destroy_plan(_backwardFT) ;
            delete _forceField ;
            delete _move ;
        }

    template <typename ParticleMover>
        void FDForce<ParticleMover>::operator()()
        {
            fftw_execute(_backwardFT) ;

            utils::gradientX(_potentialField, _forceField, _nGrid, _nGrid, _nGrid, -1.0) ;
            (*_move)(0) ;

            utils::gradientY(_potentialField, _forceField, _nGrid, _nGrid, _nGrid, -1.0) ;
            (*_move)(1) ;

            utils::gradientZ(_potentialField, _forceField, _nGrid, _nGrid, _nGrid, -1.0) ;
            (*_move)(2) ;
        }

}

#endif

