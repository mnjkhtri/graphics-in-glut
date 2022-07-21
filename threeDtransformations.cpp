#include <GL/glut.h>
#include "includes/threeDtransformations.hpp"
#include <cmath>
#include <iostream>
using namespace std;
tCoord::tCoord(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
    h = 1;
}

tCoord::tCoord(float _x, float _y, float _z, float _h)
{
    x = _x;
    y = _y;
    z = _z;
    h = _h;
}

void tCoord::show()
{
    cout << x << " " << y << " " << z << endl;
}

tMatrix::tMatrix()
{
    a11 = a22 = a33 = a44 = 1;
    a12 = a13 = a14 = a21 = a23 = a24 = a31 = a32 = a34 = a41 = a42 = a43 = 0;
}

tMatrix::tMatrix(float _a11, float _a12, float _a13, float _a21, float _a22, float _a23, float _a31, float _a32, float _a33)
{
    a11 = _a11;
    a12 = _a12;
    a13 = _a13;
    a14 = 0;

    a21 = _a21;
    a22 = _a22;
    a23 = _a23;
    a24 = 0;

    a31 = _a31;
    a32 = _a32;
    a33 = _a33;
    a34 =  0;

    a41 = a42 = a43 = 0;
    a44 = 1;

}

void tMatrix::add(tMatrix *toadd)
{
    a11 += toadd->a11;
    a12 += toadd->a12;
    a13 += toadd->a13;

    a21 += toadd->a21;
    a22 += toadd->a22;
    a23 += toadd->a23;

    a31 += toadd->a31;
    a32 += toadd->a32;
    a33 += toadd->a33;
}  

void tMatrix::product(float val)
{
    a11 *= val;
    a12 *= val;
    a13 *= val;

    a21 *= val;
    a22 *= val;
    a23 *= val;

    a31 *= val;
    a32 *= val;
    a33 *= val;
}

void tMatrix::multiply(tMatrix *tumul)
{
    float firsta11 = a11;
    float firsta12 = a12;
    a11 = firsta11*tumul->a11 + firsta12*tumul->a21 + a13*tumul->a31;
    a12 = firsta11*tumul->a12 + firsta12*tumul->a22 + a13*tumul->a32;
    a13 = firsta11*tumul->a13 + firsta12*tumul->a23 + a13*tumul->a33;

    float firsta21 = a21;
    float firsta22 = a22;
    a21 = firsta21*tumul->a11 + firsta22*tumul->a21 + a23*tumul->a31;
    a22 = firsta21*tumul->a12 + firsta22*tumul->a22 + a23*tumul->a32;
    a23 = firsta21*tumul->a13 + firsta22*tumul->a23 + a23*tumul->a33;

    float firsta31 = a31;
    float firsta32 = a32;
    a31 = firsta31*tumul->a11 + firsta32*tumul->a21 + a33*tumul->a31;
    a32 = firsta31*tumul->a12 + firsta32*tumul->a22 + a33*tumul->a32;
    a33 = firsta31*tumul->a13 + firsta32*tumul->a23 + a33*tumul->a33;
}

void tMatrix::assignMatrix(tMatrix *toassign)
{
    a11 = toassign->a11;
    a12 = toassign->a12;
    a13 = toassign->a13;
    a14 = toassign->a14;

    a21 = toassign->a21;
    a22 = toassign->a22;
    a23 = toassign->a23;
    a24 = toassign->a24;

    a31 = toassign->a31;
    a32 = toassign->a32;
    a33 = toassign->a33;
    a34 = toassign->a34;

    a41 = toassign->a41;
    a42 = toassign->a42;
    a43 = toassign->a43;
    a44 = toassign->a44;
}

void tMatrix::show()
{
    cout << a11 << " " << a12 << " " << a13 << " " << a14 << endl;
    cout << a21 << " " << a22 << " " << a23 << " " << a24 << endl;   
    cout << a31 << " " << a32 << " " << a33 << " " << a34 << endl;   
    cout << a41 << " " << a42 << " " << a43 << " " << a44 << endl;   
 
}

void ttranslateMatrix(tMatrix* ourMatrix, float tx, float ty, float tz)
{
    ourMatrix->a11 += ourMatrix->a41*tx;
    ourMatrix->a12 += ourMatrix->a42*tx;
    ourMatrix->a13 += ourMatrix->a43*tx;
    ourMatrix->a14 += ourMatrix->a44*tx;

    ourMatrix->a21 += ourMatrix->a41*ty;
    ourMatrix->a22 += ourMatrix->a42*ty;
    ourMatrix->a23 += ourMatrix->a43*ty;
    ourMatrix->a24 += ourMatrix->a44*ty;

    ourMatrix->a31 += ourMatrix->a41*tz;
    ourMatrix->a32 += ourMatrix->a42*tz;
    ourMatrix->a33 += ourMatrix->a43*tz;
    ourMatrix->a34 += ourMatrix->a44*tz;
}

