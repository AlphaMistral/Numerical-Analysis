//
//  IntegralUtilities.hpp
//  CPPTest
//
//  Created by 于京平 on 16/6/24.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef IntegralUtilities_hpp
#define IntegralUtilities_hpp

#include <stdio.h>
class IntegralUtilities
{
public :
    IntegralUtilities ();
    double gauss_legendre(int n, double (*f)(double,void*), void* data, double a, double b);
    double gauss_legendre_2D_cube(int n, double (*f)(double,double,void*), void* data, double a, double b, double c, double d);
    void gauss_legendre_tbl(int n, double* x, double* w, double eps);
};
#endif /* IntegralUtilities_hpp */
