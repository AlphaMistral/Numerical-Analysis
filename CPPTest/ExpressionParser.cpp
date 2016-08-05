//
//  ExpressionParser.cpp
//  CPPTest
//
//  Created by 于京平 on 16/4/10.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "ExpressionParser.hpp"

ExpressionParser :: ExpressionParser ()
{
    
}

double ExpressionParser :: ParseExpression(const char *expr, double xV)
{
    xValue = xV;
    expression = (char *)malloc (sizeof (char) * (strlen (expr)+ 1));
    int i = 0,j = 0;
    while (*(expr + i) != '\0')
    {
        if (*(expr + i) != ' ')
            *(expression + j++) = *(expr + i);
        i++;
    }
    realloc (expression, sizeof (char) * (strlen (expression) + 1));
    //cout << expression;
    isProcessDone = false;
    stateCode = INCOMPLETE;
    double result = GetValue(expression);
    isProcessDone = true;
    return result;
}

double ExpressionParser :: GetValue (const char *expr)
{
    if (isProcessDone)
        return 0;
    int currentIndex = 0;
    char *m_expr = (char *)malloc(sizeof(char) * (1 + strlen (expr)));
    strcpy(m_expr, expr);
    while (*m_expr == '(' && *(m_expr + strlen (m_expr) - 1) == ')')
    {
        m_expr++;
        *(m_expr + strlen (m_expr) - 1) = '\0';
    }
    bool allowNegative = true;
    pair<int, int>operation = make_pair(INT_MAX, INT_MAX);
    while (currentIndex < strlen (m_expr))
    {
        char c = *(m_expr + currentIndex);
        pair<int, int>opera = make_pair(INT_MAX, INT_MAX);
        int operate = OperatorReflection(c);
        if (operate != NONEXIST && !allowNegative)
        {
            opera = make_pair(operate, currentIndex);
            operation = operation < opera? operation : opera;
            currentIndex++;
        }
        char *temp = GetExpressionFromPointer(m_expr + currentIndex, allowNegative);
        allowNegative = false;
        currentIndex += strlen (temp);
    }
    if (operation.first == INT_MAX)
    {
        return GetSingleValue(m_expr);
    }
    int splitPosition = operation.second;
    char *firstExpression = (char *)malloc(sizeof (char) * (1 + strlen (m_expr))), *secondExpression = (char *)malloc(sizeof (char) * (1 + strlen (m_expr)));
    strncpy(firstExpression, m_expr, splitPosition);
    strncpy(secondExpression, m_expr + splitPosition + 1, strlen (m_expr) - splitPosition - 1);
    double result = 0;
    switch (operation.first)
    {
        case ADD:
            result = GetValue(firstExpression) + GetValue(secondExpression);
            break;
        case SUB:
            result = GetValue(firstExpression) - GetValue(secondExpression);
            break;
        case MUL:
            result = GetValue(firstExpression) * GetValue(secondExpression);
            break;
        case DIV:
            result = GetValue(firstExpression) / GetValue(secondExpression);
            break;
        case EXP:
            result = pow(GetValue(firstExpression), GetValue(secondExpression));
            break;
        default:
            break;
    }
    return result;
}

char * ExpressionParser :: GetExpressionFromPointer(const char *expr, bool allowNeg)
{
    char *finalExpr = (char *)malloc(sizeof (char) * strlen (expr));
    int i = 0, j = 0;
    int start = 0, end = 0;
    if (*expr == '-')
    {
        if (allowNeg)
        {
            *(finalExpr + j++) = '-';
            i++;
            allowNeg = false;
        }
        else
        {
            stateCode = SYNTAX;
            isProcessDone = true;
            return finalExpr;
        }
    }
    for (int imax = (int)strlen (expr);i < imax;i++)
    {
        char c = *(expr + i);
        if (isdigit(c) || isalpha(c))
            *(finalExpr + j++) = c;
        else if (c == '(')
        {
            *(finalExpr + j++) = c;
            start++;
        }
        else if (c == ')')
        {
            *(finalExpr + j++) = c;
            end++;
            if (start == end)
                break;
        }
        else if (start > end)
            *(finalExpr + j++) = c;
        else break;
    }
    realloc(finalExpr, sizeof (char) * (strlen (finalExpr) + 1));
    return finalExpr;
}

int ExpressionParser :: OperatorReflection(const char c)
{
    switch (c)
    {
        case '+':
            return ADD;
            break;
        case '-':
            return SUB;
            break;
        case '*':
            return MUL;
            break;
        case '/':
            return DIV;
            break;
        case '^':
            return EXP;
        default:
            return NONEXIST;
    }
}

double ExpressionParser :: GetSingleValue(const char *expr)
{
    char *finalExpr = (char *)malloc (sizeof(char) * (1 + strlen (expr)));
    strcpy(finalExpr, expr);
    double sign = 1;
    if (*expr == '-')
    {
        sign = -1;
        finalExpr++;
    }
    while (*finalExpr == '(' && *(finalExpr + strlen (finalExpr) - 1) == ')')
    {
        *(finalExpr + strlen (finalExpr) - 1) = '\0';
        finalExpr++;
    }
    char *testExpression = GetExpressionFromPointer(finalExpr, false);
    if (strcmp(testExpression, finalExpr) == 0)
    {
        if (isdigit(*finalExpr))
            return sign * atof(finalExpr);
        else if (strcmp(finalExpr, "x") == 0)
            return sign * xValue;
        else return GetFuncValue(finalExpr);
    }
    else return sign * GetValue (finalExpr);
}

double ExpressionParser :: GetFuncValue(const char *expr)
{
    char *funcName = (char *)malloc(sizeof(char) * (1 + strlen(expr)));
    int i = 0, j = 0, imax = (int)strlen (expr);
    for (;i < imax;i++)
    {
        if (*(expr + i) != '(')
            *(funcName + j++) = *(expr + i);
        else break;
    }
    if (strcmp(funcName, "sin") == 0)
    {
        return sin(GetValue(expr + i));
    }
    else if (strcmp(funcName, "cos") == 0)
    {
        return cos(GetValue(expr + i));
    }
    else if (strcmp(funcName, "tan") == 0)
    {
        return tan(GetValue(expr + i));
    }
    else if (strcmp(funcName, "cot") == 0)
    {
        return 1.0 / tan(GetValue(expr + i));
    }
    else if (strcmp(funcName, "arcsin") == 0)
    {
        return asin(GetValue(expr + i));
    }
    else if (strcmp(funcName, "arccos") == 0)
    {
        return acos(GetValue(expr + i));
    }
    else if (strcmp(funcName, "arctan") == 0)
    {
        return atan(GetValue(expr + i));
    }
    else if (strcmp(funcName, "arccot") == 0)
    {
        return atan(1.0 / GetValue(expr + i));
    }
    else if (strcmp(funcName, "abs") == 0)
    {
        return abs (GetValue(expr + i));
    }
    else if (strcmp(funcName, "pi") == 0)
    {
        if (i != imax)
        {
            isProcessDone = true;
            stateCode = SYNTAX;
            return 0;
        }
        else return acos(-1.0);
    }
    else if (strcmp(funcName, "e") == 0)
    {
        if (i != imax)
        {
            isProcessDone = true;
            stateCode = SYNTAX;
            return 0;
        }
        else return 2.71828;
    }
    return 0;
}