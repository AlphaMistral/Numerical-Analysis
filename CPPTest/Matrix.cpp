//
//  Matrix.cpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Matrix.hpp"

Matrix :: Matrix(int row, int col,double **val)
{
    rowNum = row;
    colNum = col;
    arr = (double **)malloc(sizeof (double *) * row);
    for (int i = 0;i < row;i++)
        arr[i] = (double *)malloc(sizeof(double) * col);
    for (int i = 0;i < row;i++)
        for (int j = 0;j < col;j++)
            arr[i][j] = val[i][j];
}

Matrix :: Matrix (int row, int col)
{
    rowNum = row;
    colNum = col;
    arr = (double **)malloc (sizeof (double *) * row);
    for (int i = 0;i < row;i++)
        arr[i] = (double *)malloc (sizeof (double) * col);
    for (int i = 0;i < row;i++)
        for (int j = 0;j < row;j++)
            arr[i][j] = 0;
}

Matrix :: Matrix (Matrix &mat)
{
    new (this)Matrix (mat.rowNum, mat.colNum, mat.arr);
}

Matrix * Matrix :: ZeroMatrix (int x)
{
    Matrix *mat = new Matrix (x, x);
    return mat;
}

Matrix * Matrix :: UnitMatrix (int x)
{
    Matrix *mat = new Matrix (x, x);
    for (int i = 0;i < x;i++)
        for (int j = 0;j < x;j++)
            mat->arr[i][j] = 1;
    return mat;
}

void Matrix :: GaussReduce()
{
    for (int i = 0, j = 0;j < rowNum;i++,j++)
    {
        int maxRow = i;
        double maxAbs = 0;
        for(int k = i;k < rowNum;k++)
        {
            if (abs (arr[k][j]) > maxAbs)
            {
                maxRow = k;
                maxAbs = abs (arr[k][j]);
            }
        }
        if (maxAbs == 0)
        {
            i--;
            j++;
            continue;
        }
        if (maxRow != i)
            swap(arr[i], arr[maxRow]);
        double div = arr[i][j];
        for (int k = 0;k < colNum;k++)
            arr[i][k] /= div;
        for (int r = 0;r < rowNum;r++)
        {
            if (r == i)
                continue;
            double mul = arr[r][j];
            for (int k = 0;k < colNum;k++)
                arr[r][k] -= mul * arr[i][k];
        }
    }
}

void Matrix :: GaussSimpleReduce ()
{
    for (int i = 0;i < rowNum;i++)
    {
        double div = arr[i][i];
        for (int j = 0;j < colNum;j++)
            arr[i][j] /= div;
        for (int j = i + 1;j < rowNum;j++)
        {
            double mul = -arr[j][i] / arr[i][i];
            for (int k = i;k < colNum;k++)
                arr[j][k] += mul * arr[i][k];
        }
    }
    for (int i = rowNum - 1;i > 0;i--)
    {
        for (int j = i - 1;j >= 0;j--)
        {
            double mul = -arr[j][i] / arr[i][i];
            for (int k = 0;k < colNum;k++)
                arr[j][k] += mul * arr[i][k];
        }
    }
}

vector<double> * Matrix :: SolveByDooLittle(Matrix *mat, vector<double> *vec)
{
    double **arr1 = (double **)malloc (sizeof (double *) * mat->rowNum);
    double **arr2 = (double **)malloc (sizeof (double *) * mat->rowNum);
    for (int i = 0;i < mat->rowNum;i++)
    {
        arr1[i] = (double *)malloc (sizeof (double) * mat->colNum);
        arr2[i] = (double *)malloc (sizeof (double) * mat->colNum);
    }
    for (int i = 0;i < mat->colNum;i++)
        arr1[i][i] = 1;
    for (int i = 0;i < mat->colNum;i++)
        arr2[0][i] = mat->arr[0][i];
    for (int i = 1;i < mat->rowNum;i++)
        arr1[i][0] = mat->arr[i][0] / mat->arr[0][0];
    for (int i = 1;i < mat->rowNum;i++)
    {
        for (int j = i;j < mat->colNum;j++)
        {
            double num = mat->arr[i][j];
            for (int k = 0;k < i;k++)
                num -= arr1[i][k] * arr2[k][j];
            arr2[i][j] = num;
        }
        for (int j = i + 1;j < mat->rowNum;j++)
        {
            double num = mat->arr[j][i];
            for (int k = 0;k < i;k++)
                num -= arr1[j][k] * arr2[k][i];
            arr1[j][i] = num / arr2[i][i];
        }
    }
    Matrix *lu = new Matrix (mat->rowNum, mat->colNum, arr1);
    for (int i = 0;i < mat->rowNum;i++)
        lu->arr[i][i] = 1;
    vector <double> *y = SolveDiagonalMatrix(lu, vec, false);
    lu = new Matrix (mat->rowNum, mat->colNum, arr2);
    return SolveDiagonalMatrix(lu, y, true);
}

