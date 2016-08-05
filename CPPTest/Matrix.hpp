//
//  Matrix.hpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class Matrix
{
private:
    int colNum, rowNum;
    constexpr static double UNDETERMINED = 0x3f3f3f3f;
    constexpr static int MAXITERTIME = 1500;
    constexpr static double EPS = 1e-5;
public:
    double **arr;
    Matrix(int row, int col, double **val);
    Matrix(int row, int col);
    Matrix(Matrix &mat);
    void GaussReduce ();
    void GaussSimpleReduce ();
    static Matrix *ZeroMatrix(int);
    static Matrix *UnitMatrix(int);
    static Matrix *TransPose(Matrix *);
    static double GetDifference(vector <double> *, vector <double> *);
    static vector<double> *SolveByDooLittle(Matrix *, vector<double> *);
    static vector<double> *SolveByGauss(Matrix *, vector<double> *);
    static vector <double> * SolveDiagonalMatrix (Matrix *, vector <double> *, bool);
    static vector <double> * SolveByCholesky (Matrix *, vector <double> *);
    static vector <double> * SolveByImprovedCholesky (Matrix *, vector <double> *);
    static vector <double> * SolveThreeTriByChase (Matrix *, vector <double> *);
    static vector <double> * SolveLinearByJacobi (Matrix *, vector <double> *, int x = MAXITERTIME);
    static vector <double> * SolveLinearByGaussSeidel (Matrix *, vector <double> *, int x = MAXITERTIME);
    Matrix *operator * (const Matrix *)const;
    Matrix *operator + (const Matrix *)const;
};

#endif /* Matrix_hpp */
