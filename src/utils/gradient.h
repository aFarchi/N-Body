
/*__________________________________________________
 * gradient.h
 *__________________________________________________
 *
 * functions to compute the gradient of a field
 *
 */

#ifndef GRADIENT_H
#define GRADIENT_H

namespace utils
{
    void gradientX(double *field, double *gradient, int iMax, int jMax, int kMax, double factor=1.0) ;
    void gradientY(double *field, double *gradient, int iMax, int jMax, int kMax, double factor=1.0) ;
    void gradientZ(double *field, double *gradient, int iMax, int jMax, int kMax, double factor=1.0) ;
}

#endif

