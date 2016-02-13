
/*_________________________________________
 * initializeRandom.h
 *________________________________________
 *
 * class that initializes the XVP array:
 *     positions are random
 *     velocities are null
 *
 */

#ifndef INITIALIZERANDOM_H
#define INITIALIZERANDOM_H

namespace initialize
{

    class InitializeRandom
    {
        public:
            InitializeRandom() ;
            InitializeRandom(double *xvParticles, int nParticles, double cubeLength) ;
            void operator()() ;

        private:
            double      *_xvParticles ;
            const int    _nParticles ;
            const double _cubeLength ;
    };

}

#endif

