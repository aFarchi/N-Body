
/*__________________________________________________
 * poissonSolver.h
 *__________________________________________________
 *
 * Class to solve Poisson's equation
 * Delta(Phi) = 4 pi G rho
 * with periodic boundary conditions
 * using Fourier transformations
 *
 * It takes rho and return Fourier(phi)
 */

#ifndef POISSONSOLVER_H 
#define POISSONSOLVER_H 

#include <fftw3.h>

namespace poisson
{

    class PoissonSolver
    {
        public :
            PoissonSolver() ;
            PoissonSolver(double *densityField, fftw_complex *densityFourierField, int nGrid, double pi = 3.141592, double G = 6.674e-11, unsigned flags = FFTW_MEASURE) ;
            ~PoissonSolver() ;

            void operator()() ;

        private :
            void initializeForceKernel(int nGrid, double pi, double units) ;

            double       *_densityField ;
            fftw_complex *_densityFourierField ;
            fftw_plan     _forwardFT ;
            double       *_forceKernel ;

            const int     _complexSize ;
    };

}

#endif