Matrix * Matrix :: operator *(const Matrix *mat)const
{
    Matrix *ret;
    if (this->colNum != mat->rowNum)
    {
        ret = new Matrix (1, 1);
        ret->arr[0][0] = UNDETERMINED;
        return ret;
    }
    ret = new Matrix (this->rowNum, mat->colNum);
    for (int i = 0;i < this->rowNum;i++)
    {
        for (int j = 0;j < mat->colNum;j++)
        {
            double res = 0.0;
            for (int k = 0;k < this->colNum;k++)
                res += this->arr[i][k] * mat->arr[k][j];
            ret->arr[i][j] = res;
        }
    }
    return ret;
}

Matrix * Matrix :: operator + (const Matrix *mat)const
{
    Matrix *ret;
    if (this->colNum != mat->colNum || this->rowNum != mat->rowNum)
    {
        ret = new Matrix (1, 1);
        ret->arr[0][0] = UNDETERMINED;
        return ret;
    }
    ret = new Matrix (this->colNum, this->rowNum);
    for (int i = 0;i < this->rowNum;i++)
        for (int j = 0;j < this->colNum;j++)
            ret->arr[i][j] = this->arr[i][j] + mat->arr[i][j];
    return ret;
}

vector <double> * Matrix :: SolveDiagonalMatrix(Matrix *mat, vector<double> *vec, bool isUpper)
{
    vector <double> * tempVec = new vector <double> ();
    vector <double> * retVec = new vector <double> ();
    retVec->clear ();
    for (vector <double> :: iterator iter = vec->begin ();iter != vec->end ();iter++)
        retVec->push_back(*iter), tempVec->push_back (*iter);
    if (isUpper)
    {
        for (int i = mat->rowNum - 1;i >= 0;i--)
        {
            (*retVec)[i] = (*tempVec)[i] / mat->arr[i][i];
            for (int j = i - 1;j >= 0;j--)
                (*tempVec)[j] -= (*retVec)[i] * mat->arr[j][i];
        }
    }
    else
    {
        for (int i = 0;i < mat->rowNum;i++)
        {
            (*retVec)[i] = (*tempVec)[i] / mat->arr[i][i];
            for (int j = i + 1;j < mat->rowNum;j++)
                (*tempVec)[j] -= (*retVec)[i] * mat->arr[j][i];
        }
    }
    return retVec;
}

vector <double> * Matrix :: SolveByGauss (Matrix *mat, vector<double> *vec)
{
    vector <double> *ret = new vector <double> ();
    Matrix *x = new Matrix (*mat);
    for (vector <double> :: iterator iter = vec->begin ();iter != vec->end ();iter++)
        ret->push_back (*iter);
    for (int i = 0;i < x->colNum;i++)
    {
        
    }
    return ret;
}

vector <double> * Matrix :: SolveByCholesky (Matrix *mat, vector <double> *vec)
{
    double **arr = (double **)malloc (sizeof (double *) * mat->rowNum);
    for (int i = 0;i < mat->rowNum;i++)
    {
        arr[i] = (double *)malloc (sizeof (double) * mat->colNum);
        memset (arr[i], 0, sizeof (double) * mat->colNum);
    }
    for (int j = 0;j < mat->colNum;j++)
    {
        double num = 0;
        for (int k = 0;k < j;k++)
            num += arr[j][k] * arr[j][k];
        arr[j][j] = sqrt (mat->arr[j][j] - num);
        for (int i = j + 1;i < mat->rowNum;i++)
        {
            num = 0;
            for (int k = 0;k < j;k++)
                num += arr[i][k] * arr[j][k];
            arr[i][j] = sqrt (mat->arr[i][j] - num) / arr[j][j];
        }
    }
    Matrix *mat1 = new Matrix (mat->rowNum, mat->colNum, arr);
    Matrix *mat2 = Matrix :: TransPose(mat1);
    vector <double> *y = SolveDiagonalMatrix(mat1, vec, false);
    return SolveDiagonalMatrix(mat2, y, true);
}

