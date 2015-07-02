
/*__________________________________________________
 * cube.h
 *__________________________________________________
 *
 * definition of class Cube
 *
 */

#ifndef CUBE
#define CUBE

namespace cube
{
    class Cube
    {
        public:
            Cube(int nGrid, int nParticles, double cubeLength) ;
            ~Cube() ;

            void printParameters();
            void printParticleList();

        private:
            void initializeRandomParticles();

            const int _nGrid ;
            const int _nParticles ;
            double *_xvParticles ;

            const double _cubeLength ;
    } ;

}

#endif
