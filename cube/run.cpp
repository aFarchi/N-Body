
/*__________________________________________________
 * run.cpp
 *__________________________________________________
 *
 * implementation of the run function 
 *
 */

#ifndef RUN_CPP
#define RUN_CPP

#include "run.h"

#include "cube.cpp"
#include "../patch/toString.cpp"

#ifdef DDEN_NGP
#include "density/ngp.h"
#else
#include "density/cic.h"
#endif

namespace cube
{
    int runSimulation(int nGrid, int nParticles, double cubeLength, double factor, int ntSteps,
            std::string outputDir, std::string logFile, std::string prefixPL, std::string suffixPL)
    {
#ifdef DDEN_NGP
        Cube<NGPDensity> c(nGrid, nParticles, cubeLength, logFile) ;
#else
        Cube<CICDensity> c(nGrid, nParticles, cubeLength, logFile) ;
#endif

        c.printParameters() ;
        for ( int t = 0 ; t < ntSteps ; t++ )
        {
            c.writeParticleList(prefixPL+patch::to_string(t)+suffixPL) ;
            c.computeDensityField() ;
            c.writeDensityField(prefixPL+"_den"+patch::to_string(t)+suffixPL) ;
            c.timeStep(factor) ;
        }

        c.writeParticleList(prefixPL+patch::to_string(ntSteps)+suffixPL) ;
        
        return EXIT_SUCCESS ;

    }
}

#endif

