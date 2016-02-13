
/*__________________________________________________
 * testForce.cpp
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
// gradient
#include "../utils/gradient.h"

// Fourier...
#include <fftw3.h>


int main()
{
    std::cout << "Running testForce.cpp" << std::endl ;

    std::string fileNameReal("/Users/aFarchi/Desktop/test/denTest.bin") ;
    std::string fileNameComplex("/Users/aFarchi/Desktop/test/potTest.bin") ;
    std::string fileNameForceX("/Users/aFarchi/Desktop/test/fxTest.bin") ;
    std::string fileNameForceY("/Users/aFarchi/Desktop/test/fyTest.bin") ;
    std::string fileNameForceZ("/Users/aFarchi/Desktop/test/fzTest.bin") ;

    const double  cubeLength     = 100.0 ;
    const int     nParticles     = 10 ;
    double       *xvParticles    = new double[6*nParticles] ;
    const int     nGrid          = 32 ;
    const int     realSize       = nGrid * nGrid * nGrid ;
    const int     complexSize    = nGrid * nGrid * ( nGrid / 2 + 1 ) ;
    double       *densityField   = (double*) fftw_malloc(sizeof(double)*realSize) ;
    double       *forceField     = (double*) fftw_malloc(sizeof(double)*realSize) ;
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

    utils::gradientX(densityField, forceField, nGrid, nGrid, nGrid, -1.0) ;
    io::writeDensityField(fileNameForceX, forceField, nGrid) ;

    utils::gradientY(densityField, forceField, nGrid, nGrid, nGrid, -1.0) ;
    io::writeDensityField(fileNameForceY, forceField, nGrid) ;

    utils::gradientZ(densityField, forceField, nGrid, nGrid, nGrid, -1.0) ;
    io::writeDensityField(fileNameForceZ, forceField, nGrid) ;

    fftw_free(densityField) ;
    fftw_free(forceField) ;
    fftw_free(potentialField) ;
    fftw_destroy_plan(backwardFT) ;
    delete xvParticles ;
    return 0 ;
}


