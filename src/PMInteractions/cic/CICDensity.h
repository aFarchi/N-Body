
/*_________________________________________
 * CICDensity.h
 *________________________________________
 *
 * class that computes a density field
 * using the cloud in cell (CIC) method
 *
 */

#ifndef CICDENSITY_H
#define CICDENSITY_H

namespace PM
{

    class CICDensity
    {
        public:
            CICDensity() ;
            CICDensity(double *xvParticles, double *densityField, int nParticles, int nGrid, double cubeLength) ;
            void operator()() ;

        private:
            double      *_xvParticles ;
            double      *_densityField ;
            const int    _nParticles ;
            const int    _nGrid ;
            const int    _realSize ;
            const double _factor ;
            const double _particleMass ;
    };

}

#endif

