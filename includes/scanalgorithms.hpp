#ifndef SCAN_INCLUDED
#define SCAN_INCLUDED

#include "twoDtransformations.hpp"
void LineDDA(Coord, Coord);
void LineBresenham(Coord, Coord);
void Circle(Coord, int);
void Ellipse(Coord, int, int);
void Square(Coord, Coord, Coord, Coord);
void putPixel(int , int , int, int, int);

void RasterizeTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
#endif
