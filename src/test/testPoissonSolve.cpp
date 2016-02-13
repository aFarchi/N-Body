
/*__________________________________________________
 * testPoissonSolve.cpp
 *__________________________________________________
 */

// cout
#include <iostream>
// string
#include <string>

#ifdef NGPDENSITY
// NGPDensity
#include "../PMInteractions/ngp/NGPDensity.h"
#else
// CICDensity
#include "../PMInteractions/cic/CICDensity.h"
#endif

// InitializeRandom
#include "../initialize/initializeRandom.h"
// write
#include "../io/write.h"
// printParticleList
#include "../io/printL.h"
// poisson solver
#include "../poissonSolve/poissonSolver.h"

// Fourier...
#include <fftw3.h>


int main()
{
    std::cout << "Running testDensity.cpp" << std::endl ;

    std::string fileNameReal("/Users/aFarchi/Desktop/test/denTest.bin") ;
    std::string fileNameComplex("/Users/aFarchi/Desktop/test/potTest.bin") ;

    const double  cubeLength     = 100.0 ;
    const int     nParticles     = 10 ;
    const int     nGrid          = 32 ;
    const int     realSize       = nGrid * nGrid * nGrid ;
    const int     complexSize    = nGrid * nGrid * ( nGrid / 2 + 1 ) ;

    double       *xvParticles    = new double[6*nParticles] ;
    double       *densityField   = (double*) fftw_malloc(sizeof(double)*realSize) ;
    fftw_complex *potentialField = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*complexSize) ;

    initialize::InitializeRandom initialize(xvParticles, nParticles, cubeLength) ;
#ifdef NGPDENSITY
    PM::NGPDensity computeDensity(xvParticles, densityField, nParticles, nGrid, cubeLength) ;
#else
    PM::CICDensity computeDensity(xvParticles, densityField, nParticles, nGrid, cubeLength) ;
#endif
    poisson::PoissonSolver solvePoisson(densityField, potentialField, nGrid) ;
    fftw_plan backwardFT = fftw_plan_dft_c2r_3d(nGrid, nGrid, nGrid, potentialField, densityField, FFTW_MEASURE) ;

    initialize() ;
    computeDensity() ;
    solvePoisson() ;

    io::writeDensityField(fileNameReal, densityField, nGrid) ;

    fftw_execute(backwardFT) ;
    io::writeDensityField(fileNameComplex, densityField, nGrid) ;

    fftw_free(densityField) ;
    fftw_free(potentialField) ;
    fftw_destroy_plan(backwardFT) ;
    delete xvParticles ;
    return 0 ;
}


