
/*__________________________________________________
 * symplecticEulerIntegration.h 
 *__________________________________________________
 *
 * Classes to implement an euler semi implicit integration scheme to solve the following problem :
 * x'(t) = v(t)
 * v'(t) = F(t)
 *
 * Given (x(t), v(t), F(t), dt), it must return 
 * (x(t+dt), v(t+dt))
 *
 */

#ifndef SYMPLECTICEULERINTEGRATION_H
#define SYMPLECTICEULERINTEGRATION_H

namespace integration
{

    class SymplecticEulerIntregration
    {
        public:
            void operator()(double *xt, double *vt, double Ft, double dt) ;
    };

}

#endif

