
/*__________________________________________________
 * stepFunction.h
 *__________________________________________________
 *
 * step function for the algorithm
 *
 */

#ifndef STEPFUNCTION_H
#define STEPFUNCTION_H

// Fourier...
#include <fftw3.h>

namespace cube
{

    template <typename DensityBuilder, typename PoissonSolver, typename Force, typename ParticleSender>
        class StepFunction
        {
            public:
                StepFunction() ;
                StepFunction(double *xvParticles, int nParticles, double *densityField, fftw_complex *potentialField, int nGrid, double cubeLength,
                             double deltaT, double pi = 3.141592, double G = 6.674e-11, unsigned flags = FFTW_MEASURE) ;
                ~StepFunction() ;
                void operator()() ;

            private:
                DensityBuilder *_computeDensity ;
                PoissonSolver  *_solvePoisson ;
                Force          *_derivateForce ;
                ParticleSender *_sendParticles ;
        };

}

#endif

