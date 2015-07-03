
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

namespace cube
{
    class Cube
    {
        public:
            Cube(int nGrid, int nParticles, double cubeLength) ;
            ~Cube() ;

            void printParameters() ;
            void printParticleList() ;

            int writeParticleList(const char *fileName) ;
            int writeParticleList(const std::string &fileName) ;

        private:
            void initializeRandomParticles() ;

            const int _nGrid ;
            const int _nParticles ;
            double *_xvParticles ;

            const double _cubeLength ;
    } ;

}

#endif
