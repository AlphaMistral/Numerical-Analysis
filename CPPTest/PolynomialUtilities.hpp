//
//  PolynomialUtilities.hpp
//  CPPTest
//
//  Created by 于京平 on 16/6/17.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef PolynomialUtilities_hpp
#define PolynomialUtilities_hpp

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

class PolynomialSolver
{
private:
    const int ORDER = 4;
public:
    PolynomialSolver ();
    double GetPolynomialResult (vector<double> *, double);
    double LagrangeInterp (double *, double *, int, double);
    double NewtonInterp (double *, double *, int, double);
    double NewtonForwardInterp (double *, double *, int, double);
    double NewtonBackwardInterp (double *, double *, int, double);
    pair <double, double> LeastSquare (const vector<double> &, const vector<double> &);
    vector<double> * PolynomialFitting (const vector<double> &, const vector<double> &, int degree);
};

class Polynomial
{
private :
    vector<double> coefficients;
    int size;
public :
    Polynomial ();
    Polynomial (vector<double> *);
    static double GetResult (double, void *);
    double GetYValue (double);
};
#endif /* PolynomialUtilities_hpp */
