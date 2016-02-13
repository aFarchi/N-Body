
/*_________________________________________
 * NGPForce.h
 *________________________________________
 *
 * class that computes the force applied to a particle from a force field 
 * using the nearest grid point (NGP) method 
 * and that actually moves the particles
 *
 */

#ifndef NGPFORCE_H
#define NGPFORCE_H

namespace PM
{

    template <typename IntegrationScheme>
        class NGPForce
        {
            public:
                NGPForce() ;
                NGPForce(double *xvParticles, double *forceField, int nParticles, int nGrid, double cubeLength, double deltaT) ;
                ~NGPForce() ;
                void operator()(int direction) ;

            private:
                IntegrationScheme *_integrate ;
                
                double            *_xvParticles ;
                double            *_forceField ;
                const int          _nParticles ;
                const int          _nGrid ;
                const double       _deltaT ;
                const double       _factor ;
        };

}

#endif

