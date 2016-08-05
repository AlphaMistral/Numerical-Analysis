/****************************************************
学号：14130188019
姓名：于京平
环境：MacOS X Xcode 5

如果在您的电脑上编译存在问题，
请直接通过以下方式与我取得联系，
我将第一时间给您答复！
 
Tel : 17791379371
QQ  : 597379157
Mail: Mistral@weymire.com
 
****************************************************/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>

#include"EquationSolver.hpp"
#include"Matrix.hpp"
#include"PolynomialUtilities.hpp"
#include"IntegralUtilities.hpp"
#include"spline.h"

using namespace std;

int main()
{
    double a[3][3] = { {2, -1, 0}, {-1, 2, -1}, {0, -1, 2} };
    vector < double > *b = new vector < double > { 1, 0, 1 };
    double **eles = new double *[3];
    for (int i = 0;i < 3;i++)
        eles[i] = new double [3];
    for (int i = 0;i < 3;i++)
        for (int j = 0;j < 3;j++)
            eles[i][j] = a[i][j];
    Matrix *mat = new Matrix (3, 3, eles);
    vector < double > *ans = Matrix :: SolveByCholesky(mat, b);
    cout << (*ans)[0] << endl;
    cout << "***********************Homework on June 16th***********************" << endl;
    PolynomialSolver *polynomialSolver = new PolynomialSolver ();
    cout << "Problem 18:" << endl;
    vector<double> xValues, yValues;
    xValues.push_back (-1);
    xValues.push_back (-0.5);
    xValues.push_back (0);
    xValues.push_back (0.5);
    xValues.push_back (1);
    yValues.push_back (-0.22);
    yValues.push_back (0.88);
    yValues.push_back (2.00);
    yValues.push_back (3.13);
    yValues.push_back (4.28);
    vector<double> *ret = polynomialSolver->PolynomialFitting(xValues, yValues, 1);
    cout << "   The 1 degree polynomial fitting result is as follows:" << endl;
    cout << "       y = " << (*ret)[1] << " * x + " << (*ret)[0] << endl;
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 2);
    cout << "   The 2 degree polynomial fittign result is as follows:" << endl;
    cout << "       y = " << (*ret)[2] << " * x ^ 2 + " << (*ret)[1] << " * x + " << (*ret)[0] << endl;
    cout << endl << endl;
    xValues.clear();
    yValues.clear();
    ret->clear();
    cout << "Problem 19:" << endl;
    xValues.push_back (1);
    xValues.push_back (2);
    xValues.push_back (3);
    xValues.push_back (4);
    xValues.push_back (5);
    xValues.push_back (6);
    xValues.push_back (7);
    xValues.push_back (8);
    yValues.push_back (log(15.3));
    yValues.push_back (log(20.5));
    yValues.push_back (log(27.4));
    yValues.push_back (log(34.6));
    yValues.push_back (log(49.1));
    yValues.push_back (log(65.6));
    yValues.push_back (log(87.8));
    yValues.push_back (log(117.6));
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 1);
    (*ret)[0] = exp((*ret)[0]);
    cout << "   The result is as follows:" << endl;
    cout << "       y = " << (*ret)[1] << " * x + " << (*ret)[0] << endl;
    cout << endl << endl;
    xValues.clear ();
    yValues.clear ();
    ret->clear ();
    cout << "Problem 20:" << endl;
    xValues.push_back (pow (19, 2));
    xValues.push_back (pow (25, 2));
    xValues.push_back (pow (31, 2));
    xValues.push_back (pow (38, 2));
    xValues.push_back (pow (44, 2));
    yValues.push_back (19);
    yValues.push_back (32.3);
    yValues.push_back (49);
    yValues.push_back (73.3);
    yValues.push_back (97.8);
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 1);
    cout << "   The result is as follows:" << endl;
    cout << "       y = " << (*ret)[1] << " * x ^ 2 + " << (*ret)[0] << endl;
    cout << endl << endl;
    xValues.clear ();
    yValues.clear ();
    ret->clear ();
    cout << "Problem 21:" << endl;
    xValues.push_back (1 / 1);
    xValues.push_back (1 / 2);
    xValues.push_back (1 / 3);
    xValues.push_back (1 / 4);
    yValues.push_back (0.33);
    yValues.push_back (0.4);
    yValues.push_back (0.44);
    yValues.push_back (0.45);
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 1);
    cout << "   The result is as follows:" << endl;
    cout << "       y = " << (*ret)[1] << " * x ^ (-1) + " << (*ret)[0] << endl;
    cout << endl << endl;
    xValues.clear ();
    yValues.clear ();
    ret->clear ();
    xValues.push_back (log (3));
    xValues.push_back (log (5));
    xValues.push_back (log (10));
    xValues.push_back (log (20));
    yValues.push_back (3.5);
    yValues.push_back (4.8);
    yValues.push_back (4.2);
    yValues.push_back (4.5);
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 1);
    cout << "   The result is as follows:" << endl;
    cout << "       y = " << (*ret)[1] << " * lnx + " << (*ret)[0] << endl;
    cout << "***********************Homework on June 16th***********************" << endl;
    cout << "***********************Homework on June 24th***********************" << endl;
    cout << "Problem 1 : " << endl;
    double xxx[] = {9.01, 8.96, 7.96, 7.97, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28, 13.32, 12.61, 11.29, 10.22, 9.15, 7.90, 7.95, 8.86, 9.81, 10.80, 10.93};
    xValues.clear ();
    yValues.clear ();
    for (int i = 0;i < 21;i++)
        xValues.push_back (i), yValues.push_back (xxx[i]);
    tk :: spline sp;
    sp.set_points (xValues, yValues);
    double ansLength = 0.0;
    for (double i = 0.2;i <= 20;i += 0.2)
    {
        ansLength += sqrt (0.2 * 0.2 + pow(sp(i) - sp(i - 0.2), 2));
    }
    cout << "光缆的长度为:" << ansLength << endl;
    cout << "Problem 2 : " << endl;
    xValues.clear ();
    yValues.clear ();
    ret->clear ();
    for (int i = 0;i < 25;i++)
        xValues.push_back (i);
    int t[] = {15, 14, 14, 14, 14, 15, 16, 18, 20, 20, 23, 25, 28, 31, 34, 31, 29, 27, 25, 24, 22, 20, 18, 17, 16};
    for (int i = 0;i < 25;i++)
    yValues.push_back (t[i]);
    ret = polynomialSolver->PolynomialFitting(xValues, yValues, 4);
    Polynomial *polynomial = new Polynomial (ret);
    IntegralUtilities *integralTool = new IntegralUtilities ();
    cout << "当天的气象学平均温度为:" << integralTool->gauss_legendre(128, &Polynomial :: GetResult, polynomial, 0, 24)  / 24 << endl;
    double adt = 0;
    for (int i = 0;i < 25;i++)adt += t[i];
    adt /= 25;
    cout << "当天的平均温度为:" << adt << endl;
    double deviation = 0;
    for (int i = 0;i < 25;i++)
        deviation += pow (polynomial->GetYValue(i) - yValues[i], 2);
    cout << "多项式拟合结果如下: y = " << (*ret)[4] << " * x ^ 4 " << (*ret)[3] << " * x ^ 3 + " << (*ret)[2] << " * x ^ 2 " << (*ret)[1] << " * x + " << (*ret)[0] << endl;
    cout << "误差为: " << deviation << endl;
    cout << "***********************Homework on June 24th***********************" << endl;
    return 0;
}
