//
//  EquationSolver.cpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "EquationSolver.hpp"

EquationSolver :: EquationSolver ()
{
    expressionParser = new ExpressionParser ();
}

double EquationSolver :: SolveByBinary(const char *equation, double lowerBound, double upperBound)
{
    double middle = (lowerBound + upperBound) / 2.0;
    if (upperBound - lowerBound <= EPS)
        return middle;
    double f1 = expressionParser->ParseExpression(equation, lowerBound);
    double f2 = expressionParser->ParseExpression(equation, middle);
    //double f3 = expressionParser->ParseExpression(equation, upperBound);
    if (f2 == 0)
        return middle;
    else if (f1 * f2 < 0)
        return SolveByBinary(equation, lowerBound, middle);
    else return SolveByBinary(equation, middle, upperBound);
}

double EquationSolver :: SolveByNewton(const char *equation, const char *derivativeEquation, double prediction)
{
    double last = prediction;
    while (true)
    {
        double current = last - expressionParser->ParseExpression(equation, last) / expressionParser->ParseExpression(derivativeEquation, last);
        if (abs (current - last) <= EPS)
        {
            return current;
        }
        last = current;
    }
}

double EquationSolver :: SolveByNewton1(const char *equation, const char *derivativeEquation, double prediction, double lamda)
{
    if (lamda < 0)
        lamda = 0;
    else if (lamda > 1)
        lamda = 1;
    double last = prediction;
    while (true)
    {
        double current = last - expressionParser->ParseExpression(equation, last) / expressionParser->ParseExpression(derivativeEquation, last) * lamda;
        if (abs (current - last) <= EPS)
            return current;
        last = current;
    }
}

double EquationSolver :: SolveBySecant(const char *equation, double prediction1, double prediction2)
{
    double last1 = prediction1;
    double last2 = prediction2;
    while (true)
    {
        double current = last2 - (last2 - last1) / (expressionParser->ParseExpression(equation, last2) - expressionParser->ParseExpression(equation, last1)) * expressionParser->ParseExpression(equation, last2);
        if (abs (current - last2) <= EPS)
            return current;
        last1 = last2;
        last2 = current;
    }
}