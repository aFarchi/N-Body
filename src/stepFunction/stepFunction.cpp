
/*__________________________________________________
 * stepFunction.cpp
 *__________________________________________________
 *
 */

#ifndef STEPFUNCTION_CPP
#define STEPFUNCTION_CPP

#include "stepFunction.h"

namespace cube
{

    template <typename DensityBuilder, typename PoissonSolver, typename Force, typename ParticleSender>
        StepFunction<DensityBuilder, PoissonSolver, Force, ParticleSender>::StepFunction()
        {
        }

    template <typename DensityBuilder, typename PoissonSolver, typename Force, typename ParticleSender>
        StepFunction<DensityBuilder, PoissonSolver, Force, ParticleSender>::StepFunction(double *xvParticles, int nParticles, double *densityField, 
                fftw_complex *potentialField, int nGrid, double cubeLength, double deltaT, double pi, double G, unsigned flags)
        {
            _computeDensity = new DensityBuilder(xvParticles, densityField, nParticles, nGrid, cubeLength) ;
            _solvePoisson   = new PoissonSolver(densityField, potentialField, nGrid, pi, G, flags) ;
            _derivateForce  = new Force(densityField, potentialField, nGrid, xvParticles, nParticles, cubeLength, deltaT, flags) ;
            _sendParticles  = new ParticleSender(xvParticles, nParticles, cubeLength) ;
        }

    template <typename DensityBuilder, typename PoissonSolver, typename Force, typename ParticleSender>
        StepFunction<DensityBuilder, PoissonSolver, Force, ParticleSender>::~StepFunction()
        {
            delete _computeDensity ;
            delete _solvePoisson ;
            delete _derivateForce ;
            delete _sendParticles ;
        }

    template <typename DensityBuilder, typename PoissonSolver, typename Force, typename ParticleSender>
        void StepFunction<DensityBuilder, PoissonSolver, Force, ParticleSender>::operator()()
        {
            (*_computeDensity)() ;
            (*_solvePoisson)() ;
            (*_derivateForce)() ;
            (*_sendParticles)() ;
        }

}

#endif

