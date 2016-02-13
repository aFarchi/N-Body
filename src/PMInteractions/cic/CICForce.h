
/*_________________________________________
 * CICForce.h
 *________________________________________
 *
 * class that computes the force applied to a particle from a force field 
 * using the cloud in cell (CIC) method
 * and actually moves the particles
 *
 */

#ifndef CICFORCE_H
#define CICFORCE_H

namespace PM
{

    template <typename IntegrationScheme>
        class CICForce
        {
            public:
                CICForce() ;
                CICForce(double *xvParticles, double *forceField, int nParticles, int nGrid, double cubeLength, double deltaT) ;
                ~CICForce() ;
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

