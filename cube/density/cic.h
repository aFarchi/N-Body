
/*_________________________________________
 * cic.h
 *________________________________________
 *
 * class that computes a density field
 * using the cloud in cell (CIC) method
 *
 */

#ifndef CICDENSITY_H
#define CICDENSITY_H

namespace cube
{
    class CICDensity
    {
        public :
            CICDensity(int nGrid, double cubeLength) ;
            void computeDensityField(double *xvParticles, double *densityField, int nParticles) ;

        private :
            const int    _nGrid ;
            const double _cubeLength ;
    };
}

#endif

