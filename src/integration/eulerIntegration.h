
/*__________________________________________________
 * eulerIntegration.h 
 *__________________________________________________
 *
 * Classes to implement an euler's integration scheme to solve the following problem :
 * x'(t) = v(t)
 * v'(t) = F(t)
 *
 * Given (x(t), v(t), F(t), dt), it must return 
 * (x(t+dt), v(t+dt))
 *
 * In this method, we approximate f'(t) by ( f(t+dt) - f(t) ) / dt
 *
 */

#ifndef EULERINTEGRATION_H
#define EULERINTEGRATION_H

namespace integration
{

    class EulerIntregration
    {
        public:
            void operator()(double *xt, double *vt, double Ft, double dt) ;
    };

}

#endif

