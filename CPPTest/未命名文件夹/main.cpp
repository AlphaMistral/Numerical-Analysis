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
    EquationSolver *equationSolver = new EquationSolver();
    cout << equationSolver->SolveByBinary("5*x-8", 0, 5) << endl;
    cout << equationSolver->SolveByNewton("5*x - 8", "5", 12354) << endl;
    cout << equationSolver->SolveBySecant("17*sin(x)-10", 1, 2) << endl;
    double **a = (double**)malloc(sizeof (double*) * 3);
    for (int i = 0;i < 3;i++)
        a[i] = (double*)malloc(sizeof(double) * 4);
    a[0][0] = 2;
    a[0][1] = 3;
    a[0][2] = 4;
    a[1][0] = 3;
    a[1][1] = 5;
    a[1][2] = 2;
    a[2][0] = 4;
    a[2][1] = 3;
    a[2][2] = 30;
    a[0][3] = 6;
    a[1][3] = 5;
    a[2][3] = 32;
    Matrix *mat = new Matrix(3, 4, a);
    Matrix *mat2 = new Matrix(3, 4, a);
    mat->GaussReduce();
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 4;j++)
            printf("%11.6lf", mat->arr[i][j]);
        cout << endl;
    }
    mat2->GaussSimpleReduce();
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 4;j++)
            printf("%11.6lf", mat2->arr[i][j]);
        cout << endl;
    }
    ExpressionParser *expressionParser = new ExpressionParser ();
    cout << expressionParser->ParseExpression("17 * x + sin(x^3) + (pi * 5)", 5.4) << endl;
    a[0][0] = 1;
    a[0][1] = 1;
    a[0][2] = 1;
    a[1][0] = 1;
    a[1][1] = 2;
    a[1][2] = 2;
    a[2][0] = 1;
    a[2][1] = 2;
    a[2][2] = 3;
    Matrix *xx = new Matrix (3, 3, a);
    vector <double> *testArray = new vector <double> ();
    testArray->push_back (5);
    testArray->push_back (6);
    testArray->push_back (8);
    vector <double> *ans = Matrix :: SolveByDooLittle (xx, testArray);
    for (vector <double> :: iterator iter = ans->begin ();iter != ans->end ();iter++)
        cout << *iter << ' ';
    cout << endl;
    ans = Matrix :: SolveByCholesky(xx, testArray);
    for (vector <double> :: iterator iter = ans->begin ();iter != ans->end ();iter++)
        cout << *iter << ' ';
    a[0][0] = 2;
    a[0][1] = 1;
    a[0][2] = 0;
    a[1][0] = 3;
    a[1][1] = 2;
    a[1][2] = 2;
    a[2][0] = 0;
    a[2][1] = -1;
    a[2][2] = 4;
    testArray->clear ();
    testArray->push_back (-1);
    testArray->push_back (7);
    testArray->push_back (23);
    ans = Matrix :: SolveThreeTriByChase(new Matrix (3, 3, a), testArray);
    cout << endl;
    for (vector <double> :: iterator iter = ans->begin ();iter != ans->end ();iter++)
        cout << *iter << ' ';
    ans = Matrix :: SolveLinearByJacobi (new Matrix (3, 3, a), testArray);
    cout << endl;
    for (vector <double> :: iterator iter = ans->begin ();iter != ans->end ();iter++)
        cout << *iter << ' ';
    ans = Matrix :: SolveLinearByGaussSeidel (new Matrix (3, 3, a), testArray);
    cout << endl;
    for (vector <double> :: iterator iter = ans->begin ();iter != ans->end ();iter++)
        cout << *iter << ' ';
    
    cout << endl << endl << endl;
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
    cout << integralTool->gauss_legendre(128, &Polynomial :: GetResult, polynomial, 0, 24)  / 24<< endl;
    double deviation = 0;
    for (int i = 0;i < 25;i++)
        deviation += pow (polynomial->GetYValue(i) - yValues[i], 2);
    cout << "The Deviation is : " << deviation << endl;
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
    cout << ansLength << endl;
    return 0;
}
