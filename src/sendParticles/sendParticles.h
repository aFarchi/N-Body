
/*_________________________________________
 * sendParticles.h
 *________________________________________
 *
 * class to send particles round the simulation's box
 */

#ifndef SENDPARTICLES_H
#define SENDPARTICLES_H

namespace send
{

    class ParticleSender
    {
        public:
            ParticleSender() ;
            ParticleSender(double *xvParticles, int nParticles, double cubeLength) ;
            void operator()() ;

        private:
            double      *_xvParticles ;
            const int    _nParticles ;
            const double _cubeLength ;
    };

}

#endif

