//
//  ExpressionParser.hpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef ExpressionParser_hpp
#define ExpressionParser_hpp

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

class ExpressionParser
{
    const static int INCOMPLETE = -1;
    const static int CORRECT = 0;
    const static int SYNTAX = 1;
    const static int BRACELET = 2;
    const static int DIVIDEZERO = 3;
    
    const static int NONEXIST = -1;
    const static int SINGLE = 0;
    const static int ADD = 1;
    const static int SUB = 2;
    const static int MUL = 3;
    const static int DIV = 4;
    const static int EXP = 5;
    
private:
    char *expression;
    double xValue;
    bool isProcessDone;
    int stateCode;
    double GetValue (const char *);
    double GetSingleValue (const char *);
    double GetFuncValue (const char *);
    char *GetExpressionFromPointer (const char *, bool);
    int OperatorReflection (const char);
public:
    ExpressionParser ();
    double ParseExpression (const char *, double);
};
#endif /* ExpressionParser_hpp */
