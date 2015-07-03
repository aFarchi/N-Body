
/*__________________________________________________
 * cube.h
 *__________________________________________________
 *
 * definition of class Cube
 *
 */

#ifndef CUBE
#define CUBE

#include <string>
#include "../log/logFile.h"

namespace cube
{
    class Cube
    {
        public:
            Cube(int nGrid, int nParticles, double cubeLength, const std::string &log="screen") ;
            ~Cube() ;

            void printParameters() ;
            void printParticleList() ;

            int writeParticleList(const char *fileName) ;
            int writeParticleList(const std::string &fileName) ;

        private:
            void initializeRandomParticles() ;

            output::LogFile _log ;
            const int _nGrid ;
            const int _nParticles ;
            double *_xvParticles ;

            const double _cubeLength ;
    } ;

}

#endif
