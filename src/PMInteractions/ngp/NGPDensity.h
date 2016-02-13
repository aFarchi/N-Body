
/*_________________________________________
 * NGPDensity.h
 *________________________________________
 *
 * class that computes a density field
 * using the nearest grid point (NGP) method
 *
 */

#ifndef NGPDENSITY_H
#define NGPDENSITY_H

namespace PM
{

    class NGPDensity
    {
        public:
            NGPDensity() ;
            NGPDensity(double *xvParticles, double *densityField, int nParticles, int nGrid, double cubeLength) ;
            void operator()() ;

        private:
            double       *_xvParticles ;
            double      *_densityField ;
            const int    _nParticles ;
            const int    _nGrid ;
            const int    _realSize ;
            const double _factor ;
            const double _particleMass ;
    };

}

#endif

