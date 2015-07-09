
/*_________________________________________
 * ngp.h
 *________________________________________
 *
 * class that computes a density field
 * using the nearest grid point (NGP) method
 *
 */

#ifndef NGPDENSITY_H
#define NGPDENSITY_H

namespace cube
{
    class NGPDensity
    {
        public :
            NGPDensity(int nGrid, double cubeLength) ;
            void computeDensityField(double *xvParticles, double *densityField, int nParticles) ;

        private :
            const int    _nGrid ;
            const double _cubeLength ;
    };
}

#endif

