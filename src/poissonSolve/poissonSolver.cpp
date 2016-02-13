
/*__________________________________________________
 * poissonSolver.cpp
 *__________________________________________________
 *
 * Implementation of class PoissonSolver
 *
 */

#ifndef POISSONSOLVER_CPP 
#define POISSONSOLVER_CPP

#include "poissonSolver.h"
// indexComplexField
#include "../utils/indexing.h"
// cos
# include <math.h>

namespace poisson
{

    PoissonSolver::PoissonSolver() :
        _forwardFT(),
        _complexSize(0)
    {
    }

    PoissonSolver::PoissonSolver(double *densityField, fftw_complex *densityFourierField, int nGrid, double pi, double G, unsigned flags) :
        _densityField(densityField),
        _densityFourierField(densityFourierField),
        _complexSize(nGrid*nGrid*(nGrid/2+1))
    {
        _forwardFT   = fftw_plan_dft_r2c_3d(nGrid, nGrid, nGrid, _densityField, _densityFourierField, flags) ;
        _forceKernel = new double[_complexSize] ;
        initializeForceKernel(nGrid, pi, 4.0*pi*G) ;
    }

    PoissonSolver::~PoissonSolver()
    {
        fftw_destroy_plan(_forwardFT) ;
        delete _forceKernel ;
    }

    void PoissonSolver::initializeForceKernel(int nGrid, double pi, double units)
    {
        for ( int i = 0 ; i < nGrid ; i++ )
        {   
            for ( int j = 0 ; j < nGrid ; j++ )
            {   
                for ( int k = 0 ; k < ( nGrid/2 + 1 ) ; k++ )
                {   
                    double kI = 2.0 * ( cos( 2.0 * i * pi / nGrid ) - 1.0 ) ; 
                    double kJ = 2.0 * ( cos( 2.0 * j * pi / nGrid ) - 1.0 ) ; 
                    double kK = 2.0 * ( cos( 2.0 * k * pi / nGrid ) - 1.0 ) ; 

                    _forceKernel[utils::indexComplexField(i, j, k, nGrid)] = kI + kJ + kK ;
                }   
            }   
        }   
        _forceKernel[0] = 1.0 ;

        for ( int i = 0 ; i < _complexSize ; i++ )
        {   
            _forceKernel[i] = units / _forceKernel[i] ;
        } 
    }

    void PoissonSolver::operator()()
    {
        fftw_execute(_forwardFT) ;

        for ( int i = 0 ; i < _complexSize ; i++ )
        {
            _densityFourierField[i][0] *= _forceKernel[i] ;
            _densityFourierField[i][1] *= _forceKernel[i] ;
        }
    }

}

#endif