vector <double> * Matrix :: SolveThreeTriByChase(Matrix *mat, vector<double> *vec)
{
    double **arr = mat->arr;
    double *u = (double *)malloc (sizeof (double) * mat->rowNum);
    double *q = (double *)malloc (sizeof (double) * mat->rowNum);
    vector <double> *ret = new vector <double> ();
    for (int i = 0;i < mat->rowNum;i++)
        ret->push_back (0);
    u[0] = arr[0][1] / arr[0][0];
    q[0] = (*vec)[0] / arr[0][0];
    for (int i = 1;i < mat->rowNum - 1;i++)
        u[i] = arr[i][i + 1] / (arr[i][i] - u[i - 1] * arr[i][i - 1]);
    for (int i = 1;i < mat->rowNum;i++)
        q[i] = ((*vec)[i] - q[i - 1] * arr[i][i - 1]) / (arr[i][i] - u[i - 1] * arr[i][i - 1]);
    (*ret)[mat->rowNum - 1] = q[mat->rowNum - 1];
    for (int i = mat->rowNum - 2;i >= 0;i--)
        (*ret)[i] = q[i] - u[i] * (*ret)[i + 1];
    return ret;
}

Matrix * Matrix :: TransPose (Matrix *mat)
{
    Matrix *ret = new Matrix (mat->colNum, mat->rowNum);
    for (int i = 0;i < ret->rowNum;i++)
        for (int j = 0;j < ret->colNum;j++)
            ret->arr[i][j] = mat->arr[j][i];
    return ret;
}

double Matrix :: GetDifference(vector<double> *vec1, vector<double> *vec2)
{
    double ans = 0;
    for (int i = 0;i < vec1->size ();i++)
    {
        ans += abs ((*vec1)[i] - (*vec2)[i]);
    }
    return sqrt (ans);
}

vector <double> * Matrix :: SolveLinearByJacobi(Matrix *mat, vector<double> *vec, int maxIterTime)
{
    vector <double> *vec1, *vec2, *cur, *pre;
    vec1 = new vector <double> ();
    vec2 = new vector <double> ();
    cur = vec1;
    pre = vec2;
    for (int i = 0;i < mat->rowNum;i++)
        pre->push_back (0), cur->push_back (0x3f3f3f3f);
    int iterTime = 0;
    while (iterTime < maxIterTime && GetDifference(cur, pre) > EPS)
    {
        iterTime++;
        for (int i = 0;i < mat->rowNum;i++)
        {
            double num = 0;
            for (int j = 0;j < mat->rowNum;j++)
            {
                if (i == j)
                    continue;
                num += mat->arr[i][j] * (*pre)[j];
            }
            (*cur)[i] = ((*vec)[i] - num) / mat->arr[i][i];
        }
        swap (cur, pre);
    }
    return cur;
}

vector <double> * Matrix :: SolveLinearByGaussSeidel (Matrix *mat, vector<double> *vec, int maxIterTime)
{
    vector <double> *vec1, *vec2, *cur, *pre;
    vec1 = new vector <double> ();
    vec2 = new vector <double> ();
    cur = vec1;
    pre = vec2;
    for (int i = 0;i < mat->rowNum;i++)
        pre->push_back (0), cur->push_back (0);
    int iterTime = 0;
    while ((iterTime < maxIterTime && GetDifference (cur, pre) > EPS) || iterTime == 0)
    {
        iterTime++;
        for (int i = 0;i < mat->rowNum;i++)
        {
            double num = 0;
            for (int j = 0;j < i;j++)
                num += mat->arr[i][j] * (*cur)[j];
            for (int j = i + 1;j < mat->rowNum;j++)
                num += mat->arr[i][j] * (*pre)[j];
            (*cur)[i] = ((*vec)[i] - num) / mat->arr[i][i];
        }
        swap (cur, pre);
    }
    return cur;
}