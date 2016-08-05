//
//  PolynomialUtilities.cpp
//  CPPTest
//
//  Created by 于京平 on 16/6/17.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "PolynomialUtilities.hpp"

PolynomialSolver :: PolynomialSolver ()
{
    
}

double PolynomialSolver :: LagrangeInterp(double *xValues, double *yValues, int num, double xi)
{
    double ans = 0;
    for (int i = 0;i < num;i++)
    {
        int s = 1, t = 1;
        for (int j = 0;j < num;j++)
        {
            if (j != i)
            {
                s = s * (xi - xValues[j]);
                t = t * (xValues[i] - xValues[j]);
            }
        }
        ans += (s / t) * yValues[i];
    }
    return ans;
}

double PolynomialSolver :: NewtonInterp(double *xValues, double *yValues, int num, double xi)
{
    double ans = 0;
    for (int j = 0;j < num - 1;j++)
    {
        for (int k = num - 1;k > j;k++)
        {
            yValues[k]=(yValues[k]-yValues[k - 1]) / (xValues[k] - xValues[k - j - 1]);
        }
    }
    double mult = 1.0;
    for (int i = num - 1;i >= 0;i--)
    {
        mult = 1;
        for (int j = 0;j < i;j++)
            mult *= (xi - xValues[j]);
        mult *= yValues[i];
        ans += mult;
    }
    return ans;
}

double PolynomialSolver :: NewtonForwardInterp(double *xValues, double *yValues, int num, double xi)
{
    double ans = 0;
    double h = xValues[1] - xValues[0];
    double **diff = (double **)malloc (sizeof (double *) * num);
    for (int i = 0;i < num;i++)
        diff[i] = (double *)malloc (sizeof (double) * ORDER);
    for (int i = 0;i < num;i++)
        diff[i][1] = yValues[i + 1] - yValues[i];
    for (int j = 2;j < ORDER;j++)
    {
        for (int i = 0;i <= num - j;i++)
            diff[i][j] = diff[i + 1][j - 1]- diff[i][j - 1];
    }
    int pos = 0;
    while (!(xValues[pos] > xi))pos++;
    pos--;
    double p = (xi - xValues[pos]) / h;
    double yp = yValues[pos];
    double nr = 1, dr = 1;
    for (int k = 1;k <= ORDER;k++)
    {
        nr *= p - k + 1;
        dr *= k;
        yp += (nr / dr)*diff[pos][k];
    }
    return ans;
}

pair<double, double> PolynomialSolver :: LeastSquare(const vector<double> &xValues, const vector<double> &yValues)
{
    double a, b;
    double t1 = 0, t2 = 0, t3 = 0, t4= 0;
    for (int i = 0, imax = (int)xValues.size ();i < imax;i++)
    {
        t1 += xValues[i]*xValues[i];
        t2 += xValues[i];
        t3 += xValues[i]*yValues[i];
        t4 += yValues[i];
    }
    a = (t3 * xValues.size() - t2 * t4) / (t1 * xValues.size() - t2 * t2);
    b = (t1 * t4 - t2 * t3) / (t1 * xValues.size() - t2 * t2);
    return make_pair(a, b);
}

vector<double> * PolynomialSolver :: PolynomialFitting(const vector<double> &xValues, const vector<double> &yValues, int degree)
{
    int N = (int)xValues.size ();
    int n = degree;
    vector<double> *ret = new vector<double> ();
    ret->resize(n + 1);
    double *X = (double *)malloc (sizeof (double) * (2 * n + 1));
    double *Y = (double *)malloc (sizeof (double) * (n + 1));
    double **B = (double **)malloc (sizeof (double *) * (n + 1));
    for (int i = 0;i <= n;i++)
        B[i] = (double *)malloc (sizeof (double) * (n + 2));
    for (int i = 0;i < 2 * n + 1;i++)
    {
        X[i]=0;
        for (int j = 0;j < N;j++)
            X[i] = X[i] + pow(xValues[j], i);
    }
    for (int i = 0;i <= n;i++)
        for (int j = 0;j <= n;j++)
            B[i][j] = X[i + j];
    for (int i = 0;i < n + 1;i++)
    {
        Y[i]=0;
        for (int j = 0;j < N;j++)
            Y[i] = Y[i] + pow(xValues[j], i) * yValues[j];
    }
    for (int i = 0;i <= n;i++)
        B[i][n+1] = Y[i];
    n++;
    for (int i = 0;i < n;i++)
        for (int k = i + 1;k < n;k++)
            if (B[i][i] < B[k][i])
                for (int j = 0;j <= n;j++)
                {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
    
    for (int i = 0;i < n - 1;i++)
        for (int k = i + 1;k < n;k++)
        {
            double t = B[k][i] / B[i][i];
            for (int j = 0;j <= n;j++)
                B[k][j] = B[k][j] - t * B[i][j];
        }
    for (int i = n - 1;i >= 0;i--)
    {
        (*ret)[i] = B[i][n];
        for (int j = 0;j < n;j++)
            if (j != i)
                (*ret)[i] = (*ret)[i] - B[i][j] * (*ret)[j];
        (*ret)[i] = (*ret)[i] / B[i][i];
    }
    return ret;
}

double PolynomialSolver :: GetPolynomialResult (vector<double> *coefficients, double xValue)
{
    double ans = 0.0;
    int len = (int)coefficients->size();
    for (int i = 0;i < len;i++)
        ans += (*coefficients)[i] * pow (xValue, i);
    return ans;
}

Polynomial :: Polynomial ()
{
    size = 0;
}

Polynomial :: Polynomial (vector<double> *coef)
{
    size = (int)coef->size ();
    for (int i = 0;i < size;i++)
        coefficients.push_back ((*coef)[i]);
}

double Polynomial :: GetResult(double xValue, void *data)
{
    Polynomial *poly = (Polynomial *)data;
    return poly->GetYValue(xValue);
}

double Polynomial :: GetYValue (double xValue)
{
    double ans = 0.0;
    for (int i = 0;i < size;i++)
        ans += coefficients[i] * pow (xValue, i);
    return ans;
}