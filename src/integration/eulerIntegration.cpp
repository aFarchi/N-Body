
/*__________________________________________________
 * eulerIntegration.cpp 
 *__________________________________________________
 *
 * Implementation of euler's integration scheme
 *
 */

#ifndef EULERINTEGRATION_CPP
#define EULERINTEGRATION_CPP

#include "eulerIntegration.h"

namespace integration
{

    void EulerIntregration::operator()(double *xt, double *vt, double Ft, double dt)
    {
        *xt += dt * ( *vt ) ;
        *vt += dt * Ft ;
    }

}

#endif

