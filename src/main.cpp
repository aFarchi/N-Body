/*__________________________________________________
 * main.cpp
 *__________________________________________________
 *
 */

// InitializeRandom
#include "initialize/initializeRandom.h"

#ifdef NGPDENSITY
// NGPDensity
#include "PMInteractions/ngp/NGPDensity.h"
#else
// CICDensity
#include "PMInteractions/cic/CICDensity.h"
#endif

// PoissonSolver
#include "poissonSolve/poissonSolver.h"

#ifdef EULERINTEGRATION
// EulerIntregration
#include "integration/eulerIntegration.h"
#else
// SymplecticEulerIntregration
#include "integration/symplecticEulerIntegration.h"
#endif

#ifdef NGPFORCE
// NGPForce
#include "PMInteractions/ngp/NGPForce.cpp"
#else
// CICForce
#include "PMInteractions/cic/CICForce.cpp"
#endif

// FDForce
#include "derivateForce/FDForce.cpp"

// ParticleSender
#include "sendParticles/sendParticles.h"

// StepFunction
#include "stepFunction/stepFunction.cpp"

// Cube
#include "cube/cube.cpp"

// LogFile
#include "io/logFile.h"

// Run
#include "cube/run.cpp"

// string
#include <string>
// EXIT_SUCCESS
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // typdef
    typedef initialize::InitializeRandom Initializator ;
#ifdef NGPDENSITY
    typedef PM::NGPDensity DensityBuilder ;
#else
    typedef PM::CICDensity DensityBuilder ;
#endif
    typedef poisson::PoissonSolver PoissonSolver ;
#ifdef EULERINTEGRATION
    typedef integration::EulerIntregration IntegrationScheme ;
#else
    typedef integration::SymplecticEulerIntregration IntegrationScheme ;
#endif
#ifdef NGPFORCE
    typedef PM::NGPForce<IntegrationScheme> ParticleMover ;
#else
    typedef PM::CICForce<IntegrationScheme> ParticleMover ;
#endif
    typedef force::FDForce<ParticleMover> Force ;
    typedef send::ParticleSender ParticleSender ;
    typedef cube::StepFunction<DensityBuilder, PoissonSolver, Force, ParticleSender> Step ;
    typedef cube::Cube<Initializator, Step> Cube ;
    typedef io::LogFile Log ;
    typedef run::Run<Cube, Log> Run ;

    // parameters
    const int         nParticles = 2 ;
    const int         nGrid      = 32 ;
    const double      cubeLength = 100.0 ;
    const double      deltaT     = 1.0e3 ;

    const double      pi         = 3.14159265 ;
    const double      G          = 6.674e-11 ;
    unsigned          flags      = FFTW_MEASURE ;

    const int         nTStep     = 100 ;
    const int         nModPrint  = 10 ;
    const int         nModWrite  = 1 ;

    const std::string outputDir  = std::string("/Users/aFarchi/Desktop/test/output/") ;
    const std::string logFile    = outputDir + std::string("log.txt") ;
    const std::string prefixPL   = outputDir + std::string("xvp") ;
    const std::string suffixPL   = ".bin" ;
    
    // start
    Cube *cube = new Cube(nParticles, nGrid, cubeLength, deltaT, pi, G, flags);
    Run  *run  = new Run(cube, nTStep, nModPrint, nModWrite, logFile, prefixPL, suffixPL) ;
    run->initialize() ;
    (*run)() ;

    delete cube ;
    delete run ;

    return EXIT_SUCCESS ;
}

