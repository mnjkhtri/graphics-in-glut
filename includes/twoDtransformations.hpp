#ifndef TWO_INCLUDED
#define TWO_INCLUDED

class Coord
{
    public:
        int x;
        int y;
        int h;
        Coord(int, int);
        
};

class Matrix
{
    public:
        float a11, a12, a13;
        float a21, a22, a23;
        float a31, a32, a33; 
        Matrix();      
};

void translateMatrix(Matrix* ourMatrix, int tx, int ty);
void originrotateMatrix(Matrix* ourMatrix, int theta);
void originscaleMatrix(Matrix* ourMatrix, int sx, int sy);

void pivotrotateMatrix(Matrix* ourMatrix, int theta, Coord pivot);
void pivotscaleMatrix(Matrix* ourMatrix, int sx, int sy, Coord pivot);
Coord doTransform(Coord* arr, Matrix* ourMatrix);

#endif