#include <GL/glut.h>
#include "twoDtransformations.hpp"
#include <cmath>
#include <iostream>
using namespace std;
Coord::Coord(int _x, int _y)
{
    x = _x;
    y = _y;
    h = 1;
}

Matrix::Matrix()
{
    a11 = a22 = a33 = 1;
    a12 = a13 = a21 = a23 = a31 = a32 = 0;
}

void translateMatrix(Matrix* ourMatrix, int tx, int ty)
{
    ourMatrix->a11 += ourMatrix->a31*tx;
    ourMatrix->a12 += ourMatrix->a32*tx;
    ourMatrix->a13 += ourMatrix->a33*tx;

    ourMatrix->a21 += ourMatrix->a31*ty;
    ourMatrix->a22 += ourMatrix->a32*ty;
    ourMatrix->a23 += ourMatrix->a33*ty;
}

void originrotateMatrix(Matrix* ourMatrix, int theta)
{
    float sint = sin((3.14*(float)theta)/180.0);
    float cost = cos((3.14*(float)theta)/180.0);
    int a11s = ourMatrix->a11;
    int a12s = ourMatrix->a12;
    int a13s = ourMatrix->a13;
    ourMatrix->a11 = cost*ourMatrix->a11-sint*ourMatrix->a21;
    ourMatrix->a12 = cost*ourMatrix->a12-sint*ourMatrix->a22;
    ourMatrix->a13 = cost*ourMatrix->a13-sint*ourMatrix->a23;

    ourMatrix->a21 = sint*a11s+cost*ourMatrix->a21;
    ourMatrix->a22 = sint*a12s+cost*ourMatrix->a22;
    ourMatrix->a23 = sint*a13s+cost*ourMatrix->a23;
}

void originscaleMatrix(Matrix* ourMatrix, int sx, int sy)
{
    ourMatrix->a11 *= sx;
    ourMatrix->a12 *= sx;
    ourMatrix->a13 *= sx;

    ourMatrix->a21 *= sy;
    ourMatrix->a22 *= sy;
    ourMatrix->a23 *= sy;
}

void pivotrotateMatrix(Matrix* ourMatrix, int theta, Coord pivot)
{
    translateMatrix(ourMatrix, -1*pivot.x, -1*pivot.y);
    originrotateMatrix(ourMatrix, theta);
    translateMatrix(ourMatrix, pivot.x, pivot.y);
}

void pivotscaleMatrix(Matrix* ourMatrix, int sx, int sy, Coord pivot)
{
    translateMatrix(ourMatrix, -1*pivot.x, -1*pivot.y);
    originscaleMatrix(ourMatrix, sx, sy);
    translateMatrix(ourMatrix, pivot.x, pivot.y);
}

Coord doTransform(Coord* arr, Matrix* ourMatrix)
{
    int x = ourMatrix->a11*arr->x + ourMatrix->a12*arr->y + ourMatrix->a13*arr->h;
    int y = ourMatrix->a21*arr->x + ourMatrix->a22*arr->y + ourMatrix->a23*arr->h;
    return Coord(round(x),round(y));
}