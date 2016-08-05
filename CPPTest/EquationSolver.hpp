//
//  EquationSolver.hpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>

#include"ExpressionParser.hpp"

using namespace std;

class EquationSolver
{
    constexpr static const double EPS = 1e-6;
    static void SetPrecision (double eps);
private:
    ExpressionParser *expressionParser;
public:
    EquationSolver ();
    double SolveByBinary (const char *equation, double lowerBound, double upperBound);
    double SolveByNewton (const char *equation, const char* derivativeEquation, double prediction);
    double SolveBySecant (const char *equation, double prediction1, double prediction2);
    double SolveByNewton1 (const char *equation, const char *derivativeEquation, double prediction, double lamda);
};

#endif /* EquationSolver_hpp */
