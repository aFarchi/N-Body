
/*__________________________________________________
 * testDensity.cpp
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
// writeDensityField
#include "../io/write.h"
// printParticleList
#include "../io/printL.h"


int main()
{
    std::cout << "Running testDensity.cpp" << std::endl ;

    std::string fileName("/Users/aFarchi/Desktop/test/denTest.bin") ;

    const double cubeLength  = 100.0 ;
    const int    nParticles  = 100 ;
    const int    nGrid       = 64 ;
    double      *xvParticles = new double[6*nParticles] ;
    double      *denField    = new double[nGrid*nGrid*nGrid] ;    

    initialize::InitializeRandom initialize(xvParticles, nParticles, cubeLength) ;
#ifdef NGPDENSITY
    PM::NGPDensity computeDensity(xvParticles, denField, nParticles, nGrid, cubeLength) ;
#else
    PM::CICDensity computeDensity(xvParticles, denField, nParticles, nGrid, cubeLength) ;
#endif
    
    initialize() ;
    io::printParticleList(xvParticles, nParticles) ;
    computeDensity() ;
    io::writeDensityField(fileName, denField, nGrid) ;

    delete xvParticles ;
    delete denField ;
    return 0 ;
}