void trotateMatrix(tMatrix* ourMatrix, float theta, tCoord vec)
{
    float sint = sin((3.14*(float)theta)/180.0);
    float cost = cos((3.14*(float)theta)/180.0);
    float ux = vec.x;
    float uy = vec.y;
    float uz = vec.z;

    tMatrix identity;
    identity.product(cost);

    tMatrix uxmatrix;
    uxmatrix.a11 = ux*ux; uxmatrix.a22 = uy*uy; uxmatrix.a33 = uz*uz;
    uxmatrix.a12 = uxmatrix.a21 = ux*uy;
    uxmatrix.a13 = uxmatrix.a31 = ux*uz;
    uxmatrix.a23 = uxmatrix.a32 = uy*uz;
    uxmatrix.product(1-cost);

    tMatrix uumatrix;
    uumatrix.a11 = uumatrix.a22 = uumatrix.a33 = 0;
    uumatrix.a12 = -uz;
    uumatrix.a21 = uz;
    uumatrix.a13 = uy;
    uumatrix.a31 = -uy;
    uumatrix.a23 = -ux;
    uumatrix.a32 = ux;
    uumatrix.product(sint);

    tMatrix final;
    final.product(0);
    final.add(&uxmatrix);
    final.add(&uumatrix);
    final.add(&identity);

    ourMatrix->multiply(&final);
}

void toriginscaleMatrix(tMatrix* ourMatrix, float sx, float sy, float sz)
{
    ourMatrix->a11 *= sx;
    ourMatrix->a12 *= sx;
    ourMatrix->a13 *= sx;
    ourMatrix->a14 *= sx;

    ourMatrix->a21 *= sy;
    ourMatrix->a22 *= sy;
    ourMatrix->a23 *= sy;
    ourMatrix->a24 *= sy;

    ourMatrix->a31 *= sz;
    ourMatrix->a32 *= sz;
    ourMatrix->a33 *= sz;
    ourMatrix->a34 *= sz;

}

void tpivotscaleMatrix(tMatrix* ourMatrix, float sx, float sy, float sz, tCoord pivot)
{
    ttranslateMatrix(ourMatrix, -1*pivot.x, -1*pivot.y, -1*pivot.z);
    toriginscaleMatrix(ourMatrix, sx, sy, sz);
    ttranslateMatrix(ourMatrix, pivot.x, pivot.y, pivot.z);
}

void tdoTransform(tCoord* arr, tMatrix* ourMatrix)
{
    int x = ourMatrix->a11*arr->x + ourMatrix->a12*arr->y + ourMatrix->a13*arr->z + ourMatrix->a14*arr->h;
    int y = ourMatrix->a21*arr->x + ourMatrix->a22*arr->y + ourMatrix->a23*arr->z + ourMatrix->a24*arr->h;
    int z = ourMatrix->a31*arr->x + ourMatrix->a32*arr->y + ourMatrix->a33*arr->z + ourMatrix->a34*arr->h;
    int h = ourMatrix->a41*arr->x + ourMatrix->a42*arr->y + ourMatrix->a43*arr->z + ourMatrix->a44*arr->h;

    arr->x = x;
    arr->y = y;
    arr->z = z;
    arr->h = h;
}

void viewMatrix(tMatrix *unitMatrix, tCoord *reference, tCoord *Nvector, tCoord *Vvector)
{
    float x0 = reference->x;
    float y0 = reference->y;
    float z0 = reference->z;

    float n1 = Nvector->x;
    float n2 = Nvector->y;
    float n3 = Nvector->z;

    float V1 = Vvector->x;
    float V2 = Vvector->y;
    float V3 = Vvector->z;

    float u1 = V2*n3-V3*n2;
    float u2 = V3*n1-V1*n3;
    float u3 = V1*n2-V2*n1;

    float v1 = n2*u3-n3*u2;
    float v2 = n3*u1-n1*u3;
    float v3 = n1*u2-n2*u1;

    tMatrix Rmatrix(u1,u2,u3,v1,v2,v3,n1,n2,n3);
    Rmatrix.a14 = -x0*u1-y0*u2-z0*u3;
    Rmatrix.a24 = -x0*v1-y0*v2-z0*v3;
    Rmatrix.a34 = -x0*n1-y0*n2-z0*n3;
    Rmatrix.a44 = 1;
    unitMatrix->assignMatrix(&Rmatrix);
}

//Send an array of vertices to do view matrix
void DoviewMatrix(tMatrix *ourViewMatrix, tCoord *vertices, int noOfVertices)
{
    for (int k = 0; k < noOfVertices; ++k)
    {
        tdoTransform(vertices+k, ourViewMatrix);
    }
}

void DocabinetMatrix(float phi, tCoord *vertices, int noOfVertices)
{
    float sint = sin((3.14*(float)phi)/180.0);
    float cost = cos((3.14*(float)phi)/180.0);

    for (int k = 0; k < noOfVertices; ++k)
    {
        float xp = vertices[k].x + vertices[k].z*0.5*cost;
        float yp = vertices[k].y + vertices[k].z*0.5*sint;
        vertices[k].x = xp;
        vertices[k].y = yp;
    }
}

void DocavalierMatrix(float phi, tCoord *vertices, int noOfVertices)
{
    float sint = sin((3.14*(float)phi)/180.0);
    float cost = cos((3.14*(float)phi)/180.0);

    for (int k = 0; k < noOfVertices; ++k)
    {
        float xp = vertices[k].x + vertices[k].z*cost;
        float yp = vertices[k].y + vertices[k].z*0.5*sint;
        vertices[k].x = xp;
        vertices[k].y = yp;
    }
}

void DoTranslateMatrix(float tx, float ty, float tz, tCoord *vertices, int noOfVertices)
{
    for (int i = 0; i < noOfVertices; ++i)
    {
        vertices[i].x += tx;
        vertices[i].y += ty;
        vertices[i].z += tz;
    }
}

void Plotvertices(tCoord *coordinates, int COUNT)
{
    for (int i = 0; i < COUNT-1; ++i)
    {
        LineDDA(Coord(coordinates[i].x, coordinates[i].y), Coord(coordinates[i+1].x, coordinates[i+1].y));
    }
}
