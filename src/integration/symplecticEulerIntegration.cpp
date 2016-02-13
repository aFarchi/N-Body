
/*__________________________________________________
 * symplecticEulerIntegration.cpp 
 *__________________________________________________
 *
 * Implementation of euler semi implicit integration scheme
 *
 */

#ifndef SYMPLECTICEULERINTEGRATION_CPP
#define SYMPLECTICEULERINTEGRATION_CPP

#include "symplecticEulerIntegration.h"

namespace integration
{

    void SymplecticEulerIntregration::operator()(double *xt, double *vt, double Ft, double dt)
    {
        *vt += dt * Ft ;
        *xt += dt * ( *vt ) ;
    }

}

#endif

