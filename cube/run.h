
/*__________________________________________________
 * run.h
 *__________________________________________________
 *
 * definition of the run function 
 *
 */

#ifndef RUN_H
#define RUN_H

#include <string>

namespace cube
{
    int runSimulation(int nGrid, int nParticles, double cubeLength, double factor, int ntSteps, 
            std::string outputDir, std::string logFile, std::string prefixPL, std::string suffixPL);
}

#endif
